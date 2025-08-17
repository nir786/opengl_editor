#pragma  once 
#include <functional>
#include <vector>
#include <iostream>
#include "../editor/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "window.h" 
#include "widget.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <fstream> 
#include <sstream> 
#include <string>
#include "shaderManeger.h"
#include "widgetManeger.h"
#include "jasonloader.h"
#include "toolbar.h"

typedef struct {
 glm::mat4 projection ; 
 glm::mat4 model; 
 glm::vec4 myColor;
 GLint colorLoc;  
 GLint projLoc;
 GLint modelLoc; 
 GLuint program;
 glm::vec4 highlightcolor;
GLint highlightLoc; 
GLint isselected; 
}ShaderInfo; 

class Shaders{
  public : 
    //add shaders here
    //make all of these into a vector for hotswap shaders on the file also inherit json 
  ShaderInfo widgetShader;
  ShaderInfo Path_selection;
  ShaderInfo ToolBar_shader; 
  GLuint vao ,vbo , ebo ;
  GLuint VaoPath;
  GLuint ToolBarVao; 
  static Shaders& get(){
     static Shaders instance; 
     return instance; 
   }
  void init_shaders (); //all shaders initiation goes here 
  ShaderInfo* get_widget_shader(  );
  void attach_shader( std::vector<float> vertecies , std::vector<unsigned int > indicies, ShaderInfo * s ,glm::vec4 color); 

  void render_shader(ShaderInfo* s ); 
   
  void attach_shader_selection(); 
  void render_path_selection(); 
  void create_path(float boxWidth , float boxHight , float ceterX , float ceterY); 
  


  void init_Toolbar(); 
  void update_Tool_buffers( float boxWidth, float boxHight , float ceterX ,float  ceterY ); 
  void build_shader_fr_path(const char* vertPath ,const char * fragPath , GLuint vao, ShaderInfo* program ); 
  void attach_Toolbar_Shader( ); 
  void render_Toolbar(); 


  private: 

void widget_shader_init (const char * , const char * );
  Shaders()=  default; 



}; 
