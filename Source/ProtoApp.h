#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class ProtoApp
{
public:
	ProtoApp(std::string title, int width, int height);
	void loop();
	~ProtoApp();

private:
	GLFWwindow* window;
};

