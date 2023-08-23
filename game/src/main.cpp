#define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Tools.hpp"
#include "../../engine/lib/Vector2.hpp"
#include "../../engine/lib/Rect.hpp"

#include "../lib/Renderer.hpp"
#include "../lib/Image.hpp"
#include "../lib/Window.hpp"



int main (int argc, char** argv) 
{    
    Window Win("Lichen", 800,800);
    Vector2 Scale(1,1), Pos(400,400), Et(600,600);
    Rect Crop(0,0, 50,50);
    Rect Crop2(0,0, Pos.x,Pos.y);

    Renderer Rend;        
    Rend.SetClearColor(Color("#b0071e"));
    Rend.SetBlendMode(BlendMode::Add);
    Image Penguin("./res/img/penguinface.png");
    Image Alien("./res/img/minion.png");

    float ang = 0;

    while(!Rend.ExitRequested())
    {
        ang+=0.03;
        Rend.Clear();
        double x, y;
        glfwGetCursorPos(Win.GetWindow(), &x, &y);
        Vector2 Posi(-x, -y);
        Rend.SetViewPosition(Posi);
        Penguin.Render(Rend, Win.GetProjection(), Rend.GetView(), Pos, Scale,Crop, 0);
        Alien.Render(Rend, Win.GetProjection(), Rend.GetView(), Et, Scale,Crop, 0);
        Rend.Show(Win.GetWindow());

    }
    return 0;
}





    ///////////////////////////////////////////////////////
      
      
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glm::mat4 Projection = 
        //     glm::ortho( //x = ➡, y = ⬇
        //     (float)0.0, (float)Win->GetWidth(), 
        //     (float)Win->GetHeight(), (float)0.0,
        //     (float)1.0, (float)10.0)
        // ;//Defines new window boundaries
        //Attention: Internal resolution can be defined from the width and height.
        //However, a formula must be created for keeping the wished aspect ratio,
        //avoiding stretches and such.

        // glm::mat4 View = glm::translate(glm::mat4(1.0), glm::vec3(0.0,0.0,0.0));//Camera
    //Scope inserted to call ib and vb destructors before terminating, find a way to do it in a better way
    //End routines
        // ;//Defines new window boundaries
        // glm::mat4 Projection = 
        //     glm::perspective( //x = ➡, y = ⬇
        //     (float)glm::radians(45.0), (float)Win->GetWidth()/(float)Win->GetHeight(),
        //     (float)0.0, (float)100.0)
        
        
        // Texture Penguin("./res/img/penguinface.png");
        // Penguin.Bind();
        // Basic.SetUniform1i("U_Texture", 0);

        // glm::mat4 Model = glm::translate(glm::mat4(1.0), glm::vec3(400.0,200.0, 0));

        // Model =  glm::rotate(Model, glm::radians(45.0f), glm::vec3(0,1, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)

        // glm::mat4 MVP = Projection*View*Model;  
        
            // Basic.SetUniform4f("U_Color", (float)(cos(x)+1)/2, (float)(cos(x+M_PI*0.66667)+1)/2, (float)(cos(x+M_PI*1.21212)+1)/2, 1.0);
            // Basic.SetUniformMat4f("U_Mvp",MVP);
            // Rend.Draw(Va, Ib, Basic);
        
        
        // float Pos[] = 
        // { //vertex pos                                              | destiny rect
        //     -1 * (Size.x/2) * Scale.x,-1 * (Size.y/2) *Scale.y,      Crop.x/Size.x,             (Crop.y+Crop.h)/Size.y,
        //      1 * (Size.x/2) * Scale.x,-1 * (Size.y/2) *Scale.y,      (Crop.x+Crop.w)/Size.x,    (Crop.y+Crop.h)/Size.y,
        //      1 * (Size.x/2) * Scale.x, 1 * (Size.y/2) *Scale.y,      (Crop.x+Crop.w)/Size.x,    Crop.y/Size.y,
        //     -1 * (Size.x/2) * Scale.x, 1 * (Size.y/2) *Scale.y,      Crop.x/Size.x,             Crop.y/Size.y,
        // };
        
        // unsigned int Index[] ={0,1,2,2,3,0};

        // VertexArray Va;
        // VertexBuffer Vb(Pos, 4*4*sizeof(float));
        // VertexBufferLayout Vbl;
        // Vbl.Push(GL_FLOAT, 2); //Position data
        // Vbl.Push(GL_FLOAT, 2); //texture mapping data
        // Va.AddBuffer(Vb, Vbl);
        // IndexBuffer Ib(Index, 6);
        
        // Shader Basic;
        // Basic.CreateShader("./game/shader/V.vert","./game/shader/F.frag");
        // Basic.Bind();
        

        // Va.Unbind();
        // Vb.Unbind();
        // Ib.Unbind();
        // Basic.Unbind();
            
            
            // while(!GLCheckError()){}
            
            // Basic.Bind(); 
            // Va.Bind();
            // Ib.Bind();


            // Basic2.Bind(); 
            // Basic2.SetUniform4f("U_Color", 0, 1.0, 0, 1.0);
            // Va2.Bind();
            // Ib2.Bind();
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);// to use with index buffers
        
        // float Pos2[] = 
        // {
        //     -.8, -.5,
        //     .5, -.8,
        //     .8, .5,        
        //     -.5, .8,
        // };
        // unsigned int Index2[] =
        // {
        //     0,1,2,
        //     2,3,0
        // };
        // VertexArray Va2;
        // VertexBuffer Vb2(Pos2, 4*2*sizeof(float));
        // VertexBufferLayout Vbl2;
        // Vbl2.Push(GL_FLOAT, 2);
        // Va2.AddBuffer(Vb2, Vbl2);
        // IndexBuffer Ib2(Index2, 6);
        // Shader Basic2;
        // Basic2.CreateShader("./game/shader/V.vert","./game/shader/F.frag");
        // Basic2.Bind();
        // int Location2 = Basic2.GetUniformLocation("U_Color"); 


        //This Block unbinds everything
        // glBindVertexArray(0);
        // glUseProgram(0);
        // glBindBuffer(GL_ARRAY_BUFFER, 0);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Engine implementation testing
    // Engine::Instance().Run();  



    //Fragment shader: processed pixel by pixel
    //
    //Penguin game init
    // TitleState* Begin = new TitleState();
    // Engine::Instance().Push(Begin);
    // Engine::Instance().Run(); //Create a Engine instance by calling Get.. then run it


        // glDrawArrays(GL_TRIANGLES, 0, 6);

    // std::cout << glGetString(GL_VERSION) << '\n'; //to get version
        // glBegin(GL_TRIANGLES); //LEGACY
        // glVertex2f(-.5, -.5);
        // glVertex2f(0, .5);
        // glVertex2f(.5, -.5);

    // unsigned int Shader = CreateShader("./game/shader/V.vert","./game/shader/F.frag");
    // glUseProgram(Shader);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // while(!glfwWindowShouldClose(Window))
    // {
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     glDrawArrays(GL_TRIANGLES, 0, 3);
    //     // glDrawElements(GL_TRIANGLES, 0, 3);// to use with index buffers

    //     glfwSwapBuffers(Window);
    //     glfwPollEvents();
    // }
    // glDeleteProgram(Shader);
        // glEnd();
