#include "../includes/widgetManeger.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "../includes/shaderManeger.h"
int offset =1; 
void horizontal_cut(std::vector<Widget*>* f){
f->back()->width = f->back()->width/2;
f->push_back(new Widget{f->back()->highet-offset , f->back()->width-offset , f->back()->x+f->back()->width+offset,f->back()->y,(unsigned int)(f->size())*4});

  }
 
void verticle_cut(std::vector<Widget*>* f){
f->back()->highet = f->back()->highet/2 ; 
f->push_back(new Widget{f->back()->highet , f->back()->width , f->back()->x,f->back()->y +offset+ f->back()->highet,(unsigned int)(f->size())*4});
} 
void devide (int screenh , int screenw, int cuts , std::vector<Widget*>* final  ){
  for(int i=0  ; i < cuts ; i++){
  std::cout << i / 2 << std::endl ;
  if(i%2 == 0 ){
  horizontal_cut(final); 
  }else{ 
  verticle_cut(final); 
   

  }
}
}



void Maneger::initManeger(){
Widget * d = new Widget(Glwindow::get().highet, Glwindow::get().width  ,0 ,0, 0  ); 
widget_buffer.push_back(d);
number_of_cuts = 0   ; 
  glm::vec4 color (0.44f , 0.0f , 0.87f , 1.0f  );
  vertex_builder(); 
  Shaders::get().attach_shader(widget_vert, widget_indicies,&Shaders::get().widgetShader, jason::get().WIDGET_C.WIDGET_BACKROUND); 


} 

void Maneger::vertex_builder ( ){
widget_indicies.clear(); 
widget_vert.clear();

widget_buffer[current_widget]->selected = 1.0f ;

for(auto& single :widget_buffer){



  float x = single->x ; 
float y = single->y ; 
float w = single->width; 
float h = single->highet; 
unsigned int id = single->id; 
float a =  single->selected; 
std::cout << a << "selected"<< std::endl ; 
widget_vert.push_back(x); 
widget_vert.push_back(y); 
widget_vert.push_back(0.0f); 
widget_vert.push_back(0.0f); 
widget_vert.push_back(a); 

widget_vert.push_back(x+w); 
widget_vert.push_back(y); 
widget_vert.push_back(1.0f); 
widget_vert.push_back(0.0f); 
widget_vert.push_back(a); 

widget_vert.push_back(x+w); 
widget_vert.push_back(y+h); 
widget_vert.push_back(1.0f); 
widget_vert.push_back(1.0f); 
widget_vert.push_back(a); 


widget_vert.push_back(x); 
widget_vert.push_back(y+h); 
widget_vert.push_back(0.0f); 
widget_vert.push_back(1.0f); 
widget_vert.push_back(a); 

widget_indicies.push_back(id+ 0 ); 
widget_indicies.push_back(id+ 1 ); 
widget_indicies.push_back(id+ 2 ); 


widget_indicies.push_back(id+ 2 ); 
widget_indicies.push_back(id+ 3 ); 
widget_indicies.push_back(id+ 0 ); 
}
/*pretty stupid way to do it but fuck it*/
}





 void Maneger::calculate_cords(){
for(auto wi : widget_buffer ){
  delete wi ; 
}//reasorce intensive and unnecessiry but it works so fuck it 

widget_buffer.clear();


number_of_cuts++ ;



Widget * d = new Widget(Glwindow::get().highet, Glwindow::get().width  ,0 ,0, 0  ); 
widget_buffer.push_back(d);
   devide(Glwindow::get().width,Glwindow::get().highet, number_of_cuts, &widget_buffer); 
//do the math devide by number or cuts to pass to the vertex builder 
//we do this to calculate the screen position for each widget 

   vertex_builder();
//actually build the vertexarrey and indicies with the screencords from the widgetbuffer 
  Shaders::get().attach_shader(widget_vert, widget_indicies,&Shaders::get().widgetShader, jason::get().WIDGET_C.WIDGET_BACKROUND); 
//pass it to the shader for rendering later on 
   }


void Maneger::delete_widget(){
  if(current_widget != 0 ){ 
  number_of_cuts -=2; //move the cut twice back because calculate_cords adds one could work around it but im lazy 
  current_widget -- ; //move the the prev widget 
calculate_cords();
  }
}



void Maneger::renderW(){
Shaders::get().render_shader(&Shaders::get().widgetShader);
}

/*probably the most retarded and complicated way to move a widget
 the point it we need to move the current_widget back or forward and then 
 render the highlight on the shader so we recalculate the cords again and 
 nuke the buffers its stupid but were dealing with like 4 or 5 widgets this is 
 breakfeast for the gpu so fuck it */
void Maneger::move_current(int add_remove ){
     if(current_widget >= 0 && current_widget < widget_buffer.size() ){
     
   widget_buffer[current_widget]->selected = 0.0f ; 
       if(add_remove == -1&& current_widget == 0 ){
   std::cout << "add_remove == - 0 "<<std::endl ;
   } else
   {
     if(current_widget < widget_buffer.size()-1)
     current_widget += add_remove;
     else{
      if(add_remove == -1 )
     current_widget += add_remove;
     }
   vertex_builder();
   glm::vec4 color (0.44f , 0.0f , 0.87f , 1.0f  );
  Shaders::get().attach_shader(widget_vert, widget_indicies,&Shaders::get().widgetShader, jason::get().WIDGET_C.WIDGET_BACKROUND); 
   
   }
  
    }


   }





