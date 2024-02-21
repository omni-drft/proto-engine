#include "HandleInput.h"

ProtoEngine::HandleInput::HandleInput(GLFWwindow* window)
	: inputWindow(window)
{
	glfwSetKeyCallback(inputWindow, KeyCallback);
	glfwSetCursorPosCallback(inputWindow, CursorPositionCallback);
}

void ProtoEngine::HandleInput::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void ProtoEngine::HandleInput::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "X: " << xpos << " Y: " << ypos << std::endl;
}

