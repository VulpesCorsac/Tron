#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
layout(location = 3) in vec3 vNormal;

out vec2 UV;

out vec3 pos_wsp;
out vec3 nor_wsp;

/*
out vec3 eye_csp;
out vec3 ldir_csp;*/

uniform mat4 MVP;
uniform mat4 M;

/*
uniform mat4 MTI_V;
uniform mat4 MV;
uniform mat4 V;

uniform vec3 lts_p[4];*/


void main(){   
	gl_Position =  MVP * vec4(vPos,1);
	UV = vUV;

	pos_wsp = (M * vec4(vPos,1)).xyz;
	nor_wsp = normalize((M * vec4(vNormal,0)).xyz);

	/* nah i won't do traditional omni lightning probably. 
	vec3 vp_csp = ( MV * vec4(vPos,1)).xyz;
	eye_csp = vec3(0,0,0) - vp_csp;
	
	for (int i = 0; i < 4; i++)
	{
		vec3 lpos_csp = ( V * vec4(lts_p[i],1)).xyz;
		ldir_csp = lpos_csp + eye_csp;
	}*/
 }