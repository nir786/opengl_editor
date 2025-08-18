#include "../includes/shaderManeger.h"
#include <vector>
std::vector<float> vet_path;
std::vector<unsigned int> ind_path;

void Shaders::create_path(float boxWidth, float boxHight, float ceterX,
                          float ceterY) {
  vet_path.clear();
  ind_path.clear();
  float left = ceterX + Glwindow::get().highet / 4.0f;
  float right = ceterX + boxWidth;
  float top = ceterY;
  float bottom = ceterY + boxHight;
  std::cout << left << " left < " << right << "right < " << top << " top < "
            << bottom << "bott<< " << std::endl;
  vet_path.push_back(left);
  vet_path.push_back(top);
  vet_path.push_back(0.0f);
  vet_path.push_back(1.0f);
  vet_path.push_back(1.0f);

  vet_path.push_back(right);
  vet_path.push_back(top);
  vet_path.push_back(1.0f);
  vet_path.push_back(1.0f);
  vet_path.push_back(1.0f);

  vet_path.push_back(right);
  vet_path.push_back(bottom);
  vet_path.push_back(1.0f);
  vet_path.push_back(0.0f);
  vet_path.push_back(1.0f);

  vet_path.push_back(left);
  vet_path.push_back(bottom);
  vet_path.push_back(0.0f);
  vet_path.push_back(0.0f);
  vet_path.push_back(1.0f);

  ind_path.push_back(0);
  ind_path.push_back(1);
  ind_path.push_back(2);
  ind_path.push_back(0);
  ind_path.push_back(2);
  ind_path.push_back(3);
}

std::string LoadFile(const std::string &path) {
  std::ifstream file(path);
  std::stringstream buffer;
  if (!file.is_open()) {
    std::cerr << "failed to open file " << path << std::endl;
    return "";
  }
  buffer << file.rdbuf();
  return buffer.str();
}

void Shaders::widget_shader_init(const char *vertexPath, const char *fragPath) {
  std::string vertCode = LoadFile(vertexPath);
  std::string fragCode = LoadFile(fragPath);
  std::string pathVertCode =
      LoadFile("/home/nir/editor/shaders/pathLookUp.vert");
  std::string pathFragCode =
      LoadFile("/home/nir/editor/shaders/pathLookUp.frag");

  const char *pfSrc = pathFragCode.c_str();
  const char *pvSrc = pathVertCode.c_str();

  const char *vSrc = vertCode.c_str();
  const char *fSrc = fragCode.c_str();

  GLuint pvertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(pvertShader, 1, &pvSrc, nullptr);
  glCompileShader(pvertShader);
  GLint p_vert_resualt;
  glGetShaderiv(pvertShader, GL_COMPILE_STATUS, &p_vert_resualt);
  if (p_vert_resualt == GL_FALSE) {
    std::cerr << "path shader was not initiated" << std::endl;
    while (1)
      ;
  }
  GLuint p_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(p_frag_shader, 1, &pfSrc, nullptr);
  glCompileShader(p_frag_shader);
  Path_selection.program = glCreateProgram();
  glAttachShader(Path_selection.program, pvertShader);
  glAttachShader(Path_selection.program, p_frag_shader);
  glLinkProgram(Path_selection.program);

  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vSrc, nullptr);
  glCompileShader(vertShader);
  GLint results;
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &results);
  if (results == GL_FALSE) {
    std::cerr << "widget shader was not initiated" << std::endl;
    while (1) {
    }
  }

  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fSrc, nullptr);
  glCompileShader(fragShader);

  widgetShader.program = glCreateProgram();
  glAttachShader(widgetShader.program, vertShader);
  glAttachShader(widgetShader.program, fragShader);
  glLinkProgram(widgetShader.program);
}

void Shaders::attach_shader(std::vector<float> vertecies,
                            std::vector<unsigned int> indicies,
                            ShaderInfo *shader, glm::vec4 color) {
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertecies.size() * sizeof(float),
               vertecies.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(sizeof(float) * 4));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int),
               indicies.data(), GL_STATIC_DRAW);
  glBindVertexArray(0);
  shader->projection =
      glm::ortho(0.0f, (float)Glwindow::get().width,
                 (float)Glwindow::get().highet, 0.0f, -1.0f, 1.0f);
  shader->model = glm::mat4(1.0f);
  shader->projLoc = glGetUniformLocation(widgetShader.program, "projection");
  shader->modelLoc = glGetUniformLocation(widgetShader.program, "model");
  shader->colorLoc = glGetUniformLocation(widgetShader.program, "costumColor");
  shader->myColor = jason::get().WIDGET_C.WIDGET_BACKROUND;
  shader->highlightLoc =
      glGetUniformLocation(widgetShader.program, "outLineColor");
  shader->highlightcolor = jason::get().WIDGET_C.WIDGET_HIGHLIGHT;
}

