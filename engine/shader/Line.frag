#version 440 core

out vec4 FragColor;
uniform vec4 U_Color;

void main()
{
    FragColor = vec4(U_Color);
}