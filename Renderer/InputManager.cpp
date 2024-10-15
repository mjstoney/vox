#include "InputManager.h"

// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLFWwindow *window = nullptr;

InputManager::InputManager(GLFWwindow *window, Camera *cam) : window(window), camera(cam)
{
    cameraSpeed = 0.5f;
    glfwGetWindowSize(window, &lastX, &lastY);
    lastX /= 2;
    lastY /= 2;
    W_PRESSED = false;
    S_PRESSED = false;
    A_PRESSED = false;
    D_PRESSED = false;
    SPACE_PRESSED = false;
    Z_PRESSED = false;

    CURSOR_ENABLED = false;
    FIRST_MOUSE = true;

}

InputManager::~InputManager()
{
    glfwDestroyWindow(window);
}

void InputManager::ProcessKeyboardInput(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        W_PRESSED = true;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        S_PRESSED = true;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        A_PRESSED = true;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        D_PRESSED = true;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        SPACE_PRESSED = true;
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        Z_PRESSED = true;
    }
    


    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        W_PRESSED = false;
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        S_PRESSED = false;
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        A_PRESSED = false;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        D_PRESSED = false;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    {
        SPACE_PRESSED = false;
    }
    if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
    {
        Z_PRESSED = false;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        if (window)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        if (CURSOR_ENABLED)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (key == GLFW_KEY_O)// && action == GLFW_PRESS)
    {
        camera->CONSTRAIN_PITCH = !camera->CONSTRAIN_PITCH;
    }
    if (key == GLFW_KEY_I)// && action == GLFW_PRESS)
    {
        camera->ResetViewMatrix();
    }
}

void InputManager::ProcessMouseMoveInput(float xposIn, float yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (FIRST_MOUSE)
    {
        lastX = xpos;
        lastY = ypos;
        FIRST_MOUSE = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void InputManager::Update(double deltaTime)
{
    if (A_PRESSED)
        camera->Translate(glm::vec3(-cameraSpeed * deltaTime, 0.0f, 0.0f));
    if (D_PRESSED)
        camera->Translate(glm::vec3(cameraSpeed * deltaTime, 0.0f, 0.0f));
    if (W_PRESSED)
        camera->Translate(glm::vec3(0.0f, 0.0f, cameraSpeed * deltaTime));
    if (S_PRESSED)
        camera->Translate(glm::vec3(0.0f, 0.0f, -cameraSpeed * deltaTime));
    if (SPACE_PRESSED)
        camera->Translate(glm::vec3(0.0f, cameraSpeed * deltaTime, 0.0f));
    if (Z_PRESSED)
        camera->Translate(glm::vec3(0.0f, -cameraSpeed * deltaTime, 0.0f));
    camera->UpdateCameraVectors();
}
