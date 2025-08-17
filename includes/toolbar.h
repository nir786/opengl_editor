
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



class ToolBar{
  public:
    int x , y , width , highet ; 
    std::vector<std::function<void()>> elements; 

    static ToolBar& get(){ 
     static ToolBar instance;  
     return instance ; 
    }

void init_tool(); 
void render_tool();/// when adding elements make sure you put them in here  
void reload_tool(); 






  private: 
    ToolBar() =default;    


}; 






