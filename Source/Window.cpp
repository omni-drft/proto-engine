/* ================================= FILE PURPOSE ===============================
* 
*	 This file contains the implementation of the Window class. This class is 
*  responsible for creating a window using GLFW and GLEW. It also sets the
*  background color of the window and clears the window.
* 
=============================================================================== */

#include "Window.hpp"

ProtoEngine::Window::Window(int windowWidth, int windowHeight, const char* windowTitle)
	: width(windowWidth), height(windowHeight), title(windowTitle), window(nullptr)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		Log::GetLogger()->critical("GLFW: Failed to initialize");
		return;
	}
	else
		Log::GetLogger()->info("GLFW: Initialized succesfully");

	//// Get the primary monitor, which is necessary to set the window to full screen
	//GLFWmonitor* primatyMonitor = glfwGetPrimaryMonitor();
	//// If the primary monitor is not found, print an error message and return
	//if (!primatyMonitor)
	//{
	//	#ifdef DEBUG
	//	std::cerr << "Failed to get primary monitor" << std::endl;
	//	#endif // DEBUG
	//}
	//else
	//{
	//	#ifdef DEBUG
	//	std::cout << "Primary monitor found" << std::endl;
	//	#endif // DEBUG
	//}

	//// Get the video mode of the primary monitor
	//const GLFWvidmode* mode = glfwGetVideoMode(primatyMonitor);
	//// If the video mode is not found, print an error message and create a default mode window
	//if (!mode)
	//{
	//	#ifdef DEBUG
	//	std::cerr << "Failed to get video mode" << std::endl;
	//	#endif // DEBUG
	//	// Create a windowed mode window and its OpenGL context
	//	window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
	//}
	//else
	//{
	//	#ifdef DEBUG
	//	std::cout << "Video mode found" << std::endl;
	//	#endif // DEBUG
	//}

	// Set the OpenGL properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// setting the window to not be resizable
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	// Create a windowed mode window and its OpenGL context
	if (!window)
	{ 
		Log::GetLogger()->critical("Window: Failed to create");
		return;
	}
	else
		Log::GetLogger()->info("Window: Created succesfully");

	// Set the window to full screen
	//glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);


	// Make the window's context current
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);


	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		Log::GetLogger()->critical("GLEW: Failed to initialize");
		glfwTerminate();
		return;
	}
	else
	{
		Log::GetLogger()->info("GLEW: Initialized succesfully");
	}
	std::string glVersion{ reinterpret_cast<const char*>(glGetString(GL_VERSION)) };	
	Log::GetLogger()->info("OpenGL: Version: {0}", glVersion);
}

void ProtoEngine::Window::ClearWindow()
{
	// Set the background color
	glClearColor(20.0f / 255.0f, 20.0f / 255.0f, 20.0f / 255.0f, 1.0f);

	// Clear the window	
	glClear(GL_COLOR_BUFFER_BIT);
}

ProtoEngine::Window::~Window()
{
	// Terminate GLFW
	glfwTerminate();
}

void ProtoEngine::Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// Set the viewport to the new window size
	glViewport(0, 0, width, height);
}
