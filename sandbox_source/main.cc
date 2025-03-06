#include "proto_engine.h"
#include "window.h"

int main() {
  ProtoEngine::Window window(800, 600);
  window.Init();
  while (!window.ShouldClose()) {
    window.PollEvents();
  }
  window.Close();
  return 0;
}