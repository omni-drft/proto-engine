/* ======================== PURPOSE OF FILE ========================
* 
* This file is the entry point for the application. 
*	It creates a window using GLFW and GLEW, 
* and then enters a loop to render the window.
* 
================================================================== */

// Link OpenGL Extension Wrangler
#include <GL/glew.h>

// Link GLFW for window creation and input handling
#include <GLFW/glfw3.h>

// Link GLM for algebra
#include <glm/glm.hpp>

// Link standard libraries
#include <iostream>
#include <Windows.h>
#include <vector>

// Link custom classes
#include "HandleInput.h"
#include "Shader.h"
#include "Window.h"
#include "Object.h"
#include "Vertex.h"

int main()
{


	// ======================== FIRST OBJECT DATA - ONLY TEMPORARY ========================
	// Define the vertices of a rectangle
	std::vector<ProtoEngine::Vertex> vertices{
		{100.0f, 100.0f},   // bottom-left
		{600.0f, 100.0f},   // bottom-right
		{600.0f, 600.0f},   // top-right
		{100.0f, 600.0f}   // top-left
	};

	// Define the indices to form two triangles (making a rectangle)
	std::vector<int> indices {
			0, 1, 2,  // first triangle
			2, 3, 0   // second triangle
	};
	// ====================================================================================
		


	// Close the console window if in release mode
	#ifdef NDEBUG
	FreeConsole();
	#endif // NDEBUG

	// Create a window
	ProtoEngine::Window window(1600, 800, "ProtoEngine");


	// Initialize the input handler
	ProtoEngine::HandleInput inputHandler(&window);

	// Create a shader
	ProtoEngine::Shader shader("Source/Shaders/VertexShader.glsl", "Source/Shaders/FragmentShader.glsl");
	shader.Use();	


	int currentWidth{}, currentHeight{};
	ProtoEngine::Object rectangle(vertices, indices);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		// Clear the window
		window.ClearWindow();

		// Use the shader
		shader.Use();

		// Set the projection matrix
		window.GetDimensions(&currentWidth, &currentHeight);

		glViewport(0, 0, currentWidth, currentHeight);

		glm::mat4 projection{ glm::ortho(0.0f, static_cast<float>(currentWidth), 0.0f, static_cast<float>(currentHeight), -1.0f, 1.0f) };

		shader.SetMat4("projection", projection);
		shader.SetVec4("objectColor", 1.0f, 0.5f, 0.2f, 1.0f);

		// Draw the rectangle
		rectangle.Draw();

		// Swap front and back buffers
		window.SwapBuffers();

		// Poll for and process events
		window.PollEvents();
	}

	return 0;
}