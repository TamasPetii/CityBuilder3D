//Commit from laptop: Everything works well

#include "Application.h"

static int WINDOW_WIDTH = 1600;
static int WINDOW_HEIGHT = 800;

static Application* application = nullptr;

void window_size_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create Window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "City Builder", NULL, NULL);
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, mode->width / 2 - WINDOW_WIDTH / 2, mode->height / 2 - WINDOW_HEIGHT / 2);

    //Check Window Creation Errors
    if (!window)
    {
        std::cerr << "[glfwCreateWindow] : Error occured while initializing window in file {Main.cpp}" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Binding event functions to window */
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    //Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "[glewInit] : Error occured while initializing glew in file {Main.cpp}" << std::endl;
        return -1;
    }

    application = new Application(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    MyGui::Init(window);

    while (!glfwWindowShouldClose(window))
    {

        application->Update();
        application->Render();
        application->RenderUI();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    MyGui::Clean();

    delete application;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

//------------------Event-Handler-Functions------------------//

void window_size_callback(GLFWwindow* window, int width, int height)
{
    application->Window_ResizedEvent(width, height);

    application->Update();
    application->Render();
    application->RenderUI();

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    application->FrameBuffer_ResizedEvent(width, height);
}