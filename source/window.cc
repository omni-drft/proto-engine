#include "window.h"

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

struct ProtoEngine::Window::GLFWWindowHandle {
  GLFWwindow* window = nullptr;
};

void error_callback(int error, const char* description) {
  std::cerr << "GLFW Error: " << description << std::endl;
}

ProtoEngine::Window::Window(uint16_t width, uint16_t height)
    : width_(width), height_(height), resizable_(true), window_(new GLFWWindowHandle()) {}

void ProtoEngine::Window::Init() {
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialise GLFW!");
  }

  glfwSetErrorCallback(error_callback);
  
  window_->window = 
      glfwCreateWindow(width_, height_, "ProtoEngine Window", nullptr, nullptr);
  
  if (!window_) {
    throw std::runtime_error("Failed to create window!");
  }

  uint32_t extension_count{};
  vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
  std::cout << extension_count << " extensions supported." << std::endl;

  glm::vec4 vec;
  glm::mat4 matrix;
  auto test{matrix * vec}; 
}

void ProtoEngine::Window::PollEvents() { glfwPollEvents(); }

bool ProtoEngine::Window::ShouldClose() {
  return glfwWindowShouldClose(window_->window) ? true : false;
}

void ProtoEngine::Window::Close() {
  glfwDestroyWindow(window_->window);
  glfwTerminate();
}

ProtoEngine::Window::~Window() { delete window_; }
