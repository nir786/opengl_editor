#pragma once 

#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include "../editor/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "widgetManeger.h"
#include "inputHandler.h"
#include "../json.hpp"
typedef struct{
  std::string MOVE_CURSER_F;  
  std::string SPAWN_WIDGET; 
  std::string DELETE_WIDGET; 
  std::string MOVE_CURSER_B; 
}widgetKeys;

typedef struct{
  glm::vec4 WIDGET_BACKROUND;
  glm::vec4 WIDGET_HIGHLIGHT; 
}widgetColors; 



using json = nlohmann::json; 
class jason{
  public:
widgetColors WIDGET_C ; 
widgetKeys   WIDGET_K ;
std::string TOGGLE_PATH; 
std::string RELOAD_TOOLBAR; 


std::unordered_map<std::string , int> keyMap={
  {"A", GLFW_KEY_A}, {"B", GLFW_KEY_B}, {"C", GLFW_KEY_C}, {"D", GLFW_KEY_D},
    {"E", GLFW_KEY_E}, {"F", GLFW_KEY_F}, {"G", GLFW_KEY_G}, {"H", GLFW_KEY_H},
    {"I", GLFW_KEY_I}, {"J", GLFW_KEY_J}, {"K", GLFW_KEY_K}, {"L", GLFW_KEY_L},
    {"M", GLFW_KEY_M}, {"N", GLFW_KEY_N}, {"O", GLFW_KEY_O}, {"P", GLFW_KEY_P},
    {"Q", GLFW_KEY_Q}, {"R", GLFW_KEY_R}, {"S", GLFW_KEY_S}, {"T", GLFW_KEY_T},
    {"U", GLFW_KEY_U}, {"V", GLFW_KEY_V}, {"W", GLFW_KEY_W}, {"X", GLFW_KEY_X},
    {"Y", GLFW_KEY_Y}, {"Z", GLFW_KEY_Z},

    // Numbers
    {"0", GLFW_KEY_0}, {"1", GLFW_KEY_1}, {"2", GLFW_KEY_2}, {"3", GLFW_KEY_3},
    {"4", GLFW_KEY_4}, {"5", GLFW_KEY_5}, {"6", GLFW_KEY_6}, {"7", GLFW_KEY_7},
    {"8", GLFW_KEY_8}, {"9", GLFW_KEY_9},

    // Special
    {"SPACE", GLFW_KEY_SPACE},
    {"ENTER", GLFW_KEY_ENTER},
    {"TAB", GLFW_KEY_TAB},
    {"ESCAPE", GLFW_KEY_ESCAPE},
    {"BACKSPACE", GLFW_KEY_BACKSPACE},
    {"DELETE", GLFW_KEY_DELETE},
    {"INSERT", GLFW_KEY_INSERT},
    {"LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT},
    {"RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT},
    {"LEFT_CTRL", GLFW_KEY_LEFT_CONTROL},
    {"RIGHT_CTRL", GLFW_KEY_RIGHT_CONTROL},
    {"LEFT_ALT", GLFW_KEY_LEFT_ALT},
    {"RIGHT_ALT", GLFW_KEY_RIGHT_ALT},

    // Arrows
    {"UP", GLFW_KEY_UP},
    {"DOWN", GLFW_KEY_DOWN},
    {"LEFT", GLFW_KEY_LEFT},
    {"RIGHT", GLFW_KEY_RIGHT},

    // Function keys
    {"F1", GLFW_KEY_F1}, {"F2", GLFW_KEY_F2}, {"F3", GLFW_KEY_F3},
    {"F4", GLFW_KEY_F4}, {"F5", GLFW_KEY_F5}, {"F6", GLFW_KEY_F6},
    {"F7", GLFW_KEY_F7}, {"F8", GLFW_KEY_F8}, {"F9", GLFW_KEY_F9},
    {"F10", GLFW_KEY_F10}, {"F11", GLFW_KEY_F11}, {"F12", GLFW_KEY_F12}
}; 

static jason& get(){
static jason instance; 
return instance; 
} 
void init(){

  std::ifstream file("jasonfiles/settings.json") ;
  if(!file.is_open()){
    std::cerr << "failed to fetch file"<<std::endl;
  }
  std::stringstream buffer ; 
  buffer << file.rdbuf();
  std::string filecontent = buffer.str(); 
  std::cout <<"raw file\n" << filecontent << std::endl; 
  //save jason
  json q = json::parse(buffer , nullptr , false);
  
   if(q.is_discarded()){
     std::cerr << "invalid json or parse faild\n" ; 
   }else{ 
     std::cout << "parsed json "<< std::endl ; 
   }




   WIDGET_K.DELETE_WIDGET = q["delete_widget"].get<std::string>(); 
   WIDGET_K.MOVE_CURSER_B = q["move_back_widget"]; 
   WIDGET_K.MOVE_CURSER_F=  q["move_farward_widget"]; 
   WIDGET_K.SPAWN_WIDGET =  q["spawn_widget"]; 
  TOGGLE_PATH = q["toggle_path"]; 
  RELOAD_TOOLBAR = q["reload_Toolbar"]; 
  auto arr = q["backround_color"] ; 
   WIDGET_C.WIDGET_BACKROUND = glm::vec4{arr[0], arr[1], arr[2], arr[3]}; 
   for(auto & single :arr ){
  std::cout <<single << std::endl; 
  }

std::cout <<std::endl ; 
 auto ar = q["hightlight_color"] ; 

   WIDGET_C.WIDGET_HIGHLIGHT = glm::vec4{ar[0], ar[1], ar[2], ar[3]}; 
for(auto & single :ar ){
  std::cout <<single << std::endl; 
}
 

  }


























private:
jason()= default ; 



};

