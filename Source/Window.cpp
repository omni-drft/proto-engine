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
	// Initialize GLFW
	if (!glfwInit())
	{
		#ifdef DEBUG
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
		#endif // DEBUG
	}
	else
	{
		#ifdef DEBUG
		std::cout << "GLFW initialized succesfully" << std::endl;
		#endif // DEBUG
	}

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

	// setting the window to not be resizable
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a windowed mode window and its OpenGL context
	#pragma warning(disable 6011)
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	#pragma warning(default 6011)

	// Create a windowed mode window and its OpenGL context
	if (!window)
	{ 
		#ifdef DEBUG
		std::cerr << "Failed to create window" << std::endl;
		return;
		#endif // DEBUG
	}
	else
	{
		#ifdef DEBUG
		std::cout << "Window created succesfully" << std::endl;
		#endif // DEBUG
	}

	// Set the window to full screen
	//glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);


	// Make the window's context current
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);


	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		#ifdef DEBUG
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return;
		#endif // DEBUG
	}
	else
	{
		#ifdef DEBUG
		std::cout << "GLEW initialized succesfully" << std::endl;
		#endif // DEBUG
	}

	// Initialize FreeType
	if (FT_Init_FreeType(&ft))
	{
		#ifdef DEBUG
		std::cerr << "Failed to initialize FreeType" << std::endl;
		return;
		#endif // DEBUG
	}
	else
	{
		#ifdef DEBUG
		std::cout << "FreeType initialized succesfully" << std::endl;
		#endif // DEBUG
	}

	// Load the font
	if (FT_New_Face(ft, "Assets/Fonts/SourceCodePro.ttf", 0, &face))
	{
		#ifdef DEBUG
		std::cerr << "Failed to load font" << std::endl;
		return;
		#endif // DEBUG
	}
	else
	{
		#ifdef DEBUG
		std::cout << "Font loaded succesfully" << std::endl;
		#endif // DEBUG
	}

	// Set the font size
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Create map of character glyphs
	std::map<char, Character> characters;

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

	// Load the first 128 characters of the ASCII set
	for (unsigned char c{ 0 }; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			#ifdef DEBUG
			std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			#endif // DEBUG
			continue;
		}

		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// now store character for later use
		Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
		};
		characters.insert(std::pair<char, Character>(c, character));
	}

	#ifdef DEBUG
	// Print the OpenGL version
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	#endif
}

void ProtoEngine::Window::ClearWindow()
{
	// Set the background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the window	
	glClear(GL_COLOR_BUFFER_BIT);
}

ProtoEngine::Window::~Window()
{
	// Terminate GLFW
	glfwTerminate();

	// Terminate FreeType
	//FT_Done_Face(face);
	//FT_Done_FreeType(ft);
}

void ProtoEngine::Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	// Set the viewport to the new window size
	glViewport(0, 0, width, height);
}
