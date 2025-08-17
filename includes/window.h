#pragma once

#include "../editor/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
class Glwindow{
  public: 
  GLFWwindow * window = nullptr; 
  int width ; 
  int highet; 
  const char* name ; 
void init (int , int ,const char*) ; 
//~Glwindow( ); 
 
static Glwindow& get(){
static Glwindow instance; 
return instance ;
}
//window
private : 
Glwindow()= default ; 

};
