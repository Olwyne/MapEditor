#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;
layout(location = 2) in vec3 aVertexNormal;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs; //position of vertex transformed in View
out vec3 vNormal_vs; //normal of vertex transformed in View
out vec3 vFragColor;


void main() {

	//homogenous coordinates
	vec4 vertexPosition = vec4(aVertexPosition, 1);
	vec4 vertexNormal = vec4(aVertexNormal, 0);

	//out values
	vFragColor = aVertexColor;
	vPosition_vs = vec3(uMVMatrix * vertexPosition);
	vNormal_vs = vec3(uNormalMatrix * vertexNormal);

	//project position
	gl_Position = uMVPMatrix * vertexPosition;
	
};

