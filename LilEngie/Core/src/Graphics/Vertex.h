#pragma once

#include <glm/common.hpp>

class Vertex
{
public:
	union
	{
		float values[11];

		struct
		{
			glm::vec3 position;
			glm::vec2 uv;
			glm::vec3 normal;
			glm::vec3 tangent;
		};

		struct
		{
			float
				xPos, yPos, zPos,
				uTex, vTex,
				xNorm, yNorm, zNorm,
				xTan, yTan, zTan;
		};
	};
};
