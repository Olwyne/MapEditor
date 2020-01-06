#version 330 core 

in vec3 vNormal_vs;
in vec3 vFragColor;
in vec3 vPosition_vs;
in vec3 vPosInWorldSpace;

out vec3 fFragColor;


//to give info about the light to the shader
uniform vec3 uLightDir_vs;
uniform float uLightDirIntensity;
uniform vec3 uLightPointPos1;
uniform vec3 uLightPointPos2;
uniform float ambiantLightIntensity;
uniform float uLightPointIntensity1;
uniform float uLightPointIntensity2;

void main() {
	vec3 color = vFragColor;

	vec3 dirBetweenPointLightAndCurrentPixel1 = normalize(vPosInWorldSpace-uLightPointPos1);
	vec3 dirBetweenPointLightAndCurrentPixel2 = normalize(vPosInWorldSpace-uLightPointPos2);

	float luminosityDirLight = max(-dot(vNormal_vs, uLightDir_vs), 0.)*(uLightDirIntensity);
	float luminosityPointLight1 = max(-dot(vNormal_vs, dirBetweenPointLightAndCurrentPixel1), 0.)*uLightPointIntensity1;
	float luminosityPointLight2 = max(-dot(vNormal_vs, dirBetweenPointLightAndCurrentPixel2), 0.)*uLightPointIntensity2;

	//make sure the result isn't bigger than 1
	float totalLuminosity = min(luminosityDirLight + luminosityPointLight1 + luminosityPointLight2 + ambiantLightIntensity, 1.);
	fFragColor = vec3(color * totalLuminosity); 
} 