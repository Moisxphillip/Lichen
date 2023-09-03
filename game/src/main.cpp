#define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main
// #include "SDL2/SDL.h"

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cmath>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Tools.hpp"
#include "../../engine/lib/Vector2.hpp"
#include "../../engine/lib/Rect.hpp"
#include "../../engine/lib/Renderer.hpp"
#include "../../engine/lib/Resources.hpp"
#include "../../engine/lib/Image.hpp"
#include "../../engine/lib/FontHandler.hpp"
#include "../../engine/lib/Window.hpp"
#include "../../engine/lib/Draw.hpp"
#include "../../engine/lib/Circle.hpp"



int main (int argc, char** argv) 
{    
    SDL_Init(SDL_INIT_EVERYTHING);
    if(TTF_Init()==-1) { std::cout << "TTF_Init: " <<  TTF_GetError() <<'\n';}

    Window Win("Lichen", 800,800);
    Renderer Rend;
    Rend.SetClearColor(Color("#2a2a2a"));
    Rend.SetBlendMode(BlendMode::Add);

    Vector2 Scale(1,1), Pos(400,400), Et(200,200);
    Rect Crop(0,0, 100,100);
    Rect Crop2(0,0, Pos.x,Pos.y);
    
    Image Penguin("./res/img/penguinface.png");
    Image Penguin2("./res/img/penguinface.png");
    // Image Penguin("./res/img/tests.png");

    std::string Texto = "ÖÖÖÖÖÖÖ\nQuero trancar o curso", Path = "./res/ttf/Caviar.ttf";
    FontHandler Fh(Path);
    TTF_Font* Ptr = Resources::GetFont(Path);
    Fh.UpdateHandler(Ptr, Texto, 40, 300,TextStyle::BLENDED, TextAlignment::CENTER);

    Penguin2.SetColor(Color("#00f0fa"));
    
    Circle ci(Pos.x*1.3f, Pos.y*1.3f, 60);
    Rect re(Pos.x-60, Pos.y-60, 120,120);
    Draw Form;
    float ang = 0;

    while(!Win.QuitRequested())
    {
        ang+=0.04;
        Rend.Clear();
        double x, y;
        glfwGetCursorPos(Win.GetGLWindow(), &x, &y);
        Vector2 Posi(-x, -y);
        Rend.SetViewPosition(Posi);

        Color B((sin(ang)+1)/2, (sin(ang+M_PI*0.66667f)+1)/2, (sin(ang+M_PI*1.21212f)+1)/2);

        Penguin.SetColor(B);

        Penguin.Render(Rend, Win.GetProjection(), Pos, Scale, Crop, 0, Flip::N);
        Penguin2.Render(Rend, Win.GetProjection(), Pos*1.3f, Scale, Crop, 0, Flip::N);

        Fh.Render(Rend, Win.GetProjection(), Et*1.2f, 0, Flip::N, B);

        Form.DrawRectangle(re, Color("#FF00FF"),  Win.GetProjection(), Rend.GetView());
        Form.DrawCircle(ci, Color("#00FFFF"), 30, Win.GetProjection(), Rend.GetView());

        Rend.Show(Win.GetGLWindow());
    }

    TTF_Quit();
    SDL_Quit();
    return 0;
}

