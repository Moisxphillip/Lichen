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
#include "../lib/Renderer.hpp"
#include "../lib/Texture.hpp"
#include "../lib/Shader.hpp"
#include "../lib/IndexBuffer.hpp"
#include "../lib/VertexBuffer.hpp"
#include "../lib/VertexArray.hpp"



int main (int argc, char** argv) 
{

    //DIRECT OPENGL TESTING///////////////////////////
    GLFWwindow* Window;
    if(!glfwInit())
    {
        std::cout << "Error on glfw init.\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //hints for the window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //must have a vertex array if using this
    int WindowWidth = 800, WindowHeight = 800;
    Window = glfwCreateWindow(WindowWidth, WindowHeight, "Lichen",0,0);
    if(!Window)
    {
        std::cout << "Error on window creation.\n";
        return -1;
    }
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1); //VSync
    if(glewInit()!=GLEW_OK)//glew comes after making the context
    {
        std::cout << "Error on glew init.\n";
        return -1;
    }

    //Render part from here
    {
        float Pos[] = 
        {
            200,200,  0,0,
            600,200,   1,0,
            600,600,    1,1,
            200,600,   0,1
        };

        unsigned int Index[] ={0,1,2,2,3,0};

        VertexArray Va;
        VertexBuffer Vb(Pos, 4*4*sizeof(float));
        VertexBufferLayout Vbl;
        Vbl.Push(GL_FLOAT, 2);
        Vbl.Push(GL_FLOAT, 2);
        Va.AddBuffer(Vb, Vbl);
        IndexBuffer Ib(Index, 6);
        
        Shader Basic;
        Basic.CreateShader("./game/shader/V.vert","./game/shader/F.frag");
        Basic.Bind();
        

        Va.Unbind();
        Vb.Unbind();
        Ib.Unbind();
        Basic.Unbind();

        Renderer Rend;
        float x = 0;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        Texture Penguin("./res/img/penguinface.png");
        Penguin.Bind();
        Basic.SetUniform1i("U_Texture", 0);

        glm::mat4 Projection = glm::ortho(
            (float)0.0, (float)WindowWidth, 
            (float)0.0, (float)WindowHeight,
            (float)-1.0, (float)1.0);//Defines new window boundaries

        // glm::vec4 VertexPos(100.0, 100.0, 0.0, 1.0);
        // glm::vec4 Result = Projection * VertexPos;

        while(!glfwWindowShouldClose(Window))
        {
            x+=0.03;
            Rend.Clear();
            Basic.SetUniform4f("U_Color", (float)(cos(x)+1)/2, (float)(cos(x+M_PI*0.66667)+1)/2, (float)(cos(x+M_PI*1.21212)+1)/2, 1.0);
            Basic.SetUniformMat4f("U_Mvp",Projection);

            Rend.Draw(Va, Ib, Basic);

            glfwSwapBuffers(Window);
            glfwPollEvents();
        }
    }//Scope inserted to call ib and vb destructors before terminating, find a way to do it in a better way
        
    //End routines
    glfwDestroyWindow(Window);
    glfwTerminate();
     

    return 0;
}





    ///////////////////////////////////////////////////////
            
            
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