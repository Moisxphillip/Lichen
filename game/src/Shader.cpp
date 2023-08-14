#include "../lib/Shader.hpp"
#include <iomanip>
#include <fstream>
#include <vector>
#include "../../engine/lib/Tools.hpp"

Shader::Shader()
: _ProgramID(0), _VertexID(0), _FragmentID(0)
{   
    _Attributes = 0;
}

Shader::~Shader()
{
    if(_ProgramID != 0)
    {
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

// void Shader::UseProgram()
// {
//     glUseProgram(_ProgramID);
// }

// void Shader::DeleteProgram()
// {
//     if(_ProgramID != 0)
//     {
//         glDeleteProgram(_ProgramID);
//         _ProgramID = 0;
//     }
// }

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


// void Shader::CompileShaders(const std::string& VertShader, const std::string& FragShader)
// {
//     _ProgShaderID = glCreateProgram();

//     _VertShaderID = glCreateShader(GL_VERTEX_SHADER);
//     if(_VertShaderID == 0)
//     {
//         Error("Shader::CompileShaders: _VertShaderID could not be created");
//     }

//     _FragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//     if(_FragShaderID == 0)
//     {
//         Error("Shader::CompileShaders: _FragShaderID could not be created");
//     }
//     _Compile(VertShader, _VertShaderID);
//     _Compile(FragShader, _FragShaderID);
// }

// void Shader::_Compile(const std::string& TargetPath, GLuint TargetID)
// {
//     std::ifstream TargetFile(TargetPath);
//     if(TargetFile.fail())
//     {
//         Error("Shader::_Compile: Could not open " + TargetPath);
//     }
//     std::string FileContent, Line;
//     while(std::getline(TargetFile, Line))
//     {
//         FileContent += Line +"\n";
//     }
//     TargetFile.close();
//     const char* TargetFileCStr = FileContent.c_str();
//     glShaderSource(TargetID, 1, &TargetFileCStr, nullptr);
//     glCompileShader(TargetID);

//     GLint IsCompiled = 0;
//     glGetShaderiv(TargetID, GL_COMPILE_STATUS, &IsCompiled);
//     if(IsCompiled == GL_FALSE)
//     {
//         GLint MaxLength = 0;
//         glGetShaderiv(TargetID, GL_INFO_LOG_LENGTH, &IsCompiled);
//         std::vector<GLchar> ErrorLog(MaxLength);
//         glGetShaderInfoLog(TargetID, MaxLength, &MaxLength, &ErrorLog[0]);
//         Error("Shader::_Compile: Shader compilation failed");
//         std::printf("%s\n", (char*)&ErrorLog);
//     }
// }

// void Shader::LinkShaders()
// {
//     // Attach our shaders to our program
//     glAttachShader(_ProgShaderID, _VertShaderID);
//     glAttachShader(_ProgShaderID, _FragShaderID);

//     // Link our program
//     glLinkProgram(_ProgShaderID);

//     // Note the different functions here: glGetProgram* instead of glGetShader*.
//     GLint IsLinked = 0;
//     glGetProgramiv(_ProgShaderID, GL_LINK_STATUS, &IsLinked);
//     if (IsLinked == GL_FALSE)
//     {
//         GLint MaxLength = 0;
//         glGetProgramiv(_ProgShaderID, GL_INFO_LOG_LENGTH, &MaxLength);
//         std::vector<GLchar> ErrorLog(MaxLength);
//         glGetProgramInfoLog(_ProgShaderID, MaxLength, &MaxLength, &ErrorLog[0]);

//         glDeleteProgram(_ProgShaderID);
//         glDeleteShader(_VertShaderID);
//         glDeleteShader(_FragShaderID);

//         Error("Shader::_Compile: Shader linking failed");
//         std::printf("%s\n", (char*)&ErrorLog);
//         return;
//     }
//     // Always detach shaders after a successful link.
//     glDetachShader(_ProgShaderID, _VertShaderID);
//     glDetachShader(_ProgShaderID, _FragShaderID);
//     glDeleteShader(_VertShaderID);
//     glDeleteShader(_FragShaderID);
// }

void Shader::AddAttribute(const std::string& AttribName)
{
    glBindAttribLocation(_ProgramID, _Attributes, AttribName.c_str());
    _Attributes++;
}

void Shader::Bind()
{
    glUseProgram(_ProgramID);
    // for(int i = 0; i<_Attributes; i++)
    // {
    //     glEnableVertexAttribArray(i);
    // }
}

void Shader::Unbind()
{
    glUseProgram(0);
    // for(int i = 0; i<_Attributes; i++)
    // {
    //     glDisableVertexAttribArray(i);
    // }
}

int Shader::GetUniformLocation(const std::string& Name)
{
    int UniformLocation;
    if(!_UniformCache.count(Name))
    {
        UniformLocation = glGetUniformLocation(_ProgramID, Name.c_str());
        _UniformCache[Name] = UniformLocation;
    }
    else
    {
        UniformLocation = _UniformCache[Name];
    }

    if(UniformLocation == GL_INVALID_INDEX)
    {
        Error("Shader::GetUniformLocation: Invalid uniform specification for "+ Name);
    }
    return UniformLocation;
}

void Shader::SetUniform1f(const std::string& Name, float v0)
{
    int Location = GetUniformLocation(Name);
    if(Location == -1)
    {
        Error("Shader::SetUniform1f: Attempted to set an invalid uniform");
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
        Error("Shader::SetUniform2f: Attempted to set an invalid uniform");
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
        Error("Shader::SetUniform3f: Attempted to set an invalid uniform");
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
        Error("Shader::SetUniform4f: Attempted to set an invalid uniform");
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
        Error("Shader::SetUniformMat4f: Attempted to set an invalid uniform");
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
        Error("Shader::SetUniform1i: Attempted to set an invalid uniform");
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
        Error("Shader::SetUniform1ui: Attempted to set an invalid uniform");
        return;
    }
    Bind();
    glUniform1ui(Location, v0);
}

