#version 330 core 

in vec3 vNormal_vs;
in vec3 vFragColor;
in vec3 vPosition_vs;

out vec3 fFragColor;

//to represent material
uniform vec3 uDiffuse;
uniform vec3 uGlossy;
uniform float uShininess;

//to give info about the light to the shader
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(vec3 position_vs, vec3 normal_vs)
{
	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = normalize(-uLightDir_vs);
	vec3 halfVector = (w_zero + w_i) / 2;

	//wi: uLightDir_vs normalisé
	//Li uLightIntensity
	//halfVector : calculer wo (vecteur pointant vers caméra, ie opposé position frag normalisée)(normalize(-vPosition_vs))
	//attention: fonction dot pour prod scalaires, et pow pour élévation puissance

	return uLightIntensity * ( uDiffuse * ( dot(w_i, normal_vs ) ) + uGlossy * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}

void main() {
	vec3 color = vFragColor;
	//vec3 LightDir = normalize(vec3(10.0, -100.0, 15.0));
	float luminosityDirLight = max(-dot(vNormal_vs, uLightDir_vs), 0.);
//	float ambiantLightIntensity = 0.1;
	vec3 totalLuminosity = min(uLightDir_vs + uLightIntensity, 1.);
	fFragColor = color * totalLuminosity; 
//	fFragColor = color*blinnPhong(vPosition_vs, normalize(vNormal_vs));

}