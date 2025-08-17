#include "../includes/toolbar.h"

void ToolBar::init_tool(){
 width = Glwindow::get().width; 
 highet = Glwindow::get().highet/25  ;//make these values changeable via the json file  
 x  = 0 ; //starts as full width and hight no centering 
 y  = Glwindow::get().highet -highet    ; 
// Shaders::get().update_Tool_buffers(width , highet , x , y );  
 std::cout <<width << "widget width"<<std::endl;

} 
void render_tool(); 
void reload_tool(); 


