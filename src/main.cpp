
#include "../editor/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "../includes/window.h"
#include "../includes/run.h"
#include "../includes/shaderManeger.h"
#include "vector"
#include "../includes/jasonloader.h"

int main(){

 jason::get().init(); 
  Glwindow::get().init(800 , 600 , "myapp"); 
  //update 
  Shaders::get().init_shaders();
  run::get().start();  
  run::get().loop();  
 jason::get().init(); 

  std::cout<<jason::get().WIDGET_K.DELETE_WIDGET <<std::endl; 













  return 0 ; 
}
