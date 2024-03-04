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

#include <spdlog/spdlog.h>

// Link standard libraries
#include <iostream>
#include <Windows.h>
#include <vector>

// Link custom classes
#include "HandleInput.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "Object.hpp"
#include "Vertex.hpp"
#include "Text.hpp"
#include "Character.hpp"

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

	// Create shader for objects
	ProtoEngine::Shader objectShader("Source/Shaders/VertexShader.glsl", "Source/Shaders/FragmentShader.glsl");
	objectShader.Use();	
	int currentWidth{}, currentHeight{};
	window.GetDimensions(&currentWidth, &currentHeight);
	glm::mat4 projection{ glm::ortho(0.0f, static_cast<float>(currentWidth), 0.0f, static_cast<float>(currentHeight), -1.0f, 1.0f) };
	objectShader.SetMat4("projection", projection);
	objectShader.SetVec4("objectColor", 1.0f, 0.5f, 0.2f, 1.0f);

	// Create shader for text rendering
	ProtoEngine::Shader textShader("Source/Shaders/GlyphVertexShader.glsl", "Source/Shaders/GlyphFragmentShader.glsl");
	textShader.SetMat4("projection", projection);
	
	ProtoEngine::Object rectangle(vertices, indices);

	ProtoEngine::Text text("Hello there!");

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		// Clear the window
		window.ClearWindow();

		// Update the window dimensions and viewport
		glViewport(0, 0, currentWidth, currentHeight);
		window.GetDimensions(&currentWidth, &currentHeight);

		// Draw the object
		//objectShader.Use();
		//rectangle.Draw();

		// Draw the text
		text.Render(textShader, 100.0f, 100.0f, 5.0f, glm::vec3(1.0f, 1.0f, 1.0f));

		// Swap front and back buffers
		window.SwapBuffers();

		// Poll for and process events
		window.PollEvents();
	}

	return 0;
}