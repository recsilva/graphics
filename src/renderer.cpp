#include "renderer.h"

Renderer::Renderer(GLFWwindow* window) : window(window){
    triangle = Mesh::generate_triangle();

    currentShader = new Shader("shaders/basicVertex.glsl","shaders/colorFragment.glsl");

    if (!currentShader->LinkProgram()){
        return;
    }
    init = true;
}
Renderer::~Renderer(){
    delete triangle;
}

void Renderer::RenderScene(){
    // glViewport(0,0,500,500);
    glClearColor (0.2f ,0.2f ,0.2f ,1.0f );
    glClear(GL_COLOR_BUFFER_BIT);

    triangle->draw();
    glUseProgram(currentShader->GetProgram());
    glfwSwapBuffers(window);
    glfwPollEvents();
}