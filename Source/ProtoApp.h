#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <string>
#include <vector>

/// <summary>
/// The main class for the whole project. 
/// </summary>
class ProtoApp
{
public:
	/// <summary>
	/// The only constructor for ProtoApp class
	/// </summary>
	/// <param name="title">- App title (also window title)</param>
	/// <param name="width">- Window width</param>
	/// <param name="height">- Window height</param>
	ProtoApp(std::string title, int width, int height);

	/// <summary>
	/// Main run function for whole project
	/// </summary>
	void run();

	/// <summary>
	/// Destructor for ProtoApp class. It handles 
	/// the process of closing all libraries correctly
	/// </summary>
	~ProtoApp();

private:
	/// <summary>
	/// Main window for the app
	/// </summary>
	GLFWwindow* window;

	/// <summary>
	/// Main Vulkan Instance
	/// </summary>
	VkInstance instance;

	/// <summary>
	/// A function that handles vulkan instance creation
	/// </summary>
	void createInstance();
};

