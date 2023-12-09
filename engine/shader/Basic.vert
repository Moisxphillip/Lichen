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

//Aligned version
// #version 330 core

// layout(location = 0) in vec4 Pos;
// layout(location = 1) in vec2 TexCoord;

// out vec2 V_TexCoord;

// uniform mat4 U_Mvp;

// void main()
// {
//     // Round the vertex position to achieve pixel alignment
//     vec2 pixelAlignedPos = round(Pos.xy);

//     // Use the rounded position for gl_Position
//     gl_Position = U_Mvp * vec4(pixelAlignedPos, Pos.z, Pos.w);

//     V_TexCoord = TexCoord;
// }