#include "CGLES3ShaderProgram.h"
#include "GLESDebug.h"
#include "GLESType.h"
#include "base/Log.h"
#include "base/StringHelper.h"

#include <stdarg.h>

namespace magic
{
///////////////////////////////////////////////////////////////////////////////
// Identity Shader (ESS_SHADER_IDENTITY)
// This shader does no transformations at all, and uses the current
// glColor value for fragments.
// It will shade between verticies.
static const char *szIdentityShaderVP = "attribute vec4 vVertex;"
                                        "void main(void) "
                                        "{ gl_Position = vVertex; "
                                        "}";

static const char *szIdentityShaderFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "uniform vec4 vColor;"
    "void main(void) "
    "{ gl_FragColor = vColor;"
    "}";

///////////////////////////////////////////////////////////////////////////////
// Flat Shader (ESS_SHADER_FLAT)
// This shader applies the given model view matrix to the verticies,
// and uses a uniform color value.
static const char *szFlatShaderVP = "uniform mat4 mvpMatrix;"
                                    "attribute vec3 vVertex;"
                                    "void main(void) "
                                    "{ gl_Position = mvpMatrix * vec4(vVertex.xyz, 1.0f); "
                                    "}";

static const char *szFlatShaderFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "uniform vec4 vColor;"
    "void main(void) "
    "{ gl_FragColor = vColor; "
    "}";

///////////////////////////////////////////////////////////////////////////////
// ESS_SHADER_SHADED
// Point light, diffuse lighting only
static const char *szShadedVP = "uniform mat4 mvpMatrix;"
                                "attribute vec4 vColor;"
                                "attribute vec4 vVertex;"
                                "varying vec4 vFragColor;"
                                "void main(void) {"
                                "vFragColor = vColor; "
                                " gl_Position = mvpMatrix * vVertex; "
                                "}";

static const char *szShadedFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "varying vec4 vFragColor; "
    "void main(void) { "
    " gl_FragColor = vFragColor; "
    "}";

// ESS_SHADER_DEFAULT_LIGHT
// Simple diffuse, directional, and vertex based light
static const char *szDefaultLightVP = "uniform mat4 mvMatrix;"
                                      "uniform mat4 pMatrix;"
                                      "varying vec4 vFragColor;"
                                      "attribute vec4 vVertex;"
                                      "attribute vec3 vNormal;"
                                      "uniform vec4 vColor;"
                                      "void main(void) { "
                                      " mat3 mNormalMatrix;"
                                      " mNormalMatrix[0] = mvMatrix[0].xyz;"
                                      " mNormalMatrix[1] = mvMatrix[1].xyz;"
                                      " mNormalMatrix[2] = mvMatrix[2].xyz;"
                                      " vec3 vNorm = normalize(mNormalMatrix * vNormal);"
                                      " vec3 vLightDir = vec3(0.0, 0.0, 1.0); "
                                      " float fDot = max(0.0, dot(vNorm, vLightDir)); "
                                      " vFragColor.rgb = vColor.rgb * fDot;"
                                      " vFragColor.a = vColor.a;"
                                      " mat4 mvpMatrix;"
                                      " mvpMatrix = pMatrix * mvMatrix;"
                                      " gl_Position = mvpMatrix * vVertex; "
                                      "}";

static const char *szDefaultLightFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "varying vec4 vFragColor; "
    "void main(void) { "
    " gl_FragColor = vFragColor; "
    "}";

//ESS_SHADER_POINT_LIGHT_DIFF
// Point light, diffuse lighting only
static const char *szPointLightDiffVP = "uniform mat4 mvMatrix;"
                                        "uniform mat4 mvpMatrix;"
                                        "uniform vec3 vLightPos;"
                                        "uniform vec4 vColor;"
                                        "attribute vec4 vVertex;"
                                        "attribute vec3 vNormal;"
                                        "varying vec4 vFragColor;"
                                        "void main(void) { "
                                        " mat3 mNormalMatrix;"
                                        " mNormalMatrix[0] = normalize(mvMatrix[0].xyz);"
                                        " mNormalMatrix[1] = normalize(mvMatrix[1].xyz);"
                                        " mNormalMatrix[2] = normalize(mvMatrix[2].xyz);"
                                        " vec3 vNorm = normalize(mNormalMatrix * vNormal);"
                                        " vec4 ecPosition;"
                                        " vec3 ecPosition3;"
                                        " ecPosition = mvMatrix * vVertex;"
                                        " ecPosition3 = ecPosition.xyz /ecPosition.w;"
                                        " vec3 vLightDir = normalize(vLightPos - ecPosition3);"
                                        " float fDot = max(0.0, dot(vNorm, vLightDir)); "
                                        " vFragColor.rgb = vColor.rgb * fDot;"
                                        " vFragColor.a = vColor.a;"
                                        " gl_Position = mvpMatrix * vVertex; "
                                        "}";

static const char *szPointLightDiffFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "varying vec4 vFragColor; "
    "void main(void) { "
    " gl_FragColor = vFragColor; "
    "}";

//ESS_SHADER_TEXTURE_REPLACE
// Just put the texture on the polygons
static const char *szTextureReplaceVP = "uniform mat4 mvpMatrix;"
                                        "attribute vec4 vVertex;"
                                        "attribute vec2 vTexCoord0;"
                                        "varying vec2 vTex;"
                                        "void main(void) "
                                        "{ vTex = vTexCoord0;"
                                        " gl_Position = mvpMatrix * vVertex; "
                                        "}";

static const char *szTextureReplaceFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "varying vec2 vTex;"
    "uniform sampler2D textureUnit0;"
    "void main(void) "
    "{ gl_FragColor = texture2D(textureUnit0, vTex); "
    "}";

// Just put the texture on the polygons
static const char *szTextureRectReplaceVP = "uniform mat4 mvpMatrix;"
                                            "attribute vec4 vVertex;"
                                            "attribute vec2 vTexCoord0;"
                                            "varying vec2 vTex;"
                                            "void main(void) "
                                            "{ vTex = vTexCoord0;"
                                            " gl_Position = mvpMatrix * vVertex; "
                                            "}";

static const char *szTextureRectReplaceFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "varying vec2 vTex;"
    "uniform sampler2DRect textureUnit0;"
    "void main(void) "
    "{ gl_FragColor = texture2DRect(textureUnit0, vTex); "
    "}";

//ESS_SHADER_TEXTURE_MODULATE
// Just put the texture on the polygons, but multiply by the color (as a unifomr)
static const char *szTextureModulateVP = "uniform mat4 mvpMatrix;"
                                         "attribute vec3 vVertex;"
                                         "attribute vec2 vTexCoord0;"
                                         "varying vec2 vTex;"
                                         "void main(void) "
                                         "{ vTex = vTexCoord0;"
                                         " gl_Position = mvpMatrix * vec4(vVertex.xyz, 1.0); "
                                         "}";

static const char *szTextureModulateFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "varying vec2 vTex;"
    "uniform sampler2D textureUnit0;"
    "uniform vec4 vColor;"
    "void main(void) "
    "{ gl_FragColor = vColor * texture2D(textureUnit0, vTex); "
    "}";

//ESS_SHADER_TEXTURE_POINT_LIGHT_DIFF
// Point light (Diffuse only), with texture (modulated)
static const char *szTexturePointLightDiffVP = "uniform mat4 mvMatrix;"
                                               "uniform mat4 pMatrix;"
                                               "uniform vec3 vLightPos;"
                                               "uniform vec4 vColor;"
                                               "attribute vec4 vVertex;"
                                               "attribute vec3 vNormal;"
                                               "varying vec4 vFragColor;"
                                               "attribute vec2 vTexCoord0;"
                                               "varying vec2 vTex;"
                                               "void main(void) { "
                                               " mat3 mNormalMatrix;"
                                               " mNormalMatrix[0] = normalize(mvMatrix[0].xyz);"
                                               " mNormalMatrix[1] = normalize(mvMatrix[1].xyz);"
                                               " mNormalMatrix[2] = normalize(mvMatrix[2].xyz);"
                                               " vec3 vNorm = normalize(mNormalMatrix * vNormal);"
                                               " vec4 ecPosition;"
                                               " vec3 ecPosition3;"
                                               " ecPosition = mvMatrix * vVertex;"
                                               " ecPosition3 = ecPosition.xyz /ecPosition.w;"
                                               " vec3 vLightDir = normalize(vLightPos - ecPosition3);"
                                               " float fDot = max(0.0, dot(vNorm, vLightDir)); "
                                               " vFragColor.rgb = vColor.rgb * fDot;"
                                               " vFragColor.a = vColor.a;"
                                               " vTex = vTexCoord0;"
                                               " mat4 mvpMatrix;"
                                               " mvpMatrix = pMatrix * mvMatrix;"
                                               " gl_Position = mvpMatrix * vVertex; "
                                               "}";

static const char *szTexturePointLightDiffFP =
#ifdef OPENGL_ES
    "precision mediump float;"
#endif
    "varying vec4 vFragColor;"
    "varying vec2 vTex;"
    "uniform sampler2D textureUnit0;"
    "void main(void) { "
    " gl_FragColor = vFragColor * texture2D(textureUnit0, vTex);"
    "}";

CGLES3ShaderProgram::CGLES3ShaderProgram()
{
    m_hProgram = GLDebug(glCreateProgram());
    memset(m_hShaders, 0, sizeof(m_hShaders));
}

CGLES3ShaderProgram::~CGLES3ShaderProgram()
{
    for (uint i = 0; i < EShaderType::Count; ++i)
    {
        if (m_hShaders[i] > 0)
        {
            GLDebug(glDetachShader(m_hProgram, m_hShaders[i]));
        }
    }
    GLDebug(glDeleteProgram(m_hProgram));
}

bool CGLES3ShaderProgram::Attach(IShader *shader)
{
    if (shader)
    {
        return AttachSource(shader->GetSource(), shader->GetShaderType()); 
    }
    return false;
}

bool CGLES3ShaderProgram::AttachSource(const char *shaderSrc, EShaderType shaderType)
{
    m_hShaders[shaderType] = GLDebug(glCreateShader(GetGLShaderType(shaderType)));
    GLchar *fsStringPtr[1];
    fsStringPtr[0] = (GLchar *)shaderSrc;
    GLDebug(glShaderSource(m_hShaders[shaderType], 1, (const GLchar **)fsStringPtr, NULL));

    GLint testVal;
    GLDebug(glCompileShader(m_hShaders[shaderType]));
    GLDebug(glGetShaderiv(m_hShaders[shaderType], GL_COMPILE_STATUS, &testVal));
    if (testVal == GL_FALSE)
    {
        char infoLog[1024];
        GLDebug(glGetShaderInfoLog(m_hShaders[shaderType], 1024, NULL, infoLog));
        LogError("The Shader failed to compile with the following error:%s\n", infoLog);
        return false;
    }
    GLDebug(glAttachShader(m_hProgram, m_hShaders[shaderType]));
    return true;
}

void CGLES3ShaderProgram::Detach(EShaderType shaderType)
{
    GLDebug(glDetachShader(m_hProgram, m_hShaders[shaderType]));
}

bool CGLES3ShaderProgram::Link()
{
    GLint testVal;
    GLDebug(glLinkProgram(m_hProgram));
    GLDebug(glGetProgramiv(m_hProgram, GL_LINK_STATUS, &testVal));
    if (testVal == GL_FALSE)
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_hProgram, 1024, NULL, infoLog);
        LogError("The program %d failed to link with the following error:%s\n", m_hProgram, infoLog);
        return false;
    }

    GetShaderUniform();

    return true;
}

