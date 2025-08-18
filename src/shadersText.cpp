#include "../includes/shadersText.h"
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#define STB_TRUETYPE_IMPLEMENTATION
#include "../includes/stb_truetype.h"

std::vector<float> vertecies;
std::string Loadfile(const std::string &path) {
  std::ifstream file(path);
  std::stringstream buffer;
  if (!file.is_open()) {
    std::cerr << "failed to open file " << path << std::endl;
    return "";
  }
  buffer << file.rdbuf();
  return buffer.str();
}
std::vector<unsigned char> LoadTTF(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    std::cerr << "failed to open file " << path << std::endl;
    while (1) {
    };
  }

  size_t size = file.tellg();
  std::vector<unsigned char> FontBuffer(size);
  file.seekg(0);

  if (!file.read(reinterpret_cast<char *>(FontBuffer.data()), size)) {
    std::cerr << "failed to read font file " << std::endl;
    while (1)
      ;
  }
  return FontBuffer;
}

void TextShader::load_opengl_shader() {
  std::string pathVertCode =
      Loadfile("/home/nir/editor/shaders/text/text.vert");
  std::string pathFragCode =
      Loadfile("/home/nir/editor/shaders/text/text.frag");

  const char *fSrc = pathFragCode.c_str();
  const char *vSrc = pathVertCode.c_str();

  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vSrc, nullptr);
  glCompileShader(vertShader);
  GLint vert_resualt;
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vert_resualt);
  if (vert_resualt == GL_FALSE) {
    std::cerr << "text shader was not initiated" << std::endl;
    while (1)
      ;
  }
  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &fSrc, nullptr);
  glCompileShader(frag_shader);
  TextShaderData.program = glCreateProgram();
  glAttachShader(TextShaderData.program, vertShader);
  glAttachShader(TextShaderData.program, frag_shader);
  glLinkProgram(TextShaderData.program);
}

/// usr/share/fonts/TTF/JetBrainsMonoNerdFontPropo-Light.ttf"

void TextShader::load_stb_atlas() {
  std::vector<unsigned char> fontBuffer =
      LoadTTF("/usr/share/fonts/TTF/DejaVuSans-Bold.ttf");
  stbtt_fontinfo font;
  if (!stbtt_InitFont(
          &font, fontBuffer.data(),
          stbtt_GetFontOffsetForIndex_internal(fontBuffer.data(), 0))) {
    std::cerr << " failed to init stb font" << std::endl;
    while (1)
      ;
  }
  fontOffsets.size = 64.0f;
  ProgramFont.scale = stbtt_ScaleForPixelHeight(&font, fontOffsets.size);
  stbtt_GetFontVMetrics(&font, &ProgramFont.ascent, &ProgramFont.descent,
                        &ProgramFont.lineGap);

  std::cout << "font loaded" << std::endl;
  std::cout << "ascent: " << ProgramFont.ascent * ProgramFont.scale
            << std::endl;
  std::cout << "descent: " << ProgramFont.descent * ProgramFont.scale
            << std::endl;
  std::cout << "linegap: " << ProgramFont.lineGap * ProgramFont.scale
            << std::endl;
  std::cout << "font size" << ProgramFont.scale << std::endl;
  FontData.width = 512;
  FontData.hieght = 512;
  std::vector<unsigned char> atlas(FontData.width * FontData.hieght);
  stbtt_pack_context pc;
  stbtt_PackBegin(&pc, atlas.data(), FontData.width, FontData.hieght, 0, 1,
                  nullptr);

  stbtt_PackFontRange(&pc, fontBuffer.data(), 0, fontOffsets.size, 32, 95,
                      FontData.chars);
  stbtt_PackEnd(&pc);

  glGenTextures(1, &FontData.TextreID);
  glBindTexture(GL_TEXTURE_2D, FontData.TextreID);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, FontData.width, FontData.hieght, 0,
               GL_RED, GL_UNSIGNED_BYTE, atlas.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextShader::init_text() {
  std::cout << "start of init text " << std::endl;
  load_opengl_shader();
  std::cout << "sagfault at shader" << std::endl;
  load_stb_atlas();
  std::cout << "text was initiated" << std::endl;
  curLine.x = 100.0f;
  curLine.y = 100.0f;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void TextShader::build_vao() {
  glGenVertexArrays(1, &VAO_TEXT);
  glGenBuffers(1, &VBO_TEXT);
  glGenBuffers(1, &EBO_TEXT);

  glBindVertexArray(VAO_TEXT);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXT);
  std::cout << vertecies.size() << " " << sizeof(vertexData) << std::endl;
  glBufferData(GL_ARRAY_BUFFER, vertecies.size() * sizeof(vertexData) * 6,
               vertecies.data(),
               GL_STATIC_DRAW); // if not drawing * sizeof(float)
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)0);

  glBindVertexArray(0);
  TextShaderData.projection =
      glm::ortho(0.0f, (float)Glwindow::get().width,
                 (float)Glwindow::get().highet, 0.0f, -1.0f, 1.0f);
  TextShaderData.color = glm::vec3(1.0f, 0.0f, 0.0f);
  std::cout << "sagfault at somewhere" << std::endl;
  /*
   * space for more parameters
   */
}
void TextShader::build_string(std::string line) {
  for (auto &ch : line) {
    stbtt_aligned_quad q;
    stbtt_GetPackedQuad(FontData.chars, FontData.width, FontData.hieght,
                        ch - 32, &curLine.x, &curLine.y, &q, 1);

    quadData t = {
        {q.x0, q.y0, q.s0, q.t0},
        {q.x1 - fontOffsets.xScale, q.y0, q.s1, q.t0},
        {q.x0, q.y1 + fontOffsets.yScale, q.s0, q.t1},

        {q.x1 - fontOffsets.xScale, q.y0, q.s1, q.t0},
        {q.x1 - fontOffsets.xScale, q.y1 + fontOffsets.yScale, q.s1, q.t1},
        {q.x0, q.y1 + fontOffsets.yScale, q.s0, q.t1},
    };
    if (ch != ' ')
      curLine.x -= fontOffsets.Xspace;
    else
      curLine.x -= fontOffsets.XSpaceForSpace;

    std::cout << ch << std::endl;
    vertecies.push_back(t);
  }
  build_vao();
}
void push_string();
void TextShader::flush_render() {
  glUseProgram(TextShaderData.program);
  glUniformMatrix4fv(glGetUniformLocation(TextShaderData.program, "projection"),
                     1, GL_FALSE, glm::value_ptr(TextShaderData.projection));
  glUniform3f(glGetUniformLocation(TextShaderData.program, "textColor"),
              TextShaderData.color.r, TextShaderData.color.g,
              TextShaderData.color.b);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, FontData.TextreID);

  glBindVertexArray(VAO_TEXT);

  glDrawArrays(GL_TRIANGLES, 0, vertecies.size() * 6);

  glBindVertexArray(0);
  glUseProgram(0);
}
