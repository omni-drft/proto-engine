/* ======================== PURPOSE OF FILE ========================
*
* This file is the implementation of the HandleInput class.
*
==================================================================*/

#include "HandleInput.h"

ProtoEngine::HandleInput::HandleInput(ProtoEngine::Window* window)
	: inputWindow(window)
{

	// Set the key callback function
	glfwSetKeyCallback(inputWindow->GetWindow(), KeyCallback);

	// Set the cursor position callback function
	glfwSetCursorPosCallback(inputWindow->GetWindow(), CursorPositionCallback);

	// Set the mouse button callback function
	glfwSetMouseButtonCallback(inputWindow->GetWindow(), MouseButtonCallback);

	// Set the scroll callback function
	glfwSetScrollCallback(inputWindow->GetWindow(), ScrollCallback);

	// Set the character callback function
	glfwSetCharCallback(inputWindow->GetWindow(), CharacterCallback);
}

void ProtoEngine::HandleInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// If the escape key is pressed, close the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void ProtoEngine::HandleInput::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{

	#if INPUT_DEBUG
	// Print the current cursor position whenever the cursor moves
	std::cout << "X: " << xpos << " Y: " << ypos << std::endl;
	#endif 

}

void ProtoEngine::HandleInput::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	// If the left mouse button is pressed, print a message
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{

	#ifdef INPUT_DEBUG
		std::cout << "Left mouse button pressed" << std::endl;
	#endif

	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{

	#ifdef INPUT_DEBUG
		std::cout << "Right mouse button pressed" << std::endl;
	#endif 

	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{

	#ifdef INPUT_DEBUG
		std::cout << "Middle mouse button pressed" << std::endl;
	#endif

	}
}

void ProtoEngine::HandleInput::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

#ifdef INPUT_DEBUG
	// Print the scroll offset whenever the mouse wheel is scrolled
	std::cout << "X Offset: " << xoffset << " Y Offset: " << yoffset << std::endl;
#endif

}

void ProtoEngine::HandleInput::CharacterCallback(GLFWwindow* window, unsigned int codepoint)
{

#ifdef INPUT_DEBUG
	// Print the character whenever a key is pressed
	std::cout << "Character: " << codepoint << std::endl;
#endif

}
