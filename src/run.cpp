#include "../includes/run.h"
#include <GLFW/glfw3.h>

void run::start() {

  glfwSetKeyCallback(Glwindow::get().window, Input::key_call_back);
  Input::get().bind_keys(
      jason::get().keyMap[jason::get().WIDGET_K.SPAWN_WIDGET],
      []() { Maneger::get().calculate_cords(); });
  Input::get().bind_keys(
      jason::get().keyMap[jason::get().WIDGET_K.MOVE_CURSER_F],
      []() { Maneger::get().move_current(1); });
  Input::get().bind_keys(
      jason::get().keyMap[jason::get().WIDGET_K.MOVE_CURSER_B],
      []() { Maneger::get().move_current(-1); });
  Input::get().bind_keys(
      jason::get().keyMap[jason::get().WIDGET_K.DELETE_WIDGET],
      []() { Maneger::get().delete_widget(); });
  Input::get().bind_keys(jason::get().keyMap[jason::get().TOGGLE_PATH],
                         []() { pathManeger::get().on_Click_Toggele_Path(); });
  Input::get().bind_keys(jason::get().keyMap[jason::get().RELOAD_TOOLBAR],
                         []() { ToolBar::get().init_tool(); });
  ///////////////////////////////////////////input calls and sets for function
  /// for spasific input for example we use input::get() to get the bind key
  /// function and then we can take a json parameter as a key and hook it to the
  /// right function

  glViewport(0, 0, Glwindow::get().width, Glwindow::get().highet);

  ToolBar::get().init_tool();
  Shaders::get().init_Toolbar();
  pathManeger ::get().init_path();
  Maneger::get().initManeger();
  TextShader::get().init_text();
  // init functions to load on start mostly
  // feeding screen stuff and more paremeters for the render pipeline
  // make sure you put all the init functions there for
  // orginazation perpuse

  TextShader::get().build_string("std::cout << hello world << std::endl",
                                 500.0f, 500.0f); // delete this function after
                                                  // you finish this is test
                                                  // function not final build

  TextShader::get().build_string("std::cout << hello world << std::endl",
                                 700.0f, 700.0f);
  TextShader::get().path_build_string("~/home/nir/program/",
                                      (pathManeger::get().x + 1.0f) * 5.0f,
                                      (pathManeger::get().y + 64.0f));
  // disable some opengl stuff here
  //
  glDisable(GL_DEPTH_TEST);
}
// main engine loop function this is where we draw all the stuff
// todo for later devide the renederes to a few functions
// first layer core engine
// second layer text and other stuff
// third layer for the path Maneger and the toolbar at the bottom

void run::loop() {
  while (!glfwWindowShouldClose(Glwindow::get().window)) {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // flash the screen before rendering pretty self explanitory make sure
    // renders come after this and input before
    Maneger::get().renderW();
    TextShader::get().flush_render();
    pathManeger::get().render_path();
    Shaders::get().render_Toolbar();
    TextShader::get().path_flush_render();
    glfwPollEvents(); // move the pull events to the start we wanna do input and
                      // then do rendering not the oposit
    glfwSwapBuffers(
        Glwindow::get().window); // keep this at the end of the renderer
  }

  glfwTerminate();
}
