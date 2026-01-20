#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
// #include "mesh.h"
#include "renderer.h"
#include "camera.h"

bool is_focus = true;

Renderer* renderer;
Camera* camera;
float scale = 100.0f;
float rotation = 0.0f;
float fov = 45.0f;
Vector3 position(0.0f,0.0f,-1500.0f);

bool keyW, keyA, keyS, keyD, keySPACE, keyLCTRL, keyQ, keyE = false;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!is_focus){
        return;
    }
    camera->UpdateCameraRotation(xpos, ypos);
    renderer->UpdateScene();
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            is_focus = true;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    (yoffset > 0) ? camera->SetZoom(camera->GetZoom() + 0.1f) : 
                        camera->SetZoom(camera->GetZoom() - 0.1f);

}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS){
        if (key == GLFW_KEY_W){
            keyW = true;
        }
        if (key == GLFW_KEY_S){
            keyS = true;
        }
        if (key == GLFW_KEY_A){
            keyA = true;
        }
        if (key == GLFW_KEY_D){
            keyD = true;
        }
        if (key == GLFW_KEY_Q){
            keyQ = true;
        }
        if (key == GLFW_KEY_E){
            keyE = true;
        }
        if (key == GLFW_KEY_SPACE){
            keySPACE = true;
        }
        if (key == GLFW_KEY_LEFT_CONTROL){
            keyLCTRL = true;
        }
    }

    if (action == GLFW_RELEASE){
        if (key == GLFW_KEY_W){
            keyW = false;
        }
        if (key == GLFW_KEY_S){
            keyS = false;
        }
        if (key == GLFW_KEY_A){
            keyA = false;
        }
        if (key == GLFW_KEY_D){
            keyD = false;
        }
        if (key == GLFW_KEY_Q){
            keyQ = false;
        }
        if (key == GLFW_KEY_E){
            keyE = false;;
        }
        if (key == GLFW_KEY_SPACE){
            keySPACE = false;
        }
        if (key == GLFW_KEY_LEFT_CONTROL){
            keyLCTRL = false;
        }
    }

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

        // if (key == GLFW_KEY_W){
        //     camera->UpdateCameraPosition(Vector3(0.f,0.f,-1.f), false);
        //     renderer->UpdateScene();
        // }
        // if (key == GLFW_KEY_S){
        //     camera->UpdateCameraPosition(Vector3(-0.f,0.f, 1.f), true);
        //     renderer->UpdateScene();
        // }
        // if (key == GLFW_KEY_A){
        //     camera->UpdateCameraPosition(Vector3(-1.f,0.f, 0.f), false);
        //     renderer->UpdateScene();
        // }
        // if (key == GLFW_KEY_D){
        //     camera->UpdateCameraPosition(Vector3(-1.f,0.f, 0.f), true);
        //     renderer->UpdateScene();
        // }
        // if (key == GLFW_KEY_SPACE){
        //     camera->UpdateCameraHeight(false);
        //     renderer->UpdateScene();
        // }
        // if (key == GLFW_KEY_X){
        //     camera->UpdateCameraHeight(true);
        //     renderer->UpdateScene();
        // }
        if (key == GLFW_KEY_ESCAPE){
            camera->ResetPrevCursorPos();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            is_focus = false;
        }


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

    camera = new Camera(window);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    renderer = new Renderer(window, camera, 800, 800); //needs to be destroyed before glfw terminate
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    cout << "renderer constructed\n\nrunning...\n";
    
    const GLuint program = glCreateProgram();
    glLinkProgram(program); 
    
    renderer->SetRotation(rotation);
    renderer->SetPosition(position);
    renderer->SetScale(scale);
    renderer->SetFov(fov);

    double lastFrame = 0.0;
    double delta;

    while (!glfwWindowShouldClose(window)){
        double currentFrame = glfwGetTime();
        delta = currentFrame-lastFrame;
        if (keyW){camera->UpdateCameraPosition(delta*1000.f, Vector3(0.f,0.f,-1.f), false);}
        if (keyA){camera->UpdateCameraPosition(delta*1000.f, Vector3(-1.f,0.f,0.f), false);}
        if (keyS){camera->UpdateCameraPosition(delta*1000.f, Vector3(0.f,0.f,-1.f), true);}
        if (keyD){camera->UpdateCameraPosition(delta*1000.f, Vector3(-1.f,0.f,0.f), true);}
        if (keySPACE){camera->UpdateCameraHeight(delta*1000.f, false);}
        if (keyLCTRL){camera->UpdateCameraHeight(delta*1000.f, true);}
        if (keyQ){camera->SetRoll(camera->GetRoll()+delta*100.f);}
        if (keyE){camera->SetRoll(camera->GetRoll()-delta*100.f);}
        renderer->UpdateScene();
        renderer->RenderScene();

        lastFrame = currentFrame;
    }

    delete renderer;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}