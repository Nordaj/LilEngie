#vert
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

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
uniform PointLight uPointLights[8];
uniform SpotLight uSpotLights[8];
uniform DirLight uDirLights[4];
uniform vec3 uAmbient;
uniform sampler2D uMainTex;

in vec3 iNormal;
in vec3 iFragPos;
in vec2 iUv;

out vec4 color;

void main()
{
	vec3 norm = normalize(iNormal);

	//Calculate point lights (i know its not physically accurate, will get attenuation later)
	vec3 combinedPointLights = vec3(0, 0, 0);
	for (int i = 0; i < 8; i++)
	{
		//Dont use if i am empty
		if (uPointLights[i].intensity == 0)
			continue;

		//Calculate light dir
		vec3 lightDir = normalize(uPointLights[i].position - iFragPos);

		//Get distance
		float dist = distance(uPointLights[i].position, iFragPos);

		//Get the brightness
		float val = (dot(norm, lightDir) * uPointLights[i].intensity) / dist;
		if (val < 0) val = 0;

		//Calculate color
		vec3 c = val * uPointLights[i].color;

		//Add to combined lights
		combinedPointLights += c;
	}

	//Caclulate spot lights 
	vec3 combinedSpotLights = vec3(0, 0, 0);
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

			//Get the brightness
			val = (dot(norm, lightDir) * uSpotLights[i].intensity) / dist;
			if (val < 0) val = 0;
		}
		else
		{
			//Out of the zone
			val = 0;
		}

		//Calculate color
		vec3 c = val * uSpotLights[i].color;

		//Add to combined lights
		combinedPointLights += c;
	}

	//Calculate directional lights
	vec3 combinedDirLights = vec3(0, 0, 0);
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
		combinedDirLights += c;
	}

	//Combine all lights
	vec3 combinedLights = combinedDirLights + combinedPointLights + uAmbient;

	//Multiply color
	vec3 c = uColor.rgb * combinedLights * texture(uMainTex, iUv).rgb;

	//Output
	color = vec4(c, uColor.a);
}
