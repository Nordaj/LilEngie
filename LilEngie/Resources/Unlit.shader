#vert
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 uMVPMat;

void main()
{
	gl_Position = uMVPMat * vec4(position, 1);
}

#surf
#version 330 core

uniform vec4 uColor;

out vec4 color;

void main()
{
	color = uColor;
}
