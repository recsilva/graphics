#include "camera.h"

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))

float xppos = 0.f;
float yppos = 0.f;

void Camera::UpdateCameraRotation(float xpos, float ypos){
    if (xppos == 0.f){
        xppos = xpos;
        yppos = ypos;
        return;
    }
    pitch-=sensitivity*(ypos-yppos);
    std::cout << (ypos - yppos) << "\n";
    yaw-=sensitivity*(xpos-xppos);
    std::cout << (xpos - xppos) << "\n";

    pitch = min(pitch, 90.f);
    pitch = max(pitch, -90.f);
    
    if (yaw < 0.f){
        yaw += 360.f;
    }
    if (yaw > 360.f){
        yaw -= 360.f;
    }

    xppos = xpos;
    yppos = ypos;
   
    std::cout << "pitch: " << pitch << " - yaw: " << yaw << "\n";
}

void Camera::UpdateCameraPosition(double delta, Vector3 dir, bool invert){
    Vector3 pos = Matrix4::Rotation(yaw, Vector3(0.0f,1.0f,0.0f)) * dir;
    
    if (!invert){
        position += pos * delta;
    }
    else{
        position -= pos * delta;
    }
    // BuildViewMatrix();
}

void Camera::UpdateCameraHeight(double delta, bool invert){
    (!invert) ? position.y += 1.0f * delta : position.y -= 1.0f * delta;
    // BuildViewMatrix();
}

void Camera::ResetPrevCursorPos(){
    xppos = 0.f;
    yppos = 0.f;
}

Matrix4 Camera::BuildViewMatrix(){
    return  Matrix4::Rotation(-roll, Vector3(0,0,1)) * 
            Matrix4::Rotation(-pitch, Vector3(1,0,0)) *
            Matrix4::Rotation(-yaw, Vector3(0,1,0)) *
            Matrix4::Translation(-position);
} // first transform so that camera is at world center,
    // then mod the yaw - horizontal rotation
      // finally mod the pitch - vertical rotation ( if rotations are 
                    // inversed, the pitch is unchanged, yaw is
                    // calculated from the current pitch and 
                    // is therefore tilted )
    //this code makes the camera not roll due to any factors