#version 330 core 

in vec3 vNormal_vs;
in vec3 vFragColor;

out vec3 fFragColor;

void main() {
	vec3 color = vFragColor;
	vec3 LightDir = normalize(vec3(10.0, -100.0, 15.0));
	float luminosityDirLight = max(-dot(vNormal_vs, LightDir), 0.);
	float ambiantLightIntensity = 0.1;
	float totalLuminosity = min(luminosityDirLight + ambiantLightIntensity, 1.);
	fFragColor = color * totalLuminosity; 
}
