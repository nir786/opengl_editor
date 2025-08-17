#version 330 core 
in vec2 TexCoords;
in float selected; 






out vec4 FragColor; 

uniform vec4 costumColor ; 
uniform vec4 outLineColor; 
float radius = 1 ;  



void main ( ){




  float border = 0.004;
bool isOutline= (TexCoords.x < border || TexCoords.x > 1.0 -border+0.001 ||TexCoords.y < border || TexCoords.y > 1.0 -border) ;

bool isselected = selected> 0.5 ;
  if(isselected && isOutline ){
  FragColor =  outLineColor; 
}else {
  FragColor = costumColor ; 
}



 // FragColor = costumColor; 
}
