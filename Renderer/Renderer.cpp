#include "Renderer.h"


Renderer::Renderer()
{

    camera = new Camera();
    window = new Window(camera);
    if (InitContext() != 0)
    {
        std::cout << "failed to init openGL\n.";
    };
    
    Load();
}

void Renderer::Load()
{
    scene = new Scene(camera);

}

Renderer::~Renderer()
{
    delete window;
    delete scene;
}


/// @brief Main renderer loop
/// @return None
void Renderer::Run()
{
    double previousTime = glfwGetTime();
    double lag = 0.0;
    while(!window->WindowShouldClose())
    {
        double currentTime = glfwGetTime();
        double elapsed = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsed;

        window->PollEvents();

        while (lag >= MS_PER_UPDATE)
        {
            scene->UpdateScene(lag / MS_PER_UPDATE);
            Window::inputManager->Update(lag / MS_PER_UPDATE);
            lag -= MS_PER_UPDATE;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->RenderScene();
        window->Render();
    }
}

/// @brief Initialize OpenGL using GLAD
/// @return 0 for sucessful init, -1 for failure
int Renderer::InitContext()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialized OpenGL using glad.\n";
        return -1;
    }
    SetClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    SetDepthTest(true);
    return 0;
}

/// @brief Sets the OpenGL Clear Color for clearing the screen
/// @param r Red value, between 0.0 and 1.0
/// @param g Green value, between 0.0 and 1.0
/// @param b Blue value, between 0.0 and 1.0
/// @param a Alpha value, between 0.0 and 1.0
void Renderer::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

/// @brief Sets the OpenGL Viewport
/// @param width Width of the viewport
/// @param height Height of the viewport
void Renderer::SetViewport(unsigned int width, unsigned int height)
{
    glViewport(0, 0, width, height);
}

/// @brief Enables or Disables OpenGL Depth Testing
/// @param toggle True to enable, False to disable
void Renderer::SetDepthTest(bool toggle)
{
    if (toggle) 
        glEnable(GL_DEPTH_TEST);
    else 
        glDisable(GL_DEPTH_TEST);
}