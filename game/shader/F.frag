#version 330 core

layout(location = 0) out vec4 Color;

uniform vec4 U_Color;

void main()
{
    Color = U_Color;
}