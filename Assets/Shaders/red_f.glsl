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
	vec4 texColor = texture(u_tex, uv).rgba;
	FragColor = texColor;
}