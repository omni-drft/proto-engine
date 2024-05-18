#include "ProtoApp.h"

ProtoApp::ProtoApp(std::string title, int width, int height)
{
	if (!glfwInit())
		std::cerr << "Failed to initialise glfw" << std::endl;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

void ProtoApp::loop()
{
	while (!glfwWindowShouldClose(window))
		glfwPollEvents();
}

ProtoApp::~ProtoApp()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}