// static unsigned int CompileShader(unsigned int Type, const std::string& Source)
// {
//     unsigned int Id = glCreateShader(Type);

//     std::ifstream TargetFile(Source);
//     if(TargetFile.fail())
//     {
//         Error("Shader::_Compile: Could not open " + Source);
//     }
//     std::string FileContent, Line;
//     while(std::getline(TargetFile, Line))
//     {
//         FileContent += Line +"\n";
//     }
//     TargetFile.close();
//     const char* Src = FileContent.c_str();

//     glShaderSource(Id, 1, &Src, nullptr);
//     glCompileShader(Id);

//     int IsCompiled = 0;
//     glGetShaderiv(Id, GL_COMPILE_STATUS, &IsCompiled);
//     if(IsCompiled == GL_FALSE)
//     {
//         int MaxLength = 0;
//         glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &IsCompiled);
//         std::vector<char> ErrorLog(MaxLength);
//         glGetShaderInfoLog(Id, MaxLength, &MaxLength, &ErrorLog[0]);
//         std::string GLErrorMessage(ErrorLog.begin(), ErrorLog.end());
//         Error("Shader::_Compile: Shader compilation failed: " + GLErrorMessage);
//         glDeleteShader(Id);
//         return 0;
//     }


//     return Id;
// }

// static unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
// {
//     unsigned int Program = glCreateProgram();
//     unsigned int VShader = CompileShader(GL_VERTEX_SHADER, VertexShader);
//     unsigned int FShader = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

//     glAttachShader(Program, VShader);
//     glAttachShader(Program, FShader);
//     glLinkProgram(Program);
//     glValidateProgram(Program); 

//     glDeleteShader(VShader);
//     glDeleteShader(FShader);
    
//     return Program;
// }