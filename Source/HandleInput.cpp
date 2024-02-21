#include "HandleInput.h"

ProtoEngine::HandleInput::HandleInput(GLFWwindow* window)
	: inputWindow(window)
{
	// Set the key callback function
	glfwSetKeyCallback(inputWindow, KeyCallback);

	// Set the cursor position callback function
	glfwSetCursorPosCallback(inputWindow, CursorPositionCallback);

	// Set the mouse button callback function
	glfwSetMouseButtonCallback(inputWindow, MouseButtonCallback);

	// Set the scroll callback function
	glfwSetScrollCallback(inputWindow, ScrollCallback);

	// Set the character callback function
	glfwSetCharCallback(inputWindow, CharacterCallback);
}

void ProtoEngine::HandleInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// If the escape key is pressed, close the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void ProtoEngine::HandleInput::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	// Print the current cursor position whenever the cursor moves
	std::cout << "X: " << xpos << " Y: " << ypos << std::endl;
}

void ProtoEngine::HandleInput::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	// If the left mouse button is pressed, print a message
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << "Left mouse button pressed" << std::endl;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		std::cout << "Right mouse button pressed" << std::endl;
	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		std::cout << "Middle mouse button pressed" << std::endl;
	}
}

void ProtoEngine::HandleInput::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Print the scroll offset whenever the mouse wheel is scrolled
	std::cout << "X Offset: " << xoffset << " Y Offset: " << yoffset << std::endl;
}

void ProtoEngine::HandleInput::CharacterCallback(GLFWwindow* window, unsigned int codepoint)
{
	// Print the character whenever a key is pressed
	std::cout << "Character: " << codepoint << std::endl;
}
