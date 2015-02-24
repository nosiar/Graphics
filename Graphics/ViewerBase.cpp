#include "ViewerBase.h"
#include<iostream>

namespace nosiar
{
    ViewerBase::ViewerBase(int width, int height) 
        : width_(width), height_(height), alpha{ 210.f }, beta{ -70.f }, zoom{ 20.f }, locked{ false }
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

    void ViewerBase::framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
    {
        width_ = width;
        height_ = height;

        float ratio = 1.f;

        if (height > 0)
            ratio = (float)width / (float)height;

        // Setup viewport
        glViewport(0, 0, width, height);

        // Change to the projection matrix and set our viewing volume
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, ratio, 1.0, 1024.0);
    }

    void ViewerBase::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        do_mouse_button_callback(window, button, action, mods);
    }

    void ViewerBase::cursor_position_callback(GLFWwindow* window, double x, double y)
    {
        do_cursor_position_callback(window, x, y);
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

    void ViewerBase::draw(GLFWwindow* window)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        GLfloat ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat diffuse[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
        GLfloat specular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat position[4] = { 0.0f, 0.0f, 10.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
        glLightfv(GL_LIGHT0, GL_POSITION, position);

        glTranslatef(0, 0, -zoom);

        glRotatef(beta, 1.0f, 0.0f, 0.0f);
        glRotatef(alpha, 0.0f, 0.0f, 1.0f);

        draw_scene();

        glfwSwapBuffers(window);
    }
}