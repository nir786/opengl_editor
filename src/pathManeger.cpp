///loook at the bottom of the shadermaneger we created new shaders 
///just need to add a few functions here like create path maneger class and so on 
///also need to make keybinds for it simple 
///go fuck yourself 
#include "../includes/pathManeger.h"


void pathManeger::init_path (){
 width = Glwindow::get().highet; 
 highet = Glwindow::get().width/4;  
 std::cout<<width<<" width" <<Glwindow::get().highet <<std::endl; 
 x  = Glwindow::get().highet/4 ; 
 y  = 0 ; 
 
 Shaders::get().create_path((float)width, (float)highet ,(float) x ,(float) y); 







}
void pathManeger::on_Click_Toggele_Path(){
init_path(); 
if(is_toggeled == 0){ 
  Shaders::get().attach_shader_selection(); 
  is_toggeled =1 ; 
}else{ 
is_toggeled =0 ; 
}

}



void pathManeger::render_path() {
if(is_toggeled == 1){ 
  Shaders::get().render_path_selection(); 
}



}
void pathManeger::on_Screen_Resize() { }//addlater 


