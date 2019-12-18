#version 330

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs; //position of vertex transformed in View
out vec3 vNormal_vs; //normal of vertex transformed in View
out vec2 vTexCoords; //coordinates of vertex's texture


void main() {

	//homogenous coordinates
	vec4 vertexPosition = vec4(aVertexPosition, 1);
	vec4 vertexNormal = vec4(aVertexNormal, 0);

	//out values
	vPosition_vs = vec3(uMVMatrix * vertexPosition);
	vNormal_vs = vec3(uNormalMatrix * vertexNormal);
	vTexCoords = aVertexTexCoords;

	//project position
	gl_Position = uMVPMatrix * vertexPosition;
	
};

