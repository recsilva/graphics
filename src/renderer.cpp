#include "renderer.h"

Renderer::Renderer(GLFWwindow* window, Camera* camera, int width, int height) 
    : window(window), camera(camera), width(width), height(height)
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
    delete camera;
    delete mesh;
}

void Renderer::RenderScene(){
    // glViewport(0,0,500,500);
    glClearColor (0.2f ,0.2f ,0.2f ,1.0f );
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(currentShader->GetProgram());

    UpdateShaderMatrices();
    
    for(int i = 0; i < 3; i++){
        Vector3 tempPos = position;
        tempPos += Vector3(-100.f*i, -100.f*i, 500.f*i);

        // cout << rotation << " : " << scale << " : " << tempPos;

        modelMatrix =   Matrix4::Translation(tempPos) *
                        Matrix4::Rotation(rotation, Vector3(0,1,0)) *
                        Matrix4::Scale(Vector3(100,100,100));

        glUniformMatrix4fv(glGetUniformLocation(
            currentShader->GetProgram(), "modelMatrix"),
            1, false, (float*)&modelMatrix);
        mesh->draw();
    }

    glUseProgram(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::UpdateScene(){
    // camera->UpdateCameraRotation();
    viewMatrix = camera->BuildViewMatrix();
}

void Renderer::UpdateShaderMatrices(){
    if (currentShader){
        glUniformMatrix4fv(
            glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"),
            1, false, (float*)&modelMatrix);
        glUniformMatrix4fv(
            glGetUniformLocation(currentShader->GetProgram(), "viewMatrix"),
            1, false, (float*)&viewMatrix);
        glUniformMatrix4fv(
            glGetUniformLocation(currentShader->GetProgram(), "projMatrix"),
            1, false, (float*)&projMatrix);
        glUniformMatrix4fv(
            glGetUniformLocation(currentShader->GetProgram(), "textureMatrix"),
            1, false, (float*)&textureMatrix);
    }
}

void Renderer::SwitchToPerspective(){
    projMatrix = Matrix4::Perspective(1.0f, 10000.0f, 
                (float)width / (float)height, fov);
}

void Renderer::SwitchToOrthographic(){
    projMatrix = Matrix4::Orthographic(-1.0f, 10000.0f, 
        width/2.0f,-width/2.0f,height/2.0f,-height/2.0f);
}