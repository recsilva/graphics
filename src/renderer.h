#pragma once

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"

class Renderer {
public:
    Renderer(GLFWwindow *window, Camera *camera, int width, int height);
    virtual ~Renderer();
    virtual void RenderScene();
    virtual void UpdateScene();

    void UpdateShaderMatrices();

    void SwitchToPerspective();
    void SwitchToOrthographic();

    inline void SetScale(float s)       {scale = s;}
    inline void SetRotation(float r)    {rotation = r;}
    inline void SetPosition(Vector3 p)  {position = p;}
    inline void SetFov(float f)         {fov = f;SwitchToPerspective();}
protected:
    Mesh* mesh;

    float scale;
    float rotation;
    Vector3 position;

    Matrix4 modelMatrix;
    Matrix4 projMatrix;
    Matrix4 viewMatrix;
    Matrix4 textureMatrix;
private:
    Shader* currentShader;
    GLFWwindow* window;
    Camera* camera;

    float fov = 45.0f;

    int		width;			//Render area width (not quite the same as window width)
	int		height;			//Render area height (not quite the same as window height)
    bool	init;
};