#version 400

// Vertex Shader Inputs
// These are the attributes of the vertex
layout(location = 0) in vec3 vIn_vertex;
layout(location = 1) in vec3 vIn_normal;
layout(location = 2) in vec3 vIn_uv;
layout(location = 3) in vec4 vIn_colour;

// Uniforms
// Constants throughout the entire pipeline
// These values are sent from C++ (glSendUniform*)
uniform mat4 u_mvp;

out VertexData
{
	vec3 normal;
	vec3 texCoord;
	vec4 colour;
} vOut;

void main()
{
	vOut.texCoord = vIn_uv;
	vOut.normal = vIn_normal;

	gl_Position = u_mvp * vec4(vIn_vertex, 1.0);
}