void CGLES3ShaderProgram::Bind()
{
    GLDebug(glUseProgram(m_hProgram));

    CShaderProgram::UniformArray::iterator it = m_uniforms.begin();
    for (; it != m_uniforms.end(); ++it)
    {
        Uniform &uniform = it->second;
        if (uniform.IsDirty())
        {
            switch (uniform.m_format)
            {
            case GL_FLOAT:
                GLDebug(glUniform1fv(uniform.m_location, uniform.m_count, (GLfloat *)uniform.m_value));
                break;
            case GL_INT:
                GLDebug(glUniform1iv(uniform.m_location, uniform.m_count, (GLint *)uniform.m_value));
                break;
            case GL_FLOAT_VEC2:
                GLDebug(glUniform2fv(uniform.m_location, uniform.m_count, (GLfloat *)uniform.m_value));
                break;
            case GL_FLOAT_VEC3:
                GLDebug(glUniform3fv(uniform.m_location, uniform.m_count, (GLfloat *)uniform.m_value));
                break;
            case GL_FLOAT_VEC4:
                GLDebug(glUniform4fv(uniform.m_location, uniform.m_count, (GLfloat *)uniform.m_value));
                break;
            case GL_FLOAT_MAT3:
                GLDebug(glUniformMatrix3fv(uniform.m_location, uniform.m_count, GL_FALSE, (GLfloat *)uniform.m_value));
                break;
            case GL_FLOAT_MAT4:
                GLDebug(glUniformMatrix4fv(uniform.m_location, uniform.m_count, GL_FALSE, (GLfloat *)uniform.m_value));
                break;
            default:
                break;
            }
            uniform.Dirty(false);
        }
    }
}

