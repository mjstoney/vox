#include "Camera.h"

Camera::Camera()
{
    position = {0.0f, 0.0f, -5.0f};
    forward = {0.0f, 0.0f, 1.0f};
    up = {0.0f, 1.0f, 0.0f};
    right = {1.0f, 0.0f, 0.0f};
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));
    yaw = 90.0f;
    pitch = 0.0f;
    mouseSensitivity = 0.1;
    CONSTRAIN_PITCH = true;
}

Camera::Camera(glm::vec3 pos)
{
    position = pos;
    forward = {0.0f, 0.0f, 1.0f};
    up = {0.0f, 1.0f, 0.0f};
}

Camera::Camera(glm::vec3 pos, glm::vec3 forward, glm::vec3 up)
{
    position = pos;
    forward = forward;
    up = up;
}

void Camera::Translate(glm::vec3 translation)
{
    position += translation.x * right;
    position += translation.y * up;
    position += translation.z * forward;
}

Camera::~Camera()
{
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(forward, up)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    //up = glm::normalize(glm::cross(right, forward));


    // float roll = 0.0f;
    // glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1.0f, 0.0f, 0.0f));
    // glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    // glm::quat qRoll = glm::angleAxis(roll, glm::vec3(0, 0, 1));

    // glm::quat orientation = qPitch * qYaw;
    // orientation = glm::normalize(orientation);
    // glm::mat4 rotate = glm::mat4_cast(orientation);

    // glm::mat4 translate = glm::mat4(1.0f);
    // translate = glm::translate(translate, -position);
    // view = rotate * translate;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + forward, up);
}

void Camera::ResetViewMatrix()
{
    position = {0.0f, 0.0f, -5.0f};
    forward = {0.0f, 0.0f, 1.0f};
    up = {0.0f, 1.0f, 0.0f};
    right = {1.0f, 0.0f, 0.0f};
    view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));
    yaw = 90.0f;
    pitch = 0.0f;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;
    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (CONSTRAIN_PITCH)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    UpdateCameraVectors();
}
