#include "renderer.h"

Renderer::Renderer(GLFWwindow* window, int width, int height) 
    : window(window), width(width), height(height)
{
    mesh = Mesh::generate_quad();

    currentShader = new Shader( "shaders/matrixVertex.glsl",
                                "shaders/colorFragment.glsl");

    if (!currentShader->LinkProgram()){
        return;
    }
    init = true;

    SwitchToOrthographic();
}
Renderer::~Renderer(){
    delete mesh;
}

void Renderer::RenderScene(){
    // glViewport(0,0,500,500);
    glClearColor (0.2f ,0.2f ,0.2f ,1.0f );
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(currentShader->GetProgram());

    glUniformMatrix4fv(
        glGetUniformLocation(currentShader->GetProgram(), "projMatrix"),
        1, false, (float*)&projMatrix);
    glUniformMatrix4fv(
        glGetUniformLocation(currentShader->GetProgram(), "viewMatrix"),
        1, false, (float*)&viewMatrix);
    
    for(int i = 0; i < 3; i++){
        Vector3 tempPos = position;
        tempPos += Vector3(-100.f*i, -100.f*i, 500.f*i);

        // cout << rotation << " : " << scale << " : " << tempPos;

        modelMatrix =   Matrix4::Translation(tempPos) *
                        Matrix4::Rotation(rotation, Vector3(0,1,0)) *
                        Matrix4::Scale(Vector3(scale,scale,scale));

        glUniformMatrix4fv(glGetUniformLocation(
            currentShader->GetProgram(), "modelMatrix"),
            1, false, (float*)&modelMatrix);
        mesh->draw();
    }

    glUseProgram(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::SwitchToPerspective(){
    projMatrix = Matrix4::Perspective(1.0f, 10000.0f, 
                (float)width / (float)height, fov);
}

void Renderer::SwitchToOrthographic(){
    projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, 
        width/2.0f,-width/2.0f,height/2.0f,-height/2.0f);
}