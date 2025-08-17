#pragma once

#include <functional>
#include <vector>
#include <iostream>
#include "../editor/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "window.h" 
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <fstream> 
#include <sstream> 
#include <string>
class Widget{
  public:
  int highet; 
  int width;
  int x , y ;
  unsigned int id ;
  float selected; 
  //std::vector<float[]> vertecies; 

  //std::vector<unsigned int [] > indicies ; 
  Widget(int h , int w , int pox,int poy , unsigned int id  );  
  void render() ;




};
