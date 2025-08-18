#include "../includes/window.h"
#include <GLFW/glfw3.h>
void frame_buffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  glfwGetFramebufferSize(Glwindow::get().window, &Glwindow::get().width,
                         &Glwindow::get().highet);
}
void Glwindow::init(int h, int w, const char *n) {
  highet = h;
  width = w;
  name = n;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  window = glfwCreateWindow(width, highet, name, NULL, NULL);
  if (!window) {
    std::cout << "failed to create window " << std ::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "failed to intitialze glad" << std ::endl;
  }

  glViewport(0, 0, w, h);

  glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
}
// Glwindow::~Glwindow( ){
// glfwTerminate();
// }

// window
