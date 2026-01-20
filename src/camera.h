#pragma once

#include "Matrix4.h"
#include "Vector3.h"
#include "GLFW/glfw3.h"

class Camera {
    public:
        Camera(GLFWwindow* window) : window(window){
            yaw = 0.0f;
            pitch = 0.0f;
        };
        Camera(GLFWwindow* window, float pitch, float yaw, Vector3 position) : window(window){
            this->pitch = pitch;
            this->yaw = yaw;
            this->position = position;
        }
        ~Camera(){}
        void UpdateCameraRotation(float xpos, float ypos);
        void UpdateCameraPosition(double delta, Vector3 pos, bool invert);
        void UpdateCameraHeight(double delta, bool invert);

        void ResetPrevCursorPos();

        Matrix4 BuildViewMatrix();

        //getset: pos, yaw, pitch
        Vector3 GetPosition() const {return position;}
        void    SetPosition(Vector3 val) {position = val;}
        float   GetYaw()    const   {return yaw;}
        void    SetYaw(float y)     {yaw = y;}
        float   GetPitch()  const   {return pitch;}
        void    SetPitch(float p)   {pitch = p;}
        float   GetRoll()  const   {return roll;}
        void    SetRoll(float r)   {roll = r;}

        float GetZoom(){return zoom;}
        void SetZoom(float z){zoom = z;}
    protected:
        float yaw;      //horizontal rotation
        float pitch;    //vertical rotation
        float roll;     //you roll like a ball
        Vector3 position; //set to Vector3(0,0,0) by constructor
        GLFWwindow* window;

        float sensitivity = 0.3f;
        float zoom = 1.0f;
};