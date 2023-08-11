#include "../lib/GLSL.hpp"
#include <iomanip>
#include <fstream>
#include <vector>
#include "../../engine/lib/Tools.hpp"

GLSL::GLSL()
: _ProgramID(0), _VertexID(0), _FragmentID(0)
{   
    _Attributes = 0;
}

GLSL::~GLSL()
{
    if(_ProgramID != 0)
    {
        glDeleteProgram(_ProgramID);
        _ProgramID = 0;
    }
}

unsigned int GLSL::_CompileShader(unsigned int Type, const std::string& Source)
{
    unsigned int Id = glCreateShader(Type);

    std::ifstream TargetFile(Source);
    if(TargetFile.fail())
    {
        Error("GLSL::_Compile: Could not open " + Source);
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
        Error("GLSL::_Compile: Shader compilation failed: " + GLErrorMessage);
        glDeleteShader(Id);
        return 0;
    }
    return Id;
}

void GLSL::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    _ProgramID = glCreateProgram();
    
    _VertexID = _CompileShader(GL_VERTEX_SHADER, VertexShader);
    if(_VertexID == 0)
    {
        Error("GLSL::CreateShader: _VertexID could not be created");
    }

    _FragmentID = _CompileShader(GL_FRAGMENT_SHADER, FragmentShader);
    if(_FragmentID == 0)
    {
        Error("GLSL::CreateShader: _FragmentID could not be created");
    }

    glAttachShader(_ProgramID, _VertexID);
    glAttachShader(_ProgramID, _FragmentID);
    glLinkProgram(_ProgramID);
    glValidateProgram(_ProgramID);
    glDeleteShader(_VertexID);
    glDeleteShader(_FragmentID);
}

void GLSL::UseProgram()
{
    glUseProgram(_ProgramID);
}

void GLSL::DeleteProgram()
{
    if(_ProgramID != 0)
    {
        glDeleteProgram(_ProgramID);
        _ProgramID = 0;
    }
}

unsigned int GLSL::GetProgramID()
{
    return _ProgramID;
}

unsigned int GLSL::GetVertexID()
{
    return _VertexID;
}

unsigned int GLSL::GetFragmentID()
{
    return _FragmentID;
}


// void GLSL::CompileShaders(const std::string& VertShader, const std::string& FragShader)
// {
//     _ProgShaderID = glCreateProgram();

//     _VertShaderID = glCreateShader(GL_VERTEX_SHADER);
//     if(_VertShaderID == 0)
//     {
//         Error("GLSL::CompileShaders: _VertShaderID could not be created");
//     }

//     _FragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//     if(_FragShaderID == 0)
//     {
//         Error("GLSL::CompileShaders: _FragShaderID could not be created");
//     }
//     _Compile(VertShader, _VertShaderID);
//     _Compile(FragShader, _FragShaderID);
// }

// void GLSL::_Compile(const std::string& TargetPath, GLuint TargetID)
// {
//     std::ifstream TargetFile(TargetPath);
//     if(TargetFile.fail())
//     {
//         Error("GLSL::_Compile: Could not open " + TargetPath);
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
//         Error("GLSL::_Compile: Shader compilation failed");
//         std::printf("%s\n", (char*)&ErrorLog);
//     }
// }

// void GLSL::LinkShaders()
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

//         Error("GLSL::_Compile: Shader linking failed");
//         std::printf("%s\n", (char*)&ErrorLog);
//         return;
//     }
//     // Always detach shaders after a successful link.
//     glDetachShader(_ProgShaderID, _VertShaderID);
//     glDetachShader(_ProgShaderID, _FragShaderID);
//     glDeleteShader(_VertShaderID);
//     glDeleteShader(_FragShaderID);
// }

void GLSL::AddAttribute(const std::string& AttribName)
{
    glBindAttribLocation(_ProgramID, _Attributes, AttribName.c_str());
    _Attributes++;
}

void GLSL::Bind()
{
    glUseProgram(_ProgramID);
    for(int i = 0; i<_Attributes; i++)
    {
        glEnableVertexAttribArray(i);
    }
}

void GLSL::Unbind()
{
    glUseProgram(0);
    for(int i = 0; i<_Attributes; i++)
    {
        glDisableVertexAttribArray(i);
    }
}

int GLSL::GetUniformLocation(const std::string& Name)
{
    int UniformLocation = glGetUniformLocation(_ProgramID, Name.c_str());
    if((GLuint)UniformLocation == GL_INVALID_INDEX)
    {
        Error("GLSL::GetUniformLocation: Uniform not found in shader");
    }
    return UniformLocation;
}