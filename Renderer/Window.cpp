#include "Window.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);


InputManager* Window::inputManager = nullptr;


/// @brief Default constructor, sets the GLFWwindow to nullptr and calls Init()
Window::Window(Camera *cam) : mp_window(nullptr)
{
    m_width = 1600;
    m_height = 1200;
    Init();
    inputManager = new InputManager(mp_window, cam);
}

Window::~Window()
{
    glfwDestroyWindow(mp_window);
    glfwTerminate();
}

/// @brief Initialize GLFW, Creates a GLFWwindow, and makes the window context current
/// @return 0 for Successful Init, -1 if errors
int Window::Init()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW.\n";
        return -1;
    }
    mp_window = glfwCreateWindow(m_width, m_height, "Interesting Title", NULL, NULL);
    if (!mp_window)
    {
        std::cout << "Failed to create GLFWwindow.\n";
        return -1;
    }
    glfwMakeContextCurrent(mp_window);
    if (mp_window) {
        glfwSetWindowUserPointer(mp_window, this);  // Store the 'this' pointer
        glfwSetKeyCallback(mp_window, key_callback);  // Set the static callback
        glfwSetCursorPosCallback(mp_window, cursor_position_callback);
        glfwSetInputMode(mp_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(mp_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


    return 0;
}


/// @brief Checks the glfwWindowShouldClose status
/// @return True if the window should close, False if not
bool Window::WindowShouldClose()
{
    return glfwWindowShouldClose(mp_window);
}

void Window::CloseWindow() 
{
    glfwSetWindowShouldClose(mp_window, GLFW_TRUE);
}
/// @brief GLFW Poll window events
/// @return None
void Window::PollEvents()
{
    glfwPollEvents();
}

/// @brief Render to the GLFW window
void Window::Render()
{
    glfwSwapBuffers(mp_window);
}



void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (instance) {
        // Call the member function of the instance
        instance->handle_key_input(key, scancode, action, mods);
    }
}

void Window::handle_key_input(int key, int scancode, int action, int mods)
{
    inputManager->ProcessKeyboardInput(key, scancode, action, mods);
}

void Window::cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    inputManager->ProcessMouseMoveInput(static_cast<float>(xpos), static_cast<float>(ypos));
}

