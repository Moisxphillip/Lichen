#version 330 core

layout(location = 0) out vec4 Color;

in vec2 V_TexCoord;

uniform vec4 U_Color;
uniform sampler2D U_Texture;

void main()
{
    vec4 TexColor = texture(U_Texture, V_TexCoord);
    Color = TexColor*U_Color;//U_Color
}