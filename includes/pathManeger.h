#pragma once

#include <functional>
#include <vector>
#include <iostream>
#include "../editor/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "window.h" 
#include "widget.h"
#include "jasonloader.h"
#include "shaderManeger.h"

class pathManeger{
  public:
int x ,y , highet, width ;
int is_toggeled;
std::string command_line_buffer; 



void init_path (); 
void render_path(); 
void on_Screen_Resize(); 
void on_Click_Toggele_Path(); 











    static pathManeger& get(){
  static pathManeger instance ; 
  return instance; 
}








private :
pathManeger() = default; 





}; 
