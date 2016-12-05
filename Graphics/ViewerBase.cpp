#include "ViewerBase.h"
#include <iostream>

namespace nosiar
{
    ViewerBase::ViewerBase(int width, int height)
        : width_(width), height_(height)
    {
    }

    void ViewerBase::initialize()
    {
        do_initialize();
    }

    void ViewerBase::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        do_key_callback(window, key, scancode, action, mods);
    }

    void ViewerBase::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        width_ = width;
        height_ = height;

        do_framebuffer_size_callback(window);
    }

    void ViewerBase::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        do_mouse_button_callback(window, button, action, mods);
    }

    void ViewerBase::cursor_position_callback(GLFWwindow* window, double x, double y)
    {
        prev_cursor_x = cursor_x;
        prev_cursor_y = cursor_y;
        cursor_x = static_cast<int>(x);
        cursor_y = static_cast<int>(y);

        do_cursor_position_callback(window);
    }

    void ViewerBase::scroll_callback(GLFWwindow* window, double x, double y)
    {
        do_scroll_callback(window, x, y);
    }

    void ViewerBase::draw_axis()
    {
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(12.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 12.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 12.0f);
        glEnd();
    }

    void ViewerBase::draw_grid()
    {

    }

    void ViewerBase::update(int elapsed_time)
    {
        do_update(elapsed_time);
    }

    void ViewerBase::draw(GLFWwindow* window)
    {
        do_draw();

        glfwSwapBuffers(window);
    }
}