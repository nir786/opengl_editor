#pragma once
#include <string> 
#include <iostream>
#include <fstream> 
#include <sstream> 
#include "../editor/glad/glad.h"
#include "freetype/freetype.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

class TextM{
  public : 
void init_textm ( ); 
void build_text (std::string word );  











    static TextM& get(){ 
    static TextM instance ; 
    return instance ; 
    }

  private: 
    TextM()= default ; 




} ; 
