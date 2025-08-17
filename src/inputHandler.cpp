#include "../includes/inputHandler.h"
#include <GLFW/glfw3.h>


 void Input::key_call_back(GLFWwindow * window , int key , int scancode , int action , int mods){
if(action == GLFW_PRESS){
  Input::get().Trigger(key); 
}

}
 void Input::bind_keys(int key , std::function<void()>callback ){
//read from jason file for macros and function name 
keymap[key]= callback ; 
 }
   void Input::Trigger(int key ){
     auto it = keymap.find(key); 
     if(it != keymap.end()){
       it->second(); 
     }
   } 
   void Input::listen_macros(){

   } 


