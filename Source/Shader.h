/* ============================ FILE PURPOSE ================================
* 
*	 This file contains the class definition for the Shader class.
*  Shader is a class that compiles and links vertex and fragment shaders.
*  It also provides functions to set uniform variables in the shaders 
*  and debug all shader related issues.
* 
========================================================================== */

#pragma once

// Link OpenGL Extension Wrangler
#include <GL/glew.h>

// Link GLFW for window creation and input handling
#include <GLFW/glfw3.h>

// Link GLM for algebra
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Link standard libraries
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace ProtoEngine
{

/// <summary>
/// Class to handle shader compilation, linking and usage
/// </summary>
class Shader
{
public:
	/// <summary>
	/// Constructor for the shader class that compiles and links the shaders
	/// </summary>
	/// <param name="vertexPath">- path to vertex shader file (relative to build file)</param>
	/// <param name="fragmentPath">- path to fragment shader file (relative to build file)</param>
	Shader(const char* vertexPath, const char* fragmentPath);

	/// <summary>
	/// Destructor for the shader class that deletes the shader program
	/// </summary>
	~Shader();

	/// <summary>
	/// Function to use the shader program in the rendering pipeline
	/// </summary>
	void Use();

	/// <summary>
	/// Function to set a 4D vector uniform in the shader
	/// </summary>
	/// <param name="name">- name of parameter</param>
	void SetVec4(std::string& name, float x, float y, float z, float w);

	/// <summary>
	/// Function to set a 4x4 matrix uniform in the shader
	/// </summary>
	void SetMat4(std::string& name, const glm::mat4& mat);

private:

	/// <summary>
	/// Variable to store the shader program ID
	/// </summary>
	unsigned int programID;

	/// <summary>
	/// Function to compile a shader
	/// </summary>
	/// <param name="type">- shader type</param>
	/// <param name="source">- path to shader file</param>
	/// <returns>shader ID</returns>
	unsigned int CompileShader(unsigned int type, const char* source);

#ifdef DEBUG
	/// <summary>
	/// Function to print shader log
	/// </summary>
	/// <param name="shader">- shader ID</param>
	void PrintShaderInfoLog(GLuint shader);
#endif // DEBUG
};

} // namespace ProtoEngine

