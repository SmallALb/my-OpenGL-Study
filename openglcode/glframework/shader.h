#pragma once
#include "../globa/base.h"
#include "../globa/math.h"
class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void setFloat(const std::string& name, float value);
	void setVector3(const std::string& name, float x, float y, float z);
	void setVector3(const std::string& name, const float* values);
	void setInt(const std::string& name, int value);
	void setMat4(const std::string& name, glm::mat4 mat);
	void begin();
	void end();
private:
	void checkShaderErrors(GLuint target, std::string type);

	unsigned int mProgram{ 0 };
};