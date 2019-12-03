#version 330 core

//to represent material
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

//to give info about the light to the shader
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
 
out vec3 fFragColor;


vec3 blinnPhong(vec3 position_vs, vec3 normal_vs)
{
	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = normalize(uLightPos_vs - vPosition_vs);
	vec3 halfVector = (w_zero + w_i) / 2;
	//distance à la lumière
	float d = distance(vPosition_vs, uLightPos_vs);

	//wi: uLightPos_vs calculé à partir pos frag et pos lumière
	//Li uLightIntensity, atténué en fonction de la distance à la lumière
	//halfVector : calculer wo (vecteur pointant vers caméra, ie opposé position frag normalisée)(normalize(-vPosition_vs))
	//attention: fonction dot pour prod scalaires, et pow pour élévation puissance

	return (uLightIntensity / (d * d)) * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}

void main() {
	fFragColor = blinnPhong(vPosition_vs, normalize(vNormal_vs));

};
 

