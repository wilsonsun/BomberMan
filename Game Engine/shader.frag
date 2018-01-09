#version 430

in vec4 ex_Color;;
in vec2 ex_TexCoord;
layout(location=4) uniform sampler2D uTexture;
layout(location=10) uniform int uMode;

out vec4 out_Color;

void main(void) {
	if (uMode == 0)
		out_Color = ex_Color;
	else
		out_Color = texture2D(uTexture, ex_TexCoord);

}

