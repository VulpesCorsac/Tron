#version 330 core

in vec2 UV;
out vec4 color;
uniform sampler2D cTex;
uniform vec4 cClr;

void main(){
	color = texture2D( cTex, UV ) * cClr;
	//color.w = 1;
  	//color = vec4(1,0,1,1);
}