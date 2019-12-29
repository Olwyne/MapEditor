#version 330 core


in vec3 vPosition_vs;
in vec3 vNormal_vs;
 
out vec3 fFragColor;


void main() {
	fFragColor = normalize(vNormal_vs);

};
 

