#include "proto_engine.h"
#include "window.h"

int main() {
  ProtoEngine::Window window(400, 200);
  window.Init();
  while (!window.ShouldClose()) {
    window.PollEvents();
  }
  window.Close();
  return 0;
}