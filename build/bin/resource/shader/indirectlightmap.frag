#version 300 es
precision mediump float;

uniform sampler2D tGPosition;
uniform sampler2D tGNormal;
uniform sampler2D tGColor;

uniform sampler2D tRSMFlux;
uniform sampler2D tRSMPosition;
uniform sampler2D tRSMNormal;

uniform sampler2D tRandNum;

uniform lowp sampler2DShadow tDepth;

uniform mat4 vplViewMatrix;
uniform mat4 vplProjMatrix;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform int samplingColCount;

in vec2 texCoord;

out vec4 fragColor;

float lookup(vec4 vShadowCoord, float x, float y)
{
    float pixelSize = 0.001;
    vec4 offset = vec4(x * pixelSize * vShadowCoord.w, y * pixelSize * vShadowCoord.w, 0.0, 0.0);
    return textureProj(tDepth, vShadowCoord + offset);
}

void calcIndirectLight(int i, vec2 texCoordInValBegin, float stepRate, float samplingColCount, vec3 gPosition, vec3 gNormal, inout vec3 indirectLC, inout float shelter)
{
	float y = floor(float(i) / samplingColCount);
	float x = float(i) - y * samplingColCount;
	//vec2 tex = vec2(texCoordInValBegin.x + stepRate * x, texCoordInValBegin.y + stepRate * y);

	vec4 rand = texture(tRandNum, vec2(x / (samplingColCount - 1.0), y / (samplingColCount - 1.0)));
	vec2 tex = vec2(texCoordInValBegin.x + stepRate * (rand.x * 2.0 - 1.0), texCoordInValBegin.y + stepRate * (rand.y * 2.0 - 1.0));

	vec4 valC = texture(tRSMFlux, tex);
	vec4 valP = texture(tRSMPosition, tex);
	vec4 valN = texture(tRSMNormal, tex);
	vec3 mainLightDir = normalize(-lightDir);
    float valRate = max(dot(mainLightDir, valN.xyz), 0.0);
	
	vec3 shootDir = normalize(gPosition - valP.xyz);
	
    vec3 shootColor = valC.rgb * valRate * max(dot(shootDir, valN.xyz), 0.0);// / 3.14;
	
	float dis = max(distance(valP.xyz, gPosition), 1.0);
    vec3 irradiance = shootColor * max(dot(gNormal, -shootDir), 0.0) / (pow(dis, 0.0) + 0.0 * pow(dis, 2.0) + 1.0 * dis + 0.0);
	
	indirectLC += irradiance;
	
	float v = (1.0 - step(0.0, dot(shootDir, valN.xyz))) * step(0.0, dot(-shootDir, gNormal.xyz));
    shelter += max(dot(-shootDir, gNormal.xyz), 0.0) / (dis * dis);
}

void calc(int i, float samplingColCount, vec4 gPosition, vec3 gNormal, inout vec3 indirectLC)
{
    float y = floor(float(i) / samplingColCount);
    float x = float(i) - y * samplingColCount;
    
    vec4 rand = texture(tRandNum, vec2(x / (samplingColCount - 1.0), y / (samplingColCount - 1.0)));
    vec4 randPosition = gPosition + rand * 256.0 - 128.0;
    vec4 posInVplMap = vplProjMatrix * vplViewMatrix * vec4(randPosition.xyz, 1.0);
    vec2 tex = (0.5 * posInVplMap.xy + 0.5) / posInVplMap.w;
 
    vec4 valC = texture(tRSMFlux, tex);
    vec4 valP = texture(tRSMPosition, tex);
    vec4 valN = texture(tRSMNormal, tex);
    vec3 mainLightDir = normalize(-lightDir);
    float valRate = max(dot(mainLightDir, valN.xyz), 0.0);
    
    vec3 shootDir = normalize(gPosition.xyz - valP.xyz);

    vec3 shootColor = 2.0 * valC.rgb * lightColor * valRate * (max(dot(shootDir, valN.xyz), 0.0)) / 3.14;
    
    float dis = max(distance(valP.xyz, gPosition.xyz), 1.0);
    vec3 irradiance = shootColor * max(dot(gNormal, -shootDir), 0.0) / (0.0 * pow(dis, 4.0) + 0.0 * pow(dis, 2.0) + 1.0 * dis + 0.0);
    
    indirectLC += irradiance;
}

void main()
{
	vec4 gPosition = texture(tGPosition, texCoord);
	vec3 gNormal = texture(tGNormal, texCoord).xyz;
	vec4 gColor = texture(tGColor, texCoord);

	float dataflag = step(0.001, dot(gNormal.xyz, gNormal.xyz));
    
	vec4 posInValMap = vplProjMatrix * vplViewMatrix * gPosition;
    vec4 texCoordInVM = 0.5 * posInValMap + 0.5;
    //vec2 texCoordInValMap = (0.5 * posInValMap.xy + 0.5) / posInValMap.w;
    
    float shadow = textureProj(tDepth, texCoordInVM);
    float x, y;
    float sum = 0.0;
    for (x = -2.0; x <= 2.0; x += 2.0)
        for (y = -2.0; y <= 2.0; y += 2.0)
            sum += lookup(texCoordInVM, x, y);
    //float shadow = sum * 0.11;

	float samplingRate = 0.2;

    //vec2 texCoordInValBegin = texCoordInValMap;// - 0.5 * samplingRate;

	//float stepRate = samplingRate / float(samplingColCount);
	
	int samplingTotalNum = int(float(samplingColCount * samplingColCount) * dataflag) ;
	vec3 indirectLC = vec3(0.0, 0.0, 0.0);
	float shelter = 0.0;
	for (int i = 0; i< samplingTotalNum; ++i)
	{
		//calcIndirectLight(i, texCoordInValBegin, samplingRate, float(samplingColCount), gPosition.xyz, gNormal.xyz, indirectLC, shelter);
        calc(i, float(samplingColCount), gPosition, gNormal, indirectLC);
    }

	//shelter /= max(float(samplingTotalNum), 1.0);
	fragColor = vec4(indirectLC, shadow );
}
