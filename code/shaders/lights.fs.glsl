#version 330 core 

in vec3 vNormal_vs;
in vec3 vFragColor;
in vec3 vPosition_vs;
in vec3 vPosInWorldSpace;

out vec3 fFragColor;

//to give info about the light to the shader
uniform vec3 uLightDir_vs;
uniform float uLightIntensity;
uniform vec3 uLightPos;
uniform float ambiantLightIntensity;

void main() {
	vec3 color = vFragColor;
	vec3 dirBetweenPointLightAndCurrentPixel = normalize(vPosInWorldSpace-uLightPos);
	
	float luminosityDirLight = max(-dot(vNormal_vs, uLightDir_vs), 0.)*(uLightIntensity);
	float d = length(vPosInWorldSpace-uLightPos);
	float luminosityPointLight = max(-dot(vNormal_vs, dirBetweenPointLightAndCurrentPixel  ), 0.);
	
	float totalLuminosity = min(luminosityDirLight + luminosityPointLight + ambiantLightIntensity, 1.);
	fFragColor = vec3(color * totalLuminosity); 
} 