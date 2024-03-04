/* ======================== PURPOSE OF FILE ========================
* 
* This file is the entry point for the application. 
*	It creates a window using GLFW and GLEW, 
* and then enters a loop to render the window.
* 
================================================================== */

#include "Includes.hpp"

int main()
{
	// Create a logger
	ProtoEngine::Log::Init();

	// Log that the logger has been initialized
	ProtoEngine::Log::GetLogger()->info("Logger initialized");
	// Log that the engine is starting
	ProtoEngine::Log::GetLogger()->info("ProtoEngine starting...");

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


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		// Clear the window
		window.ClearWindow();

		// Update the window dimensions and viewport
		glViewport(0, 0, currentWidth, currentHeight);
		window.GetDimensions(&currentWidth, &currentHeight);

		// Swap front and back buffers
		window.SwapBuffers();

		// Poll for and process events
		window.PollEvents();
	}

	return 0;
}