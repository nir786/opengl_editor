
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
class Maneger{
  public:
std::vector<Widget*> widget_buffer ;
std::vector<float> widget_vert ; 
std::vector<unsigned int > widget_indicies; 
int number_of_cuts ;
int current_widget; 
   static Maneger& get(){
     static Maneger instance; 
     return instance; 
   }


   void initManeger(); 
   void renderW(); 
   void pass_vertecies() ; 


   
   void vertex_builder ( );
   void calculate_cords() ; 
   void spawn_widget(); 

   void move_current(int add_remove); 
   void delete_widget(); 






  private: 
   Maneger()=  default; 







};
