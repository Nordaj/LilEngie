#vert
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 uv;

out vec2 iUv;

void main()
{
	gl_Position = position;
	iUv = uv;
}

#surf
#version 330 core

uniform vec4 uColor;
uniform sampler2D uCharacters;
uniform float uCutoff;
uniform float uBorderWidth;
uniform vec4 uBorderColor;
uniform float uGlowAmount;
uniform vec4 uGlowColor;

in vec2 iUv;

out vec4 color;

void main()
{
	vec4 c = uColor;

	float character = texture(uCharacters, iUv).a;

	if (character < uCutoff)
	{
		if (character > uCutoff - uBorderWidth)
			c = uBorderColor;
		else
			c = vec4(0, 0, 0, 0);

		c += uGlowColor * uGlowAmount * character;
	}

	color = c;
}
