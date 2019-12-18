#version 330 core

//to represent material
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

//to give info about the light to the shader
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;


uniform sampler2D uTexture;

 
out vec3 fFragColor;

vec3 blinnPhong(vec3 position_vs, vec3 normal_vs)
{
	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = normalize(-uLightDir_vs);
	vec3 halfVector = (w_zero + w_i) / 2;

	//wi: uLightDir_vs normalisé
	//Li uLightIntensity
	//halfVector : calculer wo (vecteur pointant vers caméra, ie opposé position frag normalisée)(normalize(-vPosition_vs))
	//attention: fonction dot pour prod scalaires, et pow pour élévation puissance

	return uLightIntensity * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}

void main() {
	fFragColor = blinnPhong(vPosition_vs, normalize(vNormal_vs))*texture( uTexture, vTexCoords ).xyz;

};
 

