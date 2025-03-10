#ifndef PROTOENGINE_INCLUDE_WINDOW_H_
#define PROTOENGINE_INCLUDE_WINDOW_H_

#include <cstdint>
#include <vector>

#include "engine_exports.h"

namespace ProtoEngine {
class Window {
 public:
  ENGINE_API Window(uint16_t width, uint16_t height);
  ENGINE_API void Init();
  ENGINE_API void PollEvents();
  ENGINE_API bool ShouldClose();
  ENGINE_API void Close();

  ENGINE_API void DrawTriangle();

  ENGINE_API ~Window();

 private:

  bool CheckValidationLayerSupport();

  void InitGLFW();
  void InitVulkan();
  void PickPhysicalDevice();

  uint16_t width_, height_;
  bool resizable_;

  struct GLFWWindowHandle;
  GLFWWindowHandle* window_;

  struct VkInstanceHandle;
  VkInstanceHandle* vulkan_instance_;

  struct VkDeviceHandle;
  VkDeviceHandle* display_device_;

  const std::vector<const char*> validation_layers_{
      "VK_LAYER_KHRONOS_validation"
  };

#ifdef _DEBUG
  const bool enable_validation_layers_{true};
#else
  const bool enable_validation_layers_{false};
#endif
};

}  // namespace ProtoEngine

#endif  // PROTOENGINE_INCLUDE_WINDOW_H_
