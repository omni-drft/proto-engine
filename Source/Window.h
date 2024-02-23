#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace ProtoEngine
{

class Window
{
public:
	Window(int windowWidth, int windowHeight, const char* windowTitle);
	GLFWwindow* GetWindow() { return window; }
	void SetShouldClose(bool value) { glfwSetWindowShouldClose(window, true); }
	void SwapBuffers() { glfwSwapBuffers(window); }
	void PollEvents() { glfwPollEvents(); }
	void ClearWindow();
private:
	unsigned int width, height;
	std::string title;
	GLFWwindow* window;

	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

}