#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace ProtoEngine
{
 
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Use();

	void SetVec4(std::string& name, float x, float y, float z, float w);
	void SetMat4(std::string& name, const glm::mat4& mat);

private:
	unsigned int programID;
	unsigned int CompileShader(unsigned int type, const char* source);
#ifdef DEBUG
	void PrintShaderInfoLog(GLuint shader);
#endif // DEBUG
};

} // namespace ProtoEngine

