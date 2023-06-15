//Commit from laptop: Everything works well

#include "Application.h"
#include <stdlib.h> 
#include <time.h>

static int WINDOW_WIDTH = 1600;
static int WINDOW_HEIGHT = 800;

static Application* application = nullptr;

void window_size_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
 * Initializes a window and runs the City Builder application until the window is closed.
 *
 * @returns 0 if the application runs successfully.
 */
int main()
{
    srand(time(NULL));

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

/**
 * Callback function that is called when the window size is changed.
 *
 * @param window The GLFW window that was resized.
 * @param width The new width of the window.
 * @param height The new height of the window.
 *
 * @returns None
 */
void window_size_callback(GLFWwindow* window, int width, int height)
{
    application->Window_ResizedEvent(width, height);

    application->Update();
    application->Render();
    application->RenderUI();

    glfwSwapBuffers(window);
}

/**
 * Callback function that is called when the size of the framebuffer is changed.
 *
 * @param window A pointer to the GLFW window.
 * @param width The new width of the framebuffer.
 * @param height The new height of the framebuffer.
 *
 * @returns None
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    application->FrameBuffer_ResizedEvent(width, height);
}