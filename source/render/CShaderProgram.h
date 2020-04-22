#ifndef _MAGIC_C_SHADER_PROGRAM_H_
#define _MAGIC_C_SHADER_PROGRAM_H_

#include "base/magicDef.h"
#include "base/magicType.h"
#include "render/IShaderProgram.h"

#include <map>
#include <string.h>

namespace magic
{
class CShaderProgram : public IShaderProgram
{
public:
    struct Uniform
    {
        char m_name[MAX_FILE_NAME];
        int m_location;
        int m_format;
        int m_count;
        int m_size;
        byte *m_value;
        bool m_bDirty;
        Uniform()
            : m_location(0), m_format(0), m_count(0), m_size(0), m_value(nullptr), m_bDirty(false)
        {
            memset(m_name, 0, sizeof(m_name));
        }
        ~Uniform()
        {
            if (m_value)
                free(m_value);
        }

        void SetValue(const void *value)
        {
            if (value && m_size > 0)
            {
                if (!m_value)
                {
                    m_value = (byte *)malloc(m_size);
                }
                memcpy(m_value, value, m_size);
                Dirty(true);
            }
        }
        inline void Dirty(bool bDirty) { m_bDirty = bDirty; }
        inline bool IsDirty() const { return m_bDirty; }
    };
    typedef std::map<int, Uniform> UniformArray;
    CShaderProgram();
    virtual ~CShaderProgram();

    virtual void SetUniform(const char *name, void *value);
    virtual void SetUniform(int location, void *value);
    virtual int GetUniformLocation(const char *name) const;
    virtual int GetUniformTypeSizeByLocation(int location) const;

protected:
    UniformArray m_uniforms;
};
} // namespace magic

#endif
