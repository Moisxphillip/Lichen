#version 440 core

layout(location = 0) out vec4 Color;

in vec2 V_TexCoord;

uniform vec4 U_Color;
uniform vec4 U_Light;
uniform sampler2D U_Texture;
// uniform float U_Time;
// uniform int U_PixelSize;

void main()
{
    vec3 light = vec3(0.9137, 0.7451, 0.4275);
    vec4 TexColor = texture(U_Texture, V_TexCoord);
    Color = TexColor*U_Color*vec4(light, 1.0);
}

//pixelate
// void main()
// {
//     float Pixels = 512.0;
//     float dx = 10.0 * (1.0 / Pixels);
//     float dy = 10.0 * (1.0 / Pixels);
//     vec2 Coord = vec2(dx * floor(V_TexCoord.x / dx), dy * floor(V_TexCoord.y / dy));
//     Color = texture(U_Texture, Coord)*U_Color;
// }

//distortion:
// void main()
// {
//     float distortion = sin(V_TexCoord.y * 4.0 + U_Time * 5.0);

//     vec2 DistortCoord = V_TexCoord + vec2(0.0, distortion*0.1);
//     vec4 TexColor = texture(U_Texture, DistortCoord);
//     Color = TexColor*U_Color;//U_Color
// }