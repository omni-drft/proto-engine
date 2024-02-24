/* ================================= FILE PURPOSE ===============================
* 
*	 This file contains the implementation of the Window class. This class is 
*  responsible for creating a window using GLFW and GLEW. It also sets the
*  background color of the window and clears the window.
* 
=============================================================================== */

#include "Window.h"

ProtoEngine::Window::Window(int windowWidth, int windowHeight, const char* windowTitle)
	: width(windowWidth), height(windowHeight), title(windowTitle), window(nullptr)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		#ifdef DEBUG
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
		#endif // DEBUG
	}

	// Set the OpenGL properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);

	// setting the window to not be resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
	if (!window)
	{ 
		#ifdef DEBUG
		std::cerr << "Failed to create window" << std::endl;
		return;
		#endif // DEBUG
	}

	// Set the window to full screen
	glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, windowWidth, windowHeight, GLFW_DONT_CARE);


	// Make the window's context current
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);


	// Initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		#ifdef DEBUG
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return;
		#endif // DEBUG
	}

	#ifdef DEBUG
	// Print the OpenGL version
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	#endif
}

void ProtoEngine::Window::ClearWindow()
{
	// Set the background color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT);
}

void ProtoEngine::Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// Set the viewport to the new window size
	glViewport(0, 0, width, height);
}
