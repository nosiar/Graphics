#include "Application.h"

#include "ViewerBase.h"

namespace nosiar
{
    Application* Application::p;
    Viewer_base* Application::viewer;

    void Application::initialize(const char* title, Viewer_base* v)
    {
        viewer = v;

        glfwSetErrorCallback(error_callback);

        if (!glfwInit())
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

        GLFWwindow* window = glfwCreateWindow(700, 700, title, NULL, NULL);

        if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(window, key_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetScrollCallback(window, scroll_callback);

        glfwSetWindowPos(window, 250, 250);
        glfwShowWindow(window);

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        framebuffer_size_callback(window, w, h);

        viewer->init();

        while (!glfwWindowShouldClose(window))
        {
            viewer->draw(window);

            glfwPollEvents();
        }


        finalize();

        exit(EXIT_SUCCESS);
    }

    void Application::finalize()
    {
        delete viewer;
    }

    void Application::error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        viewer->key_callback(window, key, scancode, action, mods);
    }

    void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        viewer->framebuffer_size_callback(window, width, height);
    }

    void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        viewer->mouse_button_callback(window, button, action, mods);
    }

    void Application::cursor_position_callback(GLFWwindow* window, double x, double y)
    {
        viewer->cursor_position_callback(window, x, y);
    }

    void Application::scroll_callback(GLFWwindow* window, double x, double y)
    {
        viewer->scroll_callback(window, x, y);
    }
}