#include <iomanip>
#include <fstream>
#include <vector>
#include "Graphics/Shader.hpp"
#include "Tools/Tools.hpp"


Shader::Shader()
: _ProgramID(0), _VertexID(0), _FragmentID(0)
{   
}

Shader::~Shader()
{
    if(_ProgramID != 0)
    {
        Unbind();
        glDeleteProgram(_ProgramID);
        _ProgramID = 0;
    }
}

unsigned int Shader::_CompileShader(unsigned int Type, const std::string& Source)
{
    unsigned int Id = glCreateShader(Type);

    std::ifstream TargetFile(Source);
    if(TargetFile.fail())
    {
        Error("Shader::_Compile: Could not open " + Source);
    }
    std::string FileContent, Line;
    while(std::getline(TargetFile, Line))
    {
        FileContent += Line +"\n";
    }
    TargetFile.close();
    const char* Src = FileContent.c_str();

    glShaderSource(Id, 1, &Src, nullptr);
    glCompileShader(Id);

    int IsCompiled = 0;
    glGetShaderiv(Id, GL_COMPILE_STATUS, &IsCompiled);
    if(IsCompiled == GL_FALSE)
    {
        int MaxLength = 0;
        glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &IsCompiled);
        std::vector<char> ErrorLog(MaxLength);
        glGetShaderInfoLog(Id, MaxLength, &MaxLength, &ErrorLog[0]);
        std::string GLErrorMessage(ErrorLog.begin(), ErrorLog.end());
        Error("Shader::_Compile: Shader compilation failed: " + GLErrorMessage);
        glDeleteShader(Id);
        return 0;
    }
    return Id;
}

void Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    if(_ProgramID != 0)
    {
        Error("Shader::CreateShader: Attempted to create a new Shader over an existing one");
        return;
    }

    _ProgramID = glCreateProgram();

    _VertexID = _CompileShader(GL_VERTEX_SHADER, VertexShader);
    if(_VertexID == 0)
    {
        Error("Shader::CreateShader: _VertexID could not be created");
    }

    _FragmentID = _CompileShader(GL_FRAGMENT_SHADER, FragmentShader);
    if(_FragmentID == 0)
    {
        Error("Shader::CreateShader: _FragmentID could not be created");
    }

    glAttachShader(_ProgramID, _VertexID);
    glAttachShader(_ProgramID, _FragmentID);
    glLinkProgram(_ProgramID);
    glValidateProgram(_ProgramID);
    glDeleteShader(_VertexID);
    glDeleteShader(_FragmentID);
}

void Shader::SubstituteShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    if(_ProgramID != 0)
    {
        Unbind();
        glDeleteProgram(_ProgramID);
        _ProgramID = 0;
    }
    CreateShader(VertexShader, FragmentShader);
}

unsigned int Shader::GetProgramID()
{
    return _ProgramID;
}

unsigned int Shader::GetVertexID()
{
    return _VertexID;
}

unsigned int Shader::GetFragmentID()
{
    return _FragmentID;
}

void Shader::Bind()
{
    glUseProgram(_ProgramID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& Name)
{
    if(!_UniformCache.count(Name))
    {
        _UniformCache[Name] = glGetUniformLocation(_ProgramID, Name.c_str());
    }
    return _UniformCache[Name];
}

void Shader::SetUniform1f(const std::string& Name, float v0)
{
    int Location = GetUniformLocation(Name);
    if(Location == -1)
    {
        Error("Shader::SetUniform1f: Attempted to set an invalid uniform "+ Name);
        return;
    }
    Bind();
    glUniform1f(Location, v0);
}

void Shader::SetUniform2f(const std::string& Name, float v0, float v1)
{
    int Location = GetUniformLocation(Name);
    if(Location == -1)
    {
        Error("Shader::SetUniform2f: Attempted to set an invalid uniform "+ Name);
        return;
    }
    Bind();
    glUniform2f(Location, v0,v1);
}

void Shader::SetUniform3f(const std::string& Name, float v0, float v1, float v2)
{
    int Location = GetUniformLocation(Name);
    if(Location == -1)
    {
        Error("Shader::SetUniform3f: Attempted to set an invalid uniform "+ Name);
        return;
    }
    Bind();
    glUniform3f(Location, v0,v1,v2);
}

void Shader::SetUniform4f(const std::string& Name, float v0, float v1, float v2, float v3)
{
    int Location = GetUniformLocation(Name);
    if(Location == -1)
    {
        Error("Shader::SetUniform4f: Attempted to set an invalid uniform "+ Name);
        return;
    }
    Bind();
    glUniform4f(Location, v0,v1,v2,v3);
}

void Shader::SetUniformMat4f(const std::string& Name, const glm::mat4& Matrix)
{
    int Location = GetUniformLocation(Name);
    if(Location == -1)
    {
        Error("Shader::SetUniformMat4f: Attempted to set an invalid uniform "+ Name);
        return;
    }
    Bind();
    glUniformMatrix4fv(Location, 1, GL_FALSE, &Matrix[0][0]);
}

void Shader::SetUniform1i(const std::string& Name, int v0)
{
    int Location = GetUniformLocation(Name);
    if(Location == -1)
    {
        Error("Shader::SetUniform1i: Attempted to set an invalid uniform "+ Name);
        return;
    }
    Bind();
    glUniform1i(Location, v0);
}

void Shader::SetUniform1ui(const std::string& Name, unsigned int v0)
{
    int Location = GetUniformLocation(Name);
    if(Location == -1)
    {
        Error("Shader::SetUniform1ui: Attempted to set an invalid uniform "+ Name);
        return;
    }
    Bind();
    glUniform1ui(Location, v0);
}

void Shader::SetColor(const std::string& Name,Color& Colour)
{
    SetUniform4f(Name, Colour.r, Colour.g, Colour.b, Colour.a);
}

