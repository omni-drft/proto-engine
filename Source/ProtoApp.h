#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <string>

class ProtoApp
{
public:
	ProtoApp(std::string title, int width, int height);
	void run();
	~ProtoApp();

private:
	GLFWwindow* window;
	VkInstance instance;

	void createInstance();
};

