/* ======================== PURPOSE OF FILE ========================
* 
* This file is the entry point for the application. 
*	It creates a window using GLFW and GLEW, 
* and then enters a loop to render the window.
* 
==================================================================*/

// Link OpenGL Extension Wrangler
#include <GL/glew.h>

// Link GLFW for window creation and input handling
#include <GLFW/glfw3.h>

// Link GLM for algebra
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Link standard libraries
#include <iostream>
#include <Windows.h>

// Link custom classes
#include "HandleInput.h"
#include "Shader.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


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
#ifdef DEBUG
		std::cerr << "Failed to create window" << std::endl;
#endif // DEBUG
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	
	// Initialise GLEW
	if (glewInit() != GLEW_OK)
	{
#ifdef DEBUG
		std::cerr << "Failed to initialize GLEW" << std::endl;
#endif // DEBUG
		glfwTerminate();
		return -1;
	}
#ifdef DEBUG
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
#endif

	// Initialise the input handler
	ProtoEngine::HandleInput inputHandler(window);
	ProtoEngine::Shader shader("Source/Shaders/vertexShader.glsl", "Source/Shaders/fragmentShader.glsl");
	shader.Use();	

	// Draw simple object
	// Define the vertices of a rectangle
	float vertices[] = {
			-0.5f, -0.5f,  // bottom-left corner
			 0.5f, -0.5f,  // bottom-right corner
			 0.5f,  0.5f,  // top-right corner
			-0.5f,  0.5f   // top-left corner
	};

	// Define the indices to form two triangles (making a rectangle)
	unsigned int indices[] = {
			0, 1, 2,  // first triangle
			2, 3, 0   // second triangle
	};

	// Create Vertex Array Object (VAO), Vertex Buffer Object (VBO), and Element Buffer Object (EBO)
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind and set up vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind and set up element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
#ifdef DEBUG
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << error << std::endl;
	}
#endif // DEBUG

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Set the clear colour
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Render here
		glClear(GL_COLOR_BUFFER_BIT);


		// Use the shader
		shader.Use();

		// Bind VAO before drawing
		glBindVertexArray(VAO);

		// Draw the rectangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Unbind VAO after drawing
		glBindVertexArray(0);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		// Check for OpenGL errors
#ifdef DEBUG
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cerr << "OpenGL error: " << error << std::endl;
		}
#endif // DEBUG

	}

	return 0;
}