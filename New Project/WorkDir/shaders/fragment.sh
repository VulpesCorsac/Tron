#version 330 core

in vec2 UV;
out vec4 color;
uniform sampler2D texSampler;
uniform vec4 clcl;

void main(){
	color = texture2D( texSampler, UV ) * clcl;
	//color = clcl;
	//color = vec4(1, 0, 1, 1);
}