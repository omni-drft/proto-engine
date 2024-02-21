/* ======================== PURPOSE OF FILE ========================
* 
* This file is the entry point for the application. 
*	It creates a window using GLFW and GLEW, 
* and then enters a loop to render the window.
* 
==================================================================*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <Windows.h>

#include "HandleInput.h"


int main()
{
	// Close the console window if in release mode
#ifdef NDEBUG
	FreeConsole();
#endif


	// Initialise GLFW
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Set the OpenGL properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	
	// Initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Initialise the input handler
	ProtoEngine::HandleInput inputHandler(window);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);

		// Set the clear colour
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	return 0;
}