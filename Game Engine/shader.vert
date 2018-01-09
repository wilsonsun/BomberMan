#version 430

layout(location=0) in vec3 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) uniform mat4 uTransform;
layout(location=3) in vec2 in_TexCoords;
layout(location=5) uniform mat4 persp_matrix;
layout(location=6) uniform mat4 view_matrix;

out vec4 ex_Color;
out vec2 ex_TexCoord;

void main() {
	gl_Position = persp_matrix*view_matrix*uTransform*vec4(in_Position, 1.0);
	ex_Color = in_Color;
	ex_TexCoord = in_TexCoords;
}