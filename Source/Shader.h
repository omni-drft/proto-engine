#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
private:
	unsigned int programID;
	unsigned int CompileShader(unsigned int type, const char* source);
};

} // namespace ProtoEngine

