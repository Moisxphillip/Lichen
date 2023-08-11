#define SDL_MAIN_HANDLED //Fix later, find out why it isn't recognizing the written main

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "../../engine/lib/Engine.hpp"
#include "../../engine/lib/Tools.hpp"
#include "../lib/GLSL.hpp"
#include "../lib/IndexBuffer.hpp"
#include "../lib/VertexBuffer.hpp"



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

    Window = glfwCreateWindow(800, 800, "Lichen",0,0);
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
    {
        float Pos[] = 
        {
            -.5, -.5,
            .5, -.5,
            .5, .5,        
            -.5, .5,
        };

        unsigned int Index[] =
        {
            0,1,2,
            2,3,0
        };


        //controversy: structure is recommended by opengl, but using a global VAO and binding 
        //new forms is faster in performance. If slow, benchmark and substitute for globals.
        unsigned int VertexArray;
        glGenVertexArrays(1, &VertexArray);
        glBindVertexArray(VertexArray);


        VertexBuffer Vb(Pos, 4*2*sizeof(float));

        // unsigned int Buffer;
        // glGenBuffers(1,&Buffer); //ID for the object in the buffer
        // glBindBuffer(GL_ARRAY_BUFFER, Buffer);//next step is to specify the data
        // glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), Pos, GL_STATIC_DRAW);//stream for few modifications and use, static for more use, dynamic for lots of both


        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float) , 0); //Links buffer above with vertex array


        IndexBuffer Ib(Index, 6);
        // unsigned int IndexBufferObj;
        // glGenBuffers(1,&IndexBufferObj); //ID for the object in the buffer
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferObj);//next step is to specify the data
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), Index, GL_STATIC_DRAW);

        GLSL Shader;
        Shader.CreateShader("./game/shader/V.vert","./game/shader/F.frag");
        Shader.UseProgram();

        int Location = Shader.GetUniformLocation("U_Color"); 
        float x = 0;


        //This Block unbinds everything
        glBindVertexArray(0);
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



        while(!glfwWindowShouldClose(Window))
        {
            x+=0.05;
            glClear(GL_COLOR_BUFFER_BIT);
                
            Shader.UseProgram(); //Bind shaders
            glUniform4f(Location, (float)cos(x), 1.0, 0.949, 1.0); // set up uniforms


            // glBindBuffer(GL_ARRAY_BUFFER, Buffer); //bind vertex buffer
            // glEnableVertexAttribArray(0); //must clear previous structure that may have changed
            // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float) , 0);//Set up vertex buffer layout

            glBindVertexArray(VertexArray);
            Ib.Bind();
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferObj);//Bind the index buffer

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);// to use with index buffers

            glfwSwapBuffers(Window);
            glfwPollEvents();
        }

        Shader.DeleteProgram();
    }//Scope inserted to call ib and vb destructors before terminating, find a way to do it in a better way
    glfwDestroyWindow(Window);
    glfwTerminate();
     

    return 0;
}





    ///////////////////////////////////////////////////////

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
//         Error("GLSL::_Compile: Could not open " + Source);
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
//         Error("GLSL::_Compile: Shader compilation failed: " + GLErrorMessage);
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