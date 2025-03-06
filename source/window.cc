#include "window.h"

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <stdexcept>

struct ProtoEngine::Window::GLFWWindowHandle {
  GLFWwindow* window = nullptr;
};

struct ProtoEngine::Window::VkInstanceHandle {
  VkInstance instance = nullptr;
};

void error_callback(int error, const char* description) {
  std::cerr << "GLFW Error: " << description << std::endl;
}

ProtoEngine::Window::Window(uint16_t width, uint16_t height)
    : width_(width),
      height_(height),
      resizable_(false),
      window_(new GLFWWindowHandle()),
      vulkan_instance_(new VkInstanceHandle()) {}

void ProtoEngine::Window::Init() {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialise GLFW!");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  glfwSetErrorCallback(error_callback);

  window_->window =
      glfwCreateWindow(width_, height_, "ProtoEngine Window", nullptr, nullptr);

  if (!window_) {
    throw std::runtime_error("Failed to create window!");
  }

  VkApplicationInfo app_info;
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "Hello Triangle";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "No Engine";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;

  uint32_t glfw_extension_count{};
  const char** glfw_extensions;

  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

  create_info.enabledExtensionCount = glfw_extension_count;
  create_info.ppEnabledExtensionNames = glfw_extensions;
  create_info.enabledLayerCount = 0;

  VkResult result{
      vkCreateInstance(&create_info, nullptr, &vulkan_instance_->instance)};



  glm::vec4 vec;
  glm::mat4 matrix;
  auto test{matrix * vec};
}

void ProtoEngine::Window::PollEvents() { glfwPollEvents(); }

bool ProtoEngine::Window::ShouldClose() {
  return glfwWindowShouldClose(window_->window) ? true : false;
}

void ProtoEngine::Window::Close() {
  vkDestroyInstance(vulkan_instance_->instance, nullptr);
  glfwDestroyWindow(window_->window);
  glfwTerminate();
}

void ProtoEngine::Window::DrawTriangle() {}

ProtoEngine::Window::~Window() {
  delete window_;
  delete vulkan_instance_;
}
