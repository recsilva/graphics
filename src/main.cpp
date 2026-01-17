#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
// #include "mesh.h"
#include "renderer.h"

int main(){
    cout << "start\n";
    if (!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600,500,"hello triangle", NULL, NULL);
    
    if (!window){
        return -1;
    }

    cout << "window created\n";

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);


    Renderer* renderer = new Renderer(window); //needs to be destroyed before glfw terminate
    
    cout << "renderer constructed\n";

    const GLuint program = glCreateProgram();
    glLinkProgram(program); 
    
    while (!glfwWindowShouldClose(window)){
        renderer->RenderScene();
    }

    delete renderer;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}