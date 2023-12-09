#version 440 core

layout(location = 0) in vec4 Pos;
layout(location = 1) in vec2 TexCoord;

out vec2 V_TexCoord;

uniform mat4 U_Mvp;

void main()
{
    gl_Position = U_Mvp * Pos;
    V_TexCoord = TexCoord;
}