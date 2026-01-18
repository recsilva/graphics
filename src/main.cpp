#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
// #include "mesh.h"
#include "renderer.h"

Renderer* renderer;
float scale = 100.0f;
float rotation = 0.0f;
float fov = 45.0f;
Vector3 position(0.0f,0.0f,-1500.0f);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_REPEAT || action == GLFW_PRESS){
        if (key == GLFW_KEY_O){renderer->SwitchToOrthographic();}
        if (key == GLFW_KEY_P){renderer->SwitchToPerspective();}

        if (key == GLFW_KEY_LEFT){position.x-=1;}
        if (key == GLFW_KEY_RIGHT){position.x+=1;}
        if (key == GLFW_KEY_UP){position.y+=1;}
        if (key == GLFW_KEY_DOWN){position.y-=1;}
        if (key == GLFW_KEY_PAGE_UP){position.z+=1;}
        if (key == GLFW_KEY_PAGE_DOWN){position.z-=1;}

        if (key == GLFW_KEY_LEFT_BRACKET){rotation+=1;}
        if (key == GLFW_KEY_RIGHT_BRACKET){rotation-=1;}

        if (key == GLFW_KEY_MINUS){scale-=1;}
        if (key == GLFW_KEY_EQUAL){scale+=1;}

        if (key == GLFW_KEY_9){fov-=1;}
        if (key == GLFW_KEY_0){fov+=1;}

        renderer->SetRotation(rotation);
        renderer->SetPosition(position);
        renderer->SetScale(scale);
        renderer->SetFov(fov);
    }
}

int main(){
    if (!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,800,"hello triangle", NULL, NULL);
    
    if (!window){
        return -1;
    }

    cout << "window created\n\n";

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);

    renderer = new Renderer(window, 800, 800); //needs to be destroyed before glfw terminate
    
    cout << "renderer constructed\n\nrunning...\n";
    
    const GLuint program = glCreateProgram();
    glLinkProgram(program); 
    
    renderer->SetRotation(rotation);
    renderer->SetPosition(position);
    renderer->SetScale(scale);
    renderer->SetFov(fov);

    while (!glfwWindowShouldClose(window)){
        
        renderer->RenderScene();
    }

    delete renderer;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}