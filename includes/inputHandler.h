#pragma once 

#include <functional>
#include <vector>
#include <iostream>
#include "../editor/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "widgetManeger.h"
#include <unordered_map>
#include <functional>

class Input {

  public:
  static Input& get(){
     static Input instance; 
     return instance; 
   }
   void bind_keys(int key , std::function<void()>callback ); 
   void Trigger(int key ); 
   void listen_macros() ; 
  static void key_call_back( GLFWwindow * window , int key , int scancode , int action , int mods); 




  private: 
 Input() = default ; 
  std::unordered_map<int , std::function<void()>> keymap ;  
};
