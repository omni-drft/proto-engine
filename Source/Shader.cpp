/* ============================== FILE PURPOSE ===============================
* 
*  This file contains the implementation of the Shader class.
* 
=========================================================================== */

#include "Shader.hpp"

ProtoEngine::Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		Log::GetLogger()->error("OpenGL error: {}", error);
	}

	// Read shader files
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);
	std::stringstream vertexStream{}, fragmentStream{};

	error = glGetError();
	if (error != GL_NO_ERROR) {
		Log::GetLogger()->error("OpenGL error: {}", error);
	}

	// Read file contents into string streams
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();
	
	// Convert string streams to strings
	std::string vertexCode{ vertexStream.str() };
	std::string fragmentCode{ fragmentStream.str() };

	// Convert strings to char arrays
	const char* vertexSource{ vertexCode.c_str() };
	const char* fragmentSource{ fragmentCode.c_str() };

	#ifdef SHADER_DEBUG
	std::cout << "Vertex shader source:" << std::endl;
	std::cout << vertexSource << std::endl;
	std::cout << std::endl << "Fragment shader source:" << std::endl;
	std::cout << fragmentSource << std::endl;
	#endif // SHADER_DEBUG

		
	// Compile shaders
	unsigned int vertexShader{ CompileShader(GL_VERTEX_SHADER, vertexSource) };
	unsigned int fragmentShader{ CompileShader(GL_FRAGMENT_SHADER, fragmentSource) };

	// Link shaders
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	// Check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		Log::GetLogger()->error("Shader program linking error: {}", infoLog);
	}
	else
		Log::GetLogger()->info("Shader program linked successfully");

	// Shader info log
	PrintShaderInfoLog(vertexShader);
	PrintShaderInfoLog(fragmentShader);

	// Delete shaders as they are linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

ProtoEngine::Shader::~Shader()
{
		glDeleteProgram(programID);
}

void ProtoEngine::Shader::Use()
{
	glUseProgram(programID);
}

void ProtoEngine::Shader::SetVec4(std::string name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}

void ProtoEngine::Shader::SetVec3(std::string name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}

void ProtoEngine::Shader::SetMat4(std::string name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

unsigned int ProtoEngine::Shader::CompileShader(unsigned int type, const char* source)
{
	unsigned int shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);
	
	// Check for compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		Log::GetLogger()->error("Shader compilation error: {}", infoLog);
	}
	else
		Log::GetLogger()->info("Shader compiled successfully");
	return shaderID;
}

void ProtoEngine::Shader::PrintShaderInfoLog(GLuint shader) {
	int maxLength{};
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
	if (maxLength > 0) {
		char* infoLog{ new char[maxLength] };
		glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);
		Log::GetLogger()->info("Shader info log: {}", infoLog);
		delete[] infoLog;
	}
}