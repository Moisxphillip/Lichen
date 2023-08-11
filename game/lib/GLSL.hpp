#ifndef LICHEN_GLSLRUN
#define LICHEN_GLSLRUN

#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"


class GLSL
{
    private:
        int _Attributes;
        unsigned int _ProgramID;
        unsigned int _VertexID;
        unsigned int _FragmentID;
        unsigned int _CompileShader(unsigned int, const std::string&);
        // void _Compile(const std::string&, GLuint);
    public:
        GLSL();
        ~GLSL();

        void CreateShader(const std::string&, const std::string&);
        void UseProgram();
        void DeleteProgram();
        unsigned int GetProgramID();
        unsigned int GetVertexID();
        unsigned int GetFragmentID();
        
        // void CompileShaders(const std::string&, const std::string&);
        // void LinkShaders();
        void Bind();
        void Unbind();
        void AddAttribute(const std::string&);
        int GetUniformLocation(const std::string&);
};
#endif// LICHEN_GLSLRUN