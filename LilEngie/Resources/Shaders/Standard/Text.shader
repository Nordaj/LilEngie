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

in vec2 iUv;

out vec4 color;

void main()
{
	float character = texture(uCharacters, iUv).r;

	color = uColor * character;
}
