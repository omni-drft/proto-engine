#include "Shader.h"

ProtoEngine::Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// Read shader files
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);
	std::stringstream vertexStream, fragmentStream;

	// Read file contents into string streams
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();
	
	// Convert string streams to strings
	std::string vertexCode = vertexStream.str();
	std::string fragmentCode = fragmentStream.str();

	// Convert strings to char arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
		
	// Compile shaders
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

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
		std::cerr << "Shader program linking error:\n" << infoLog << std::endl;
	}

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
		std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
	}

	return shaderID;
}
