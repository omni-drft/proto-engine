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

struct ProtoEngine::Window::VkDeviceHandle {
  VkPhysicalDevice physical_device = VK_NULL_HANDLE;
};

void error_callback(int error, const char* description) {
  std::cerr << "GLFW Error: " << description << std::endl;
}

ProtoEngine::Window::Window(uint16_t width, uint16_t height)
    : width_(width),
      height_(height),
      resizable_(false),
      window_(new GLFWWindowHandle()),
      vulkan_instance_(new VkInstanceHandle()),
      display_device_(new VkDeviceHandle()) {}

void ProtoEngine::Window::Init() {
  InitGLFW();
  InitVulkan();
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
  delete display_device_;
}

bool ProtoEngine::Window::CheckValidationLayerSupport() {
  uint32_t layer_count{};
  vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

  std::vector<VkLayerProperties> available_layers(layer_count);
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

  for (const char* layer_name : validation_layers_) {
    bool layer_found{false};
    for (const auto& layer_properties : available_layers) {
      if (strcmp(layer_name, layer_properties.layerName) == 0) {
        layer_found = true;
        break;
      }
    }
    if (!layer_found) {
      return false;
    }
  }
  return true;
}

void ProtoEngine::Window::InitGLFW() {
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
}

void ProtoEngine::Window::InitVulkan() {
  if (enable_validation_layers_ && !CheckValidationLayerSupport()) {
    throw std::runtime_error("Validation layers requested, but not available.");
  }

  VkApplicationInfo app_info;
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "ProtoEngine Game";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "ProtoEngine";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;
  app_info.pNext = NULL;

  VkInstanceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;
  create_info.pNext = NULL;

  if (enable_validation_layers_) {
    create_info.enabledLayerCount =
        static_cast<uint32_t>(validation_layers_.size());
    create_info.ppEnabledLayerNames = validation_layers_.data();
  } else {
    create_info.enabledExtensionCount = 0;
  }

  vkCreateInstance(&create_info, nullptr, &vulkan_instance_->instance);
}

void ProtoEngine::Window::PickPhysicalDevice() {
  uint32_t device_count{};
  vkEnumeratePhysicalDevices(vulkan_instance_->instance, &device_count,
                             nullptr);
  if (device_count == 0) {
    throw std::runtime_error("Failed to find GPUs with Vulkan support");
  }

  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(vulkan_instance_->instance, &device_count,
                             devices.data());
}
