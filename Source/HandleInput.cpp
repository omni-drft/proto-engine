/* ======================== PURPOSE OF FILE ========================
*
* This file is the implementation of the HandleInput class.
*
==================================================================*/

#include "HandleInput.hpp"

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
	Log::GetLogger()->trace("Cursor Position: X: {0}, Y: {1}", xpos, ypos);
	#endif 

}

void ProtoEngine::HandleInput::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	// If the left mouse button is pressed, print a message
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{

		#ifdef INPUT_DEBUG
		Log::GetLogger()->trace("Left mouse button pressed");
		#endif

	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{

		#ifdef INPUT_DEBUG
		Log::GetLogger()->trace("Right mouse button pressed");
		#endif 

	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{

		#ifdef INPUT_DEBUG
		Log::GetLogger()->trace("Middle mouse button pressed");
		#endif

	}
}

void ProtoEngine::HandleInput::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

	#ifdef INPUT_DEBUG
	// Print the scroll offset whenever the mouse wheel is scrolled
	Log::GetLogger()->trace("Scroll Offset: X: {0}, Y: {1}", xoffset, yoffset);
	#endif

}

void ProtoEngine::HandleInput::CharacterCallback(GLFWwindow* window, unsigned int codepoint)
{

	#ifdef INPUT_DEBUG
	// Print the character whenever a key is pressed
	Log::GetLogger()->trace("Character: {0}", codepoint);
	#endif

}
