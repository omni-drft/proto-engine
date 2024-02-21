#pragma once

// Library Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/// <summary>
/// General purpose namespace for the engine
/// </summary>
namespace ProtoEngine
{
	/// <summary>
	/// Class to handle input from the user
	/// </summary>
	class HandleInput
	{
	public:
		/// <summary>
		/// Constructor for the input handler
		/// </summary>
		/// <param name="window">- pointer to window that currently takes input</param>
		HandleInput(GLFWwindow* window);

	private:
		/// <summary>
		/// Current window that is taking input
		/// </summary>
		GLFWwindow* inputWindow;

		/// <summary>
		/// Static callback function for handling all key presses
		/// </summary>
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/// <summary>
		/// Static callback function for handling the cursor position
		/// </summary>
		static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	};
}