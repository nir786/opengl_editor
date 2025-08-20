#pragma once

#include "../editor/glad/glad.h"
#include "shaderManeger.h"
#include "shadersText.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
class pathManeger {
public:
  int x, y, highet, width;
  int is_toggeled;
  std::string command_line_buffer;
  std::vector<std::string> possible_paths;

  void init_path();
  void render_path();
  void on_Screen_Resize();
  void on_Click_Toggele_Path();

  static pathManeger &get() {
    static pathManeger instance;
    return instance;
  }

private:
  pathManeger() = default;
};
