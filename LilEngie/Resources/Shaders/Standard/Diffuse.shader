#vert
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out vec3 iFragPos;
out vec2 iUv;
out mat3 iTBN;

uniform mat4 uMVPMat;
uniform mat4 uModelMat;

void main()
{
	gl_Position = uMVPMat * position;
	iUv = uv;
	iFragPos = vec3(uModelMat * position);

	iTBN = glm::mat3(
		normalize(vec3(uModelMat * vec4(tangent, 0))),
		normalize(vec3(uModelMat * vec4(cross(normal, tangent), 0))),
		normalize(vec3(uModelMat * vec4(normal, 0)))
	);
}

#surf
#version 330 core

//TODO
//I need to somehow split diffuse and specular combined lights. Diffuse is multiplied by unlit color. Specular is added. 
//Then I need to clean everything. all light types should correctly have specular lighting and clean up any messieness

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

in vec3 iFragPos;
in vec2 iUv;
in mat3 iTBN;

out vec4 color;

vec3 CalcPointLights(vec3 norm, vec3 viewDir);
vec3 CalcSpotLights(vec3 norm, vec3 viewDir);
vec3 CalcDirLights(vec3 norm);
vec3 CalcPointLightsSpec(vec3 norm, vec3 viewDir);
//TODO: spec for rest of light types

void main()
{
	//Normal vec in tangent space
	vec3 tNormal = texture(uNormalTex, iUv).rgb;

	//If im empty, use blue
	if (textureSize(uNormalTex, 0).x == 1)
		tNormal = vec3(0.5, 0.5, 1);

	//Use correct scale (-1 - 1)
	tNormal = (tNormal * 2) - 1;

	//Multiply r and g by normal scale (not all 3 otherwise itll go back after normalized)
	tNormal.r *= uNormal;
	tNormal.g *= uNormal;

	//Transform normal map vec to world space
	vec3 norm = normalize(iTBN * tNormal);

	//Get view direction for lighting stuff
	vec3 viewDir = normalize(uCamPos - iFragPos);

	//Diffuse lighting calculations
	vec3 pointLights = CalcPointLights(norm, viewDir);
	vec3 spotLights = CalcSpotLights(norm, viewDir);
	vec3 dirLights = CalcDirLights(norm);
	vec3 lightColor = dirLights + spotLights + pointLights + uAmbient;

	//Specular lighting calculations
	vec3 specLight = vec3(0, 0, 0);
	specLight += CalcPointLightsSpec(norm, viewDir);

	//Multiply color
	vec3 c = (uColor.rgb * lightColor * texture(uMainTex, iUv).rgb) + specLight;

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

		//Get the brightness
		float val = dot(lightDir, norm) * attenuation * uPointLights[i].intensity;
		if (val < 0) val = 0;

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

vec3 CalcPointLightsSpec(vec3 norm, vec3 viewDir)
{
	vec3 combined = vec3(0, 0, 0);
	for (int i = 0; i < 8; i++)
	{
		//Continue if i am not an active light
		if (uPointLights[i].intensity == 0)
			continue;

		//Get direction from light to frag position
		vec3 lightDir = normalize(iFragPos - uPointLights[i].position);

		//Get distance
		float dist = distance(uPointLights[i].position, iFragPos);

		//Get attenuation
		float attenuation = Attenuation(dist);

		//Reflect off of the surface
		vec3 reflectDir = reflect(lightDir, norm);

		//Get dot product of dir from eye to frag and reflected dir
		float spec = dot(viewDir, reflectDir);
		if (spec < 0) spec = 0;

		//Process to consider any factors that needs to affect it
		spec *= attenuation * uSpecularity * texture(uSpecularityTex, iUv).r * uPointLights[i].intensity;

		//Get into color based on light color
		vec3 specColor = uPointLights[i].color * spec;

		//Add to combined
		combined += specColor;
	}
	return combined;
}
