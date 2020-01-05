#version 330 core

in vec3 vFragColor;
in vec2 vVertexPosition;

out vec3 fFragColor;

float halo(float alpha, float beta, vec2 position)
{
	float dist = distance(position, vec2(0));
	return alpha * exp(-beta * dist * dist);
} 

void main() {
	fFragColor = halo(200, 70, vVertexPosition)*vFragColor;
};