void CGLES3ShaderProgram::GetShaderUniform()
{
    GLint uniformsNum = 0;
    GLDebug(glGetProgramiv(m_hProgram, GL_ACTIVE_UNIFORMS, &uniformsNum));
    if (uniformsNum > 0)
    {
        GLint maxLength;
        GLDebug(glGetProgramiv(m_hProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength));
        char *name = new char[maxLength];
        
        for (int i = 0; i < uniformsNum; ++i)
        {
            Uniform uniform;

            GLenum type;
            GLsizei nameLength;
            GLDebug(glGetActiveUniform(m_hProgram, i, maxLength, &nameLength, &uniform.m_count, &type, name));
            uniform.m_format = type;
            std::string sname = Replace(name, "[0]", "");
            strncpy(uniform.m_name, sname.c_str(), MAX_FILE_NAME - 1);
            uniform.m_size = GetUniformTypeSize(uniform.m_format) * uniform.m_count;

            uniform.m_location = glGetUniformLocation(m_hProgram, uniform.m_name);

            m_uniforms[uniform.m_location] = uniform;
        }
        delete[]name;
    }
}
void CGLES3ShaderProgram::BindAttributeLocation(int argc, ...)
{
    va_list argp;

    char *name;

    va_start(argp, argc);

    for (int i = 0; i < argc; ++i)
    {
        name = va_arg(argp, char *);
        GLDebug(glBindAttribLocation(m_hProgram, i, name));
    }
    va_end(argp);
}

