#pragma once

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "mesh.h"
#include "shader.h"

class Renderer {
public:
    Renderer(GLFWwindow *window);
    virtual ~Renderer();
    virtual void RenderScene();
protected:
    Mesh* triangle;
private:
    Shader* currentShader;
    bool	init;
    GLFWwindow* window;
};