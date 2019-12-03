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
	//fFragColor = length(fract(5.0 * vVertexPosition))*vFragColor;
	//fFragColor = length(abs(fract(5.0 * vVertexPosition) * 2.0 - 1.0))*vFragColor;
	//fFragColor = mod(floor(10.0 * vVertexPosition.x) + floor(10.0 * vVertexPosition.y), 2.0)*vFragColor;
	//fFragColor = smoothstep(0.3, 0.32, length(fract(5.0 * vVertexPosition) - 0.5))*vFragColor;
	//fFragColor =smoothstep(0.4, 0.5, max(abs(fract(8.0 * vVertexPosition.x - 0.5 * mod(floor(8.0 * vVertexPosition.y), 2.0)) - 0.5), abs(fract(8.0 * vVertexPosition.y) - 0.5)))*vFragColor;
};
