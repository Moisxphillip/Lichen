#ifndef LICHEN_SHADER
#define LICHEN_SHADER

#include <string>
#include <unordered_map>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

#include "Tools/Color.hpp"

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
        int GetUniformLocation(const std::string& Name);

        //Uniform modification
        void SetUniform1f(const std::string& Name, float V0);
        void SetUniform2f(const std::string& Name, float V0, float V1);
        void SetUniform3f(const std::string& Name, float V0, float V1, float V2);
        void SetUniform4f(const std::string& Name, float V0, float V1, float V2, float V3);
        void SetUniformMat4f(const std::string& Name, const glm::mat4& Matrix);
        void SetUniform1i(const std::string& Name, int V0);
        void SetUniform1ui(const std::string& Name, unsigned int V0);
        void SetColor(const std::string& Name, Color& Colour);
};

#endif// LICHEN_SHADER