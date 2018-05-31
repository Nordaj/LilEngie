#include <string>

class Shader
{
private:
	unsigned int shaderID;

public:
	std::string vertex;
	std::string surface;

	Shader();

	unsigned int GetID();
	void Setup(std::string vert, std::string surf);
	void SetCurrent();
};
