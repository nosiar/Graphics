#include "ViewerBase.h"
#include<iostream>

namespace nosiar
{
    Viewer_base::Viewer_base(int width, int height) 
        : _width(width), _height(height), alpha{ 210.f }, beta{ -70.f }, zoom{ 20.f }, locked{ false }
    {
    }

    void Viewer_base::init()
    {
        do_init();
    }

    void Viewer_base::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action != GLFW_PRESS)
            return;

        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_LEFT:
            alpha += 5;
            break;
        case GLFW_KEY_RIGHT:
            alpha -= 5;
            break;
        case GLFW_KEY_UP:
            beta -= 5;
            break;
        case GLFW_KEY_DOWN:
            beta += 5;
            break;
        case GLFW_KEY_PAGE_UP:
            zoom -= 0.25f;
            if (zoom < 0.f)
                zoom = 0.f;
            break;
        case GLFW_KEY_PAGE_DOWN:
            zoom += 0.25f;
            break;
        default:
            do_key_callback(window, key, scancode, action, mods);
            break;
        }
    }

    void Viewer_base::framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height)
    {
        _width = width;
        _height = height;

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

    void Viewer_base::mouse_button_callback(GLFWwindow* window, int button, int action, int /*mods*/)
    {
        if (button != GLFW_MOUSE_BUTTON_LEFT)
            return;

        if (action == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            locked = GL_TRUE;
        }
        else
        {
            locked = GL_FALSE;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    void Viewer_base::cursor_position_callback(GLFWwindow* /*window*/, double x, double y)
    {
        if (locked)
        {
            alpha += (GLfloat)(x - cursorX) / 5.f;
            beta += (GLfloat)(y - cursorY) / 5.f;
        }

        cursorX = (int)x;
        cursorY = (int)y;
    }

    void Viewer_base::scroll_callback(GLFWwindow* /*window*/, double /*x*/, double y)
    {
        zoom += (float)y / 4.f;
        if (zoom < 0)
            zoom = 0;
    }

    void Viewer_base::draw_axis()
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

    void Viewer_base::draw(GLFWwindow* window)
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