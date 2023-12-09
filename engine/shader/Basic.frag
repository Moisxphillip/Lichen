#version 440 core

layout(location = 0) out vec4 Color;

in vec2 V_TexCoord;

uniform vec4 U_Color;
uniform vec4 U_AddColor;
uniform sampler2D U_Texture;

void main()
{
    vec4 TexColor = texture(U_Texture, V_TexCoord);
    vec4 ResultColor = clamp(TexColor + vec4(U_AddColor.rgb, 0), 0.0, 1.0) * U_Color  ;
    Color = clamp(ResultColor, 0.0, 1.0);
}