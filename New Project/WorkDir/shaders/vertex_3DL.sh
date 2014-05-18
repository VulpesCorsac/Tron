#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;

out vec2 UV;
uniform mat4 MVP;

void main(){   
	gl_Position =  MVP * vec4(vPos,1);
	UV = vUV;
 }