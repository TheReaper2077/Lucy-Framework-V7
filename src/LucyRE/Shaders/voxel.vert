#version 450 core

layout (location = 0) in uint v_data;

layout (std140, binding = 0) uniform ProjectionMatrix {
    mat4 model;
    mat4 view;
    mat4 projection;
	vec3 v_view_pos;
};

uniform vec3 offset;

out vec3 normal;
out vec3 uvw;
out vec2 uv;

out vec3 frag_pos;
out vec3 view_pos;

flat out int vertexid;
flat out int instanceid;

vec2 uv_array[6] = {
	{ 1, 1 },
	{ 1, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 1 },
	{ 1, 1 },
};

vec3 normal_array[6] = {
	{  0,  0, -1 },	// BACK
	{  0,  0,  1 },	// FRONT
	{  0, -1,  0 },	// BOTTOM
	{  0,  1,  0 },	// TOP
	{ -1,  0,  0 },	// LEFT
	{  1,  0,  0 },	// RIGHT
};

void main() {
	vec3 v_pos = vec3(
		(v_data & (0x7f << 11 + 7 * 0)) >> 11 + 7 * 0,	//	0xfe000000	25
		(v_data & (0x7f << 11 + 7 * 1)) >> 11 + 7 * 1,	//	0x01fc0000	18
		(v_data & (0x7f << 11 + 7 * 2)) >> 11 + 7 * 2	//	0x0003f800	11
	);

	normal = normal_array[(v_data & (0x3 << 8)) >> 8];
	uv = uv_array[gl_VertexID % 6];
	uvw = vec3(uv, v_data & 0xff);

	frag_pos = vec3(model * vec4(v_pos + offset, 1.0));
	gl_Position = projection * view * vec4(frag_pos, 1.0);

	vertexid = gl_VertexID;
	instanceid = gl_InstanceID;

	view_pos = v_view_pos;
}
