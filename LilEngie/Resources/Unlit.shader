#vert
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 uMVPMat;

void main()
{
	gl_Position = uMVPMat * position;
}

#surf
#version 330 core

out vec4 color;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}
