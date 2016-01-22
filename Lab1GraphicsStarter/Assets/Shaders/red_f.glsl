#version 400

uniform sampler2D u_tex;

// Fragment Shader Inputs
in VertexData
{
	vec3 normal;
	vec3 texCoord;
	vec4 colour;
} vIn;

layout(location = 0) out vec4 FragColor;

void main()
{
	vec2 uv = (vIn.texCoord).xy;
	FragColor = vec4(uv, 0.0, 1.0);
}