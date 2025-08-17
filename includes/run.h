#pragma once 
#include <functional>
#include <vector>
#include <iostream>
#include "../editor/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "widgetManeger.h"
#include "inputHandler.h"
#include "jasonloader.h"
#include "pathManeger.h" 
#include "toolbar.h"
#include "shadersText.h"
class run{
  public: 
    std::vector<std::function<void()>> updates ;
    std::vector<std::function<void()>> inputs;
    std::vector<std::function<void()>> renders;
   static run& get(){
     static run instance; 
     return instance; 
   }
   void start(); 
   void loop(); 


  private: 
   run()=  default; 




}; 
