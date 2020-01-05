#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;
out vec2 vVertexPosition;

mat3 scale(float sx, float sy)
{
	return mat3(vec3(sx,0,0), vec3(0,sy,0), vec3(0,0,1));
}

mat3 translate(float tx, float ty)
{
	return mat3(vec3(1,0,0), vec3(0,1,0), vec3(tx,ty,1));
}

mat3 rotate(float a)
{
	float cos_a = cos( radians(a) );
	float sin_a = sin( radians(a) );
	return mat3(vec3(cos_a,sin_a,0), vec3(-sin_a,cos_a,0), vec3(0,0,1));
}


void main() {

	vVertexPosition = aVertexPosition;

	mat3 MS = scale(0.5,0.5);
	mat3 MT = translate(0.5,0);
	mat3 MR = rotate(45);
	vec2 transformed = (MS*MR*MT*vec3(aVertexPosition,1)).xy;

	gl_Position = vec4(aVertexPosition, 0, 1);
	
};
