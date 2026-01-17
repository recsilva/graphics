#pragma once

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "mesh.h"
#include <fstream>

#define SHADER_VERTEX 0
#define SHADER_FRAGMENT 1
#define SHADER_GEOMETRY 2

using namespace std;

class Shader {
    public:
    Shader(string vertex, string fragment, string geometry = "");
    ~Shader();

    GLuint GetProgram(){return program;}
    bool LinkProgram();

    protected:
    void SetDefaultAttributes();
    bool LoadShaderFile(string from, string &into);
    GLuint GenerateShader(string from , GLuint type);

    GLuint objects[3];
    GLuint program;

    bool loadFailed;
};