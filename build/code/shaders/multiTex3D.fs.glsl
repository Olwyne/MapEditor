#version 330 core

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;
 
out vec3 fFragColor;


void main() {
	//fFragColor = normalize(vNormal_vs);
	vec3 img_texture =  texture(uEarthTexture, vTexCoords).xyz;
	vec3 img_texture2 =  texture(uCloudTexture, vTexCoords).xyz;
	fFragColor = img_texture + img_texture2;
};
 

