#ifndef LICHEN_SHADER
#define LICHEN_SHADER

#include <string>
#include <unordered_map>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

#include "Color.hpp"

class Shader
{
    private:
        unsigned int _ProgramID;
        unsigned int _VertexID;
        unsigned int _FragmentID;
        unsigned int _CompileShader(unsigned int, const std::string&);
        std::unordered_map<std::string, int> _UniformCache;
        
    public:
        Shader();
        ~Shader();
        
        void CreateShader(const std::string& = (std::string)"./engine/shader/Basic.vert", const std::string& = (std::string)"./engine/shader/Basic.frag");
        void SubstituteShader(const std::string& = (std::string)"./engine/shader/Basic.vert", const std::string& = (std::string)"./engine/shader/Basic.frag");
        unsigned int GetProgramID();
        unsigned int GetVertexID();
        unsigned int GetFragmentID();
        
        void Bind();
        void Unbind();
        int GetUniformLocation(const std::string&);

        //Uniform modification
        void SetUniform1f(const std::string&, float);
        void SetUniform2f(const std::string&, float, float);
        void SetUniform3f(const std::string&, float, float, float);
        void SetUniform4f(const std::string&, float, float, float, float);
        void SetUniformMat4f(const std::string&, const glm::mat4&);
        void SetUniform1i(const std::string&, int);
        void SetUniform1ui(const std::string&, unsigned int);
        void SetColor(const std::string&, Color& Colour);
};

#endif// LICHEN_SHADER