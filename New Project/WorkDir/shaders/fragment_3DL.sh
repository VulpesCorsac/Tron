#version 330 core

in vec2 UV;
in vec3 pos_wsp;
in vec3 nor_wsp;


out vec4 color;
uniform sampler2D cTex;

uniform vec4 cClr;

uniform float refl;

void main(){
	color = texture2D( cTex, UV ) * cClr;

	vec3 norm = normalize(nor_wsp);

	float lk1 = abs(sin(pos_wsp.z / 15.0 * 3.14159));
	float lk2 = 1-lk1;
	float lk3 = abs(sin(pos_wsp.x / 15.0 * 3.14159));
	float lk4 = 1-lk3;
	
	vec3 nl = normalize(vec3(0.5, 1, 0));
	nl.y *= refl;
	float k1 = clamp( dot( norm, nl ) * 0.7 * lk1, 0,1 );
	
	vec3 nl2 = normalize(vec3(-0.5, 1, 0));
	nl2.y *= refl;
	float k2 = clamp( dot( norm, nl2 ) * 0.7 * lk2, 0,1 );
	
	vec3 nl3 = normalize(vec3(0, 1, 0.5));
	nl3.y *= refl;
	float k3 = clamp( dot( norm, nl3 ) * 0.7 * lk3, 0,1 );
	
	vec3 nl4 = normalize(vec3(0, 1, -0.5));
	nl4.y *= refl;
	float k4 = clamp( dot( norm, nl4 ) * 0.7 * lk4, 0,1 );

	float k = clamp( 0.2 + k1 + k2 + k3 + k4, 0, 1);

	color.xyz = color.xyz * k;
}