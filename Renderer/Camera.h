#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream> // DEBUG only

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;

    glm::mat4 view;

    float yaw, pitch, mouseSensitivity;
    bool CONSTRAIN_PITCH;


    Camera();
    Camera(glm::vec3 pos);
    Camera(glm::vec3 pos, glm::vec3 forward, glm::vec3 up);
    void Translate(glm::vec3 translation);
    ~Camera();
    void UpdateCameraVectors();
    glm::mat4 GetViewMatrix();
    void ResetViewMatrix();
    void ProcessMouseMovement(float xoffset, float yoffset);
};