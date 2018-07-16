#vert
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out vec3 iNormal;
out vec3 iFragPos;
out vec2 iUv;

uniform mat4 uMVPMat;
uniform mat4 uModelMat;

void main()
{
	gl_Position = uMVPMat * position;
	iUv = uv;
	iNormal = mat3(transpose(inverse(uModelMat))) * normal;
	iFragPos = vec3(uModelMat * position);
}

#surf
#version 330 core

struct PointLight
{
	vec3 position;
	vec3 color;
	float intensity;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float intensity;
	float angle;
};

struct DirLight
{
	vec3 direction;
	vec3 color;
	float intensity;
};

uniform vec4 uColor;
uniform float uSpecularity;
uniform float uNormal;
uniform PointLight uPointLights[8];
uniform SpotLight uSpotLights[8];
uniform DirLight uDirLights[4];
uniform vec3 uAmbient;
uniform vec3 uCamPos;
uniform sampler2D uMainTex;
uniform sampler2D uSpecularityTex;
uniform sampler2D uNormalTex;

in vec3 iNormal;
in vec3 iFragPos;
in vec2 iUv;

out vec4 color;

vec3 CalcPointLights(vec3 norm, vec3 viewDir);
vec3 CalcSpotLights(vec3 norm, vec3 viewDir);
vec3 CalcDirLights(vec3 norm);

void main()
{
	//Lighting calculations
	vec3 norm = normalize(iNormal);
	vec3 viewDir = normalize(uCamPos - iFragPos);
	vec3 pointLights = CalcPointLights(norm, viewDir);
	vec3 spotLights = CalcSpotLights(norm, viewDir);
	vec3 dirLights = CalcDirLights(norm);
	vec3 lightColor = dirLights + spotLights + pointLights + uAmbient;

	//Multiply color
	vec3 c = uColor.rgb * lightColor * texture(uMainTex, iUv).rgb;

	//Output
	color = vec4(c, uColor.a);
}

float Attenuation(float distance, float constant = 1, float lin = 1, float quadratic = 2)
{
	//Light attenuation formula: 1 / Kc + KlD + KqD^2
	///Kc = constant
	///Kl = linear
	///Kq = quadratic
	///D  = distance
	//Source: http://politecnicacuenca.com/light-attenuation/

	return 1 / (constant + (lin * distance) + (quadratic * (distance * distance)));
}

vec3 CalcPointLights(vec3 norm, vec3 viewDir)
{
	vec3 combined = vec3(0, 0, 0);
	for (int i = 0; i < 8; i++)
	{
		//Dont use if i am empty
		if (uPointLights[i].intensity == 0)
			continue;

		//Calculate light dir
		vec3 lightDir = normalize(uPointLights[i].position - iFragPos);

		//Get distance
		float dist = distance(uPointLights[i].position, iFragPos);

		//Get attenuation
		float attenuation = Attenuation(dist);

		//Calculate specularity
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = dot(viewDir, reflectDir);
		if (spec < 0) spec = 0;
		spec *= attenuation * uSpecularity * texture(uSpecularityTex, iUv).r;

		//Get the brightness
		float val = dot(lightDir, norm) * attenuation * uPointLights[i].intensity;
		if (val < 0) val = 0;

		//Add specularity
		val += spec; //I think this is what i do...

		//Calculate color
		vec3 c = val * uPointLights[i].color;

		//Add to combined lights
		combined += c;
	}
	return combined;
}

vec3 CalcSpotLights(vec3 norm, vec3 viewDir)
{
	vec3 combined = vec3(0, 0, 0);
	for (int i = 0; i < 8; i++)
	{
		//Dont use if i am empty
		if (uSpotLights[i].intensity == 0)
			continue;

		//Calculate light dir
		vec3 lightDir = normalize(uSpotLights[i].position - iFragPos);

		//Calculate angle
		float angle = dot(lightDir, normalize(-uSpotLights[i].direction));

		float val = 0;
		if (angle > uSpotLights[i].angle)
		{
			//In the zone
			//Get distance
			float dist = distance(uSpotLights[i].position, iFragPos);

			//Get attenuation
			float attenuation = Attenuation(dist);

			//Calculate specularity
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = dot(viewDir, reflectDir);
			if (spec < 0) spec = 0;
			spec *= attenuation * uSpecularity * texture(uSpecularityTex, iUv).r;

			//Get the brightness
			val = (dot(norm, lightDir) * attenuation * uSpotLights[i].intensity) / dist;
			if (val < 0) val = 0;
			val += spec;
		}
		else
		{
			//Out of the zone
			val = 0;
		}

		//Calculate color
		vec3 c = val * uSpotLights[i].color;

		//Add to combined lights
		combined += c;
	}
	return combined;
}

vec3 CalcDirLights(vec3 norm)
{
	vec3 combined = vec3(0, 0, 0);
	for (int i = 0; i < 4; i++)
	{
		//Dont use if i am empty
		if (uDirLights[i].intensity == 0)
			continue;

		//Get the brightness
		float val = dot(norm, normalize(-uDirLights[i].direction)) * uDirLights[i].intensity;
		if (val < 0) val = 0;

		//Calculate color
		vec3 c = val * uDirLights[i].color;

		//Add to combined lights
		combined += c;
	}
	return combined;
}
