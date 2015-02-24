#include "Application.h"
#include "ViewerBase.h"
#include <chrono>

namespace nosiar
{
    ViewerBase* Application::viewer = nullptr;
    long long Application::start_time = 0;
    int Application::paused_time = 0;
    GLFWwindow*  Application::window_ = nullptr;

    void Application::create(const char* title, ViewerBase* v)
    {
        viewer = v;

        glfwSetErrorCallback(error_callback);

        if (!glfwInit())
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

        window_ = glfwCreateWindow(viewer->width(), viewer->height(), title, NULL, NULL);

        if (!window_)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(window_, key_callback);
        glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
        glfwSetMouseButtonCallback(window_, mouse_button_callback);
        glfwSetCursorPosCallback(window_, cursor_position_callback);
        glfwSetScrollCallback(window_, scroll_callback);

        // TODO: add variable
        glfwSetWindowPos(window_, 250, 250);
        glfwShowWindow(window_);

        glfwMakeContextCurrent(window_);
        glfwSwapInterval(1);
        int ii = sizeof window_;
        ii = (ii);
        int w, h;
        glfwGetFramebufferSize(window_, &w, &h);
        framebuffer_size_callback(window_, w, h);

        viewer->initialize();

        start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

        loop();

        finalize();

        exit(EXIT_SUCCESS);
    }

    void Application::loop()
    {
        int prev_time = get_time();

        while (!glfwWindowShouldClose(window_))
        {
            int current_time = get_time();
            while (current_time - prev_time > 20)
            {
                viewer->update(current_time - prev_time);
                viewer->draw(window_);

                prev_time = current_time;

                glfwPollEvents();
            }
        }
    }

    void Application::finalize()
    {
        if (viewer)
            delete viewer;
    }

    int Application::get_real_time()
    {
        long long current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        return static_cast<int>(current_time - start_time);
    }

    int Application::get_time()
    {
        return get_real_time() - paused_time;
    }


    void Application::error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error %d: %s\n", error, description);
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