void Shaders::render_shader(ShaderInfo *shader) {
  glUseProgram(shader->program);
  glUniform4fv(shader->highlightLoc, 1, glm::value_ptr(shader->highlightcolor));
  glUniform4fv(shader->colorLoc, 1, glm::value_ptr(shader->myColor));
  glUniformMatrix4fv(shader->projLoc, 1, GL_FALSE,
                     glm::value_ptr(shader->projection));
  glUniformMatrix4fv(shader->modelLoc, 1, GL_FALSE,
                     glm::value_ptr(shader->model));
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, Maneger::get().widget_buffer.size() * 6,
                 GL_UNSIGNED_INT, 0);
}

void Shaders::init_shaders() {
  widget_shader_init("/home/nir/editor/shaders/shader.vert",
                     "/home/nir/editor/shaders/shader.frag");
  /// make them grabable via a jason path;

} // all shaders initiation goes here
ShaderInfo *Shaders::get_widget_shader() { return &widgetShader; }

void Shaders::attach_shader_selection() {
  glGenVertexArrays(1, &VaoPath);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(VaoPath);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vet_path.size() * sizeof(float),
               vet_path.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(sizeof(float) * 4));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_path.size() * sizeof(unsigned int),
               ind_path.data(), GL_STATIC_DRAW);
  glBindVertexArray(0);
  Path_selection.projection =
      glm::ortho(0.0f, (float)Glwindow::get().width,
                 (float)Glwindow::get().highet, 0.0f, -1.0f, 1.0f);
  Path_selection.model = glm::mat4(1.0f);
  Path_selection.projLoc =
      glGetUniformLocation(widgetShader.program, "projection");
  Path_selection.modelLoc = glGetUniformLocation(widgetShader.program, "model");
  Path_selection.colorLoc =
      glGetUniformLocation(widgetShader.program, "costumColor");
  Path_selection.myColor = jason::get().WIDGET_C.WIDGET_BACKROUND;
  Path_selection.highlightLoc =
      glGetUniformLocation(widgetShader.program, "outLineColor");
  Path_selection.highlightcolor = jason::get().WIDGET_C.WIDGET_HIGHLIGHT;
}
void Shaders::render_path_selection() {
  glUseProgram(Path_selection.program);
  glUniform4fv(Path_selection.highlightLoc, 1,
               glm::value_ptr(Path_selection.highlightcolor));
  glUniform4fv(Path_selection.colorLoc, 1,
               glm::value_ptr(Path_selection.myColor));
  glUniformMatrix4fv(Path_selection.projLoc, 1, GL_FALSE,
                     glm::value_ptr(Path_selection.projection));
  glUniformMatrix4fv(Path_selection.modelLoc, 1, GL_FALSE,
                     glm::value_ptr(Path_selection.model));
  glBindVertexArray(VaoPath);
  glDrawElements(GL_TRIANGLES, Maneger::get().widget_buffer.size() * 6,
                 GL_UNSIGNED_INT, 0);
}

void Shaders::build_shader_fr_path(const char *vertPath, const char *fragPath,
                                   GLuint vao, ShaderInfo *program) {
  std::string vertCode = LoadFile(vertPath);
  std::string fragCode = LoadFile(fragPath);

  const char *vSrc = vertCode.c_str();
  const char *fSrc = fragCode.c_str();

  GLuint pvertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(pvertShader, 1, &vSrc, nullptr);
  glCompileShader(pvertShader);
  GLint p_vert_resualt;
  glGetShaderiv(pvertShader, GL_COMPILE_STATUS, &p_vert_resualt);
  if (p_vert_resualt == GL_FALSE) {
    std::cerr << "general shader creation wasnt initialized\n " << vertPath
              << "\n " << fragPath << std::endl;
    while (1)
      ;
  }
  GLuint p_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(p_frag_shader, 1, &fSrc, nullptr);
  glCompileShader(p_frag_shader);
  program->program = glCreateProgram();
  glAttachShader(program->program, pvertShader);
  glAttachShader(program->program, p_frag_shader);
  glLinkProgram(program->program);
} // creation and compile shadercode into a spasific program make sure you put
  // your disried paths in the init functin make it hot swapable via the json
  // file
std::vector<float> vertex_ToolBar;
std::vector<unsigned int> ind_ToolBar;

void Shaders::init_Toolbar() {

  build_shader_fr_path("/home/nir/editor/shaders/toolbar/toolbar.vert",
                       "/home/nir/editor/shaders/toolbar/toolbar.frag",
                       ToolBarVao, &ToolBar_shader);
  std::cout << "shader was buildt" << std::endl;
  float width = (float)ToolBar::get().width;
  float highet = (float)ToolBar::get().highet;
  float x = 0.0f;
  float y = (float)ToolBar::get().y;
  std::cout << "parameters dclared " << std::endl;
  update_Tool_buffers(width, highet, x, y);
  std::cout << "updated toolbar" << std::endl;
  attach_Toolbar_Shader();
  std::cout << "attached toolbar_shader" << std::endl;
}

void Shaders::update_Tool_buffers(float boxWidth, float boxHight, float ceterX,
                                  float ceterY) {
  // also call this one on the init function actually make a semerate
  // shader_init for this type of shader
  vertex_ToolBar.clear();
  ind_ToolBar.clear();
  float left = ceterX;
  float right = ceterX + boxWidth;
  float top = ceterY;
  float bottom = ceterY + boxHight;
  std::cout << left << " left < " << right << "right < " << top << " top < "
            << bottom << "bott<< " << std::endl;
  vertex_ToolBar.push_back(left);
  vertex_ToolBar.push_back(top);
  vertex_ToolBar.push_back(0.0f);
  vertex_ToolBar.push_back(1.0f);
  vertex_ToolBar.push_back(1.0f);

  vertex_ToolBar.push_back(right);
  vertex_ToolBar.push_back(top);
  vertex_ToolBar.push_back(1.0f);
  vertex_ToolBar.push_back(1.0f);
  vertex_ToolBar.push_back(1.0f);

  vertex_ToolBar.push_back(right);
  vertex_ToolBar.push_back(bottom);
  vertex_ToolBar.push_back(1.0f);
  vertex_ToolBar.push_back(0.0f);
  vertex_ToolBar.push_back(1.0f);

  vertex_ToolBar.push_back(left);
  vertex_ToolBar.push_back(bottom);
  vertex_ToolBar.push_back(0.0f);
  vertex_ToolBar.push_back(0.0f);
  vertex_ToolBar.push_back(1.0f);

  ind_ToolBar.push_back(0);
  ind_ToolBar.push_back(1);
  ind_ToolBar.push_back(2);
  ind_ToolBar.push_back(0);
  ind_ToolBar.push_back(2);
  ind_ToolBar.push_back(3);
}

void Shaders::attach_Toolbar_Shader() {
  glGenVertexArrays(1, &ToolBarVao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(ToolBarVao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertex_ToolBar.size() * sizeof(float),
               vertex_ToolBar.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(sizeof(float) * 4));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               ind_ToolBar.size() * sizeof(unsigned int), ind_ToolBar.data(),
               GL_STATIC_DRAW);
  glBindVertexArray(0);
  ToolBar_shader.projection =
      glm::ortho(0.0f, (float)Glwindow::get().width,
                 (float)Glwindow::get().highet, 0.0f, -1.0f, 1.0f);
  ToolBar_shader.model = glm::mat4(1.0f);
  ToolBar_shader.projLoc =
      glGetUniformLocation(widgetShader.program, "projection");
  ToolBar_shader.modelLoc = glGetUniformLocation(widgetShader.program, "model");
  ToolBar_shader.colorLoc =
      glGetUniformLocation(widgetShader.program, "costumColor");
  ToolBar_shader.myColor = jason::get().WIDGET_C.WIDGET_BACKROUND;
  ToolBar_shader.highlightLoc =
      glGetUniformLocation(widgetShader.program, "outLineColor");
  ToolBar_shader.highlightcolor = jason::get().WIDGET_C.WIDGET_HIGHLIGHT;
}
// its probably stupid to do it that way but i forgot i made a general function
// to do this also wed need to add parameters later well im fuck i really hadnt
// thought of this for the futher make sure you add a genral way to add to all
// the shaders crist this is alot of work
void Shaders::render_Toolbar() {
  glUseProgram(ToolBar_shader.program);
  glUniform4fv(ToolBar_shader.highlightLoc, 1,
               glm::value_ptr(ToolBar_shader.highlightcolor));
  glUniform4fv(ToolBar_shader.colorLoc, 1,
               glm::value_ptr(ToolBar_shader.myColor));
  glUniformMatrix4fv(ToolBar_shader.projLoc, 1, GL_FALSE,
                     glm::value_ptr(ToolBar_shader.projection));
  glUniformMatrix4fv(ToolBar_shader.modelLoc, 1, GL_FALSE,
                     glm::value_ptr(ToolBar_shader.model));
  glBindVertexArray(ToolBarVao);
  glDrawElements(GL_TRIANGLES, Maneger::get().widget_buffer.size() * 6,
                 GL_UNSIGNED_INT, 0);
}
