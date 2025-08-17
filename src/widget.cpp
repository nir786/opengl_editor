#include "../includes/widget.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "../includes/widgetManeger.h" 
Widget::Widget(int h , int w , int pox,int poy , unsigned int id  ): highet(h), width(w) , x(pox) , y(poy),id(id){
float x = pox ;
float y = poy ; 
float high = h ; 
float wid = w ;
selected= 0.0f;}  


void Widget::render(){
// Shaders::get().render_shader(&Shaders::get().widgetShader);
}

