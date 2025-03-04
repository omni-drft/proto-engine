#ifndef PROTOENGINE_INCLUDE_WINDOW_H_
#define PROTOENGINE_INCLUDE_WINDOW_H_

#include <cstdint>

#include "engine_exports.h"

namespace ProtoEngine {
class ENGINE_API Window {
 public:
  Window(uint16_t width, uint16_t height);
  void Init();
  void Close();
  ~Window();

 private:
  uint16_t width_, height_;
  bool resizable_;
  struct GLFWWindowHandle;
  GLFWWindowHandle* window_;
};

}  // namespace ProtoEngine
#endif  // PROTOENGINE_INCLUDE_WINDOW_H_
