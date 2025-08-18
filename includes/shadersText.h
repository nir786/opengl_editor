#pragma once
#include "../editor/glad/glad.h"
#include "stb_truetype.h"
#include "window.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ios>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
struct FontParameters {
  float scale;
  int ascent, descent, lineGap;
};
struct TextShaderData_a {
  glm::mat4 projection;
  GLuint program;
  glm::vec3 color;
}; // add more variables when needed to costumize the shader more

struct Charecter {
  unsigned int TextreID;
  int ax, lsb;
};
struct AtlasData {
  unsigned int TextreID;
  int width, hieght;
  stbtt_packedchar chars[96];
};

struct vertexData {
  float x, y, uvx, uvy;
};

struct quadData {
  vertexData x0, x1, x2, y0, y3, y2;
};
struct currentLine {
  float x, y;
};

struct font {
  float size = 32.0f;
  float yScale = size / 2.0f;
  float xScale = size / 12.0f;
  float Xspace = size / 6.0f;
  float XSpaceForSpace = size / 4.0f;
};

class TextShader {
public:
  FontParameters ProgramFont;
  AtlasData FontData;
  currentLine curLine;
  std::vector<quadData> vertecies;
  font fontOffsets;
  TextShaderData_a TextShaderData;
  std::map<char, Charecter> Charcters;
  unsigned int VAO_TEXT, VBO_TEXT, EBO_TEXT;

  void init_text();
  void load_opengl_shader();
  void load_stb_atlas();
  void build_vao();
  void build_string(std::string);
  void push_string();
  void flush_render();

  static TextShader &get() {
    static TextShader instance;
    return instance;
  }

private:
  TextShader() = default;
};
