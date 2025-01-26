#ifndef IMGUI_MANAGER
#define IMGUI_MANAGER

#include "imgui.h"
#include <GLFW/glfw3.h>
class ImguiManager
{
  public:
    ImguiManager(GLFWwindow* window, const char* glslVersion);
    void init();
    void newFrame();
    void render();
    void cleanup();
    ImVec4& getClearColor();

  private:
    GLFWwindow* window;
    const char* glslVersion;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

#endif