void CGLES3ShaderProgram::BindAttributeLocation(int index, const char *name)
{
    GLDebug(glBindAttribLocation(m_hProgram, index, name));
}
void CGLES3ShaderProgram::CreateStandShader(E_STAND_SHADER standShader)
{
    switch (standShader)
    {
    case ESS_SHADER_IDENTITY:
        AttachSource(szIdentityShaderVP, EShaderType::Vertex);
        AttachSource(szIdentityShaderFP, EShaderType::Fragment);
        BindAttributeLocation(1, "vVertex");
        break;
    case ESS_SHADER_FLAT:
        AttachSource(szFlatShaderVP, EShaderType::Vertex);
        AttachSource(szFlatShaderFP, EShaderType::Fragment);
        BindAttributeLocation(1, "vVertex");
        break;
    case ESS_SHADER_SHADED:
        AttachSource(szShadedVP, EShaderType::Vertex);
        AttachSource(szShadedFP, EShaderType::Fragment);
        BindAttributeLocation(2, "vVertex", "vColor");
        break;
    case ESS_SHADER_DEFAULT_LIGHT:
        AttachSource(szDefaultLightVP, EShaderType::Vertex);
        AttachSource(szDefaultLightFP, EShaderType::Fragment);
        BindAttributeLocation(2, "vVertex", "vNormal");
        break;
    case ESS_SHADER_POINT_LIGHT_DIFF:
        AttachSource(szPointLightDiffVP, EShaderType::Vertex);
        AttachSource(szPointLightDiffFP, EShaderType::Fragment);
        BindAttributeLocation(2, "vVertex", "vNormal");
        break;
    case ESS_SHADER_TEXTURE_REPLACE:
        AttachSource(szTextureReplaceVP, EShaderType::Vertex);
        AttachSource(szTextureReplaceFP, EShaderType::Fragment);
        BindAttributeLocation(2, "vVertex", "vTexCoord0");
        break;
    case ESS_SHADER_TEXTURE_MODULATE:
        AttachSource(szTextureModulateVP, EShaderType::Vertex);
        AttachSource(szTextureModulateFP, EShaderType::Fragment);
        BindAttributeLocation(2, "vVertex", "vTexCoord1");
        break;
    case ESS_SHADER_TEXTURE_POINT_LIGHT_DIFF:
        AttachSource(szTexturePointLightDiffVP, EShaderType::Vertex);
        AttachSource(szTexturePointLightDiffFP, EShaderType::Fragment);
        BindAttributeLocation(3, "vVertex", "vNormal", "vTexCoord0");
        break;
    case ESS_SHADER_TEXTURE_RECT_REPLACE:
        AttachSource(szTextureRectReplaceVP, EShaderType::Vertex);
        AttachSource(szTextureRectReplaceFP, EShaderType::Fragment);
        BindAttributeLocation(2, "vVertex", "vTexCoord0");
        break;
    default:
        break;
    }

    Link();
}

} // namespace magic
