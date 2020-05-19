#version 300 es
precision mediump float;

//uniform sampler2D tRandNum;

uniform sampler2D tGPosition;
uniform sampler2D tGNormal;
uniform sampler2D tGColor;

uniform sampler2D tRSMFlux;
uniform sampler2D tRSMPosition;
uniform sampler2D tRSMNormal;

uniform mat4 viewMatrix;

uniform vec3 lightDir;
uniform vec3 lightColor;

uniform int samplingColCount;

in vec2 texCoord;
in vec3 position;

out vec4 fragColor;

void calcIndirectLight(int i, vec2 texCoordInValBegin, float stepRate, float samplingColCount, vec3 gPosition, vec3 gNormal, inout vec3 indirectLC, inout float shelter)
{
	float y = floor(float(i) / samplingColCount);
	float x = float(i) - y * samplingColCount;
	vec2 tex = vec2(texCoordInValBegin.x + stepRate * x, texCoordInValBegin.y + stepRate * y);

	//vec4 rand = texture(tRandNum, vec2(x / (samplingColCount - 1.0), y / (samplingColCount - 1.0)));
	//vec2 tex = vec2(texCoordInValBegin.x + stepRate * (rand.x * 2.0 - 1.0), texCoordInValBegin.y + stepRate * (rand.y * 2.0 - 1.0));

	vec4 valC = texture(tRSMFlux, tex);
	vec4 valP = texture(tRSMPosition, tex);
	vec4 valN = texture(tRSMNormal, tex);
	float valRate = max(dot(-lightDir, valN.xyz), 0.0);
	
	vec3 shootDir = normalize(gPosition - valP.xyz);
	
	vec3 shootColor = valC.rgb * valRate * max(dot(shootDir, valN.xyz), 0.0) / 3.14;
	
	float dis = max(distance(valP.xyz, gPosition), 1.0);
	vec3 irradiance = shootColor * max(dot(gNormal, -shootDir), 0.0) / (pow(dis, 4.0));// + 2.0 * pow(dis, 2.0) + 3.0 * dis + 4.0);
	
	indirectLC += irradiance;
	
	float v = (1.0 - step(0.0, dot(shootDir, valN.xyz))) * step(0.0, dot(-shootDir, gNormal.xyz));
    shelter += max(dot(-shootDir, gNormal.xyz), 0.0);// / (dis * dis);	
}


void main()
{
	vec4 gPosition = texture(tGPosition, texCoord);
	vec4 gNormal = texture(tGNormal, texCoord);

	float dataflag = step(0.001, dot(gNormal.xyz, gNormal.xyz));

	
	vec3 mainLightDir = -normalize(lightDir);//normalize(lightPosition - position.xyz);
	
	vec4 posInValMap = viewMatrix * gPosition;
	vec2 texCoordInValMap = posInValMap.xy / posInValMap.w;

	float samplingRate = 0.1;

	vec2 texCoordInValBegin = texCoordInValMap;// - 0.5 * samplingRate;

	float stepRate = samplingRate / float(samplingColCount);
	
	int samplingTotalNum = int(float(samplingColCount * samplingColCount) * dataflag);
	vec3 indirectLC = vec3(0.0, 0.0, 0.0);
	float shelter = 0.0;
	for (int i = 0; i< samplingTotalNum; ++i)
	{
		calcIndirectLight(i, texCoordInValBegin, samplingRate, float(samplingColCount), gPosition.xyz, gNormal.xyz, indirectLC, shelter);
	}

	shelter /= max(float(samplingTotalNum), 1.0);
	fragColor = vec4(indirectLC, 1.0 - shelter);
    fragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
