#version 330

uniform sampler2D uTexture;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;
 
out vec3 fFragColor;


void main() {
	vec3 img_texture =  texture(uTexture, vTexCoords).xyz;
	fFragColor = img_texture;
};

