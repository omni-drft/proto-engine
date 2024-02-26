/* ========================== FILE PURPOSE ==========================
* 
*	 This file contains the window class which is used to create 
*  a window using GLFW and manage all the window related functions.
* 
================================================================== */

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace ProtoEngine
{

/// <summary>
/// This class is used to create a window using GLFW
/// </summary>
class Window
{
public:
	/// <summary>
	/// Main constructor for the window class
	/// </summary>
	/// <param name="windowWidth">- width of the window</param>
	/// <param name="windowHeight">- height of the window</param>
	/// <param name="windowTitle">- title of the window</param>
	Window(int windowWidth, int windowHeight, const char* windowTitle);

	/// <summary>
	/// Window getter
	/// </summary>
	/// <returns>window</returns>
	GLFWwindow* GetWindow() { return window; }

	/// <summary>
	/// Function to close the window
	/// </summary>
	void SetShouldClose(bool value) { glfwSetWindowShouldClose(window, true); }

	/// <summary>
	/// Swap the front and back buffers using the window class
	/// </summary>
	void SwapBuffers() { glfwSwapBuffers(window); }

	/// <summary>
	/// Poll events using the window class
	/// </summary>
	void PollEvents() { glfwPollEvents(); }

	/// <summary>
	/// Function to get the dimensions of the viewport
	/// </summary>
	/// <param name="width">- variable that will get window width</param>
	/// <param name="height">- variable that will get window height</param>
	void GetDimensions(int* width, int* height) { glfwGetWindowSize(window, width, height); }

	/// <summary>
	/// Clean the window and set the background color
	/// </summary>
	void ClearWindow();

private:

	/// <summary>
	/// Width of the window
	/// </summary>
	unsigned int width;

	/// <summary>
	/// Height of the window
	/// </summary>
	unsigned int height;

	/// <summary>
	/// Title of the window 
	/// </summary>
	std::string title;

	/// <summary>
	/// GLFW window pointer
	/// </summary>
	GLFWwindow* window;

	/// <summary>
	/// Frame buffer size callback function
	/// </summary>
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

}