#include "../includes/run.h"
#include <GLFW/glfw3.h>


void run::start(){

  glfwSetKeyCallback(Glwindow::get().window, Input::key_call_back );
  Input::get().bind_keys(jason::get().keyMap[jason::get().WIDGET_K.SPAWN_WIDGET], [](){Maneger::get().calculate_cords();}); 
  Input::get().bind_keys(jason::get().keyMap[jason::get().WIDGET_K.MOVE_CURSER_F], [](){Maneger::get().move_current(1);});
  Input::get().bind_keys(jason::get().keyMap[jason::get().WIDGET_K.MOVE_CURSER_B], [](){Maneger::get().move_current(-1);});
  Input::get().bind_keys(jason::get().keyMap[jason::get().WIDGET_K.DELETE_WIDGET], [](){Maneger::get().delete_widget();});
  Input::get().bind_keys(jason::get().keyMap[jason::get().TOGGLE_PATH], [](){pathManeger::get().on_Click_Toggele_Path();});
  Input::get().bind_keys(jason::get().keyMap[jason::get().RELOAD_TOOLBAR], [](){ToolBar::get().init_tool();});
  glViewport(0 ,0 , Glwindow::get().width , Glwindow::get().highet); 
  
  ToolBar::get().init_tool(); 
  Shaders::get().init_Toolbar() ; 
  pathManeger ::get().init_path();
  Maneger::get().initManeger();
  TextShader::get().init_text(); 
  std::cout << "sagfault at init"<<std::endl; 
  TextShader::get().build_string("std::cout << hello world << std::endl"); 
  std::cout << "sagfault at build"<<std::endl; 
  //open file pull colors 
//read settings and slot them 
//asign funcitons 
 glDisable(GL_DEPTH_TEST); 
 } 
void run::loop(){
  while(!glfwWindowShouldClose(Glwindow::get().window)){

//input below

//rendering below
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
// call events or swap buffers

Maneger::get().renderW(); 
pathManeger::get().render_path(); 
Shaders::get().render_Toolbar(); 
TextShader::get().flush_render();
glfwPollEvents() ; 
  glfwSwapBuffers(Glwindow::get().window); 
}

glfwTerminate(); 

} 


