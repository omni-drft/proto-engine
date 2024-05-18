#include "ProtoApp.h"

ProtoApp::ProtoApp(std::string title, int width, int height)
{
	// Vulkan instance creation
	createInstance();

	// GLFW initialisation and error handling
	if (!glfwInit())
		std::cerr << "Failed to initialise glfw" << std::endl;
	
	// GLFW setup
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Window creation
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

void ProtoApp::run()
{
	// Checking if app should be closed
	while (!glfwWindowShouldClose(window))
		glfwPollEvents();
}

ProtoApp::~ProtoApp()
{
	// Correctly closing all libraries
	vkDestroyInstance(instance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}

void ProtoApp::createInstance()
{
	// Adding information about application (can lead to better optimisation)
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "ProtoEngine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	// Using created information to apply it 
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	// Creating variables to hold available extensions
	uint32_t glfwExtensionCount{};
	const char** glfwExtensions{};

	// Collecting information about required extensions
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// Binding variables as a place to hold extension info
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	// Disabling validation layers
	createInfo.enabledLayerCount = 0;

	// Creating Vulkan instance
	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

	// Handling failure of Vulkan instance creation
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		throw std::runtime_error("failed to create instance!");
	else
		std::cout << "Instance created succesfully!" << std::endl;

	// Collecting information about available extensions
	uint32_t extensionCount{};
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	// Printing all available extensions
	std::cout << "Available extensions:" << std::endl;
	for (const auto& extension : extensions)
		std::cout << "    " << extension.extensionName << std::endl;
}



