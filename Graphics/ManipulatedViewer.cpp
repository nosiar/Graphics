#include "ManipulatedViewer.h"

namespace nosiar
{

    ManipulatedViewer::ManipulatedViewer(int width, int height)
        : ViewerBase(width, height), alpha{ 210.f }, beta{ -70.f }, zoom{ 20.f }, is_dragging{ false }
    {
    }

    ManipulatedViewer::~ManipulatedViewer()
    {
    }

    void ManipulatedViewer::do_key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
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
            break;
        }
    }

    void ManipulatedViewer::do_framebuffer_size_callback(GLFWwindow* /*window*/)
    {
        float ratio = 1.f;

        if (height_ > 0)
            ratio = static_cast<float>(width_) / height_;

        // Setup viewport
        glViewport(0, 0, width_, height_);

        // Change to the projection matrix and set our viewing volume
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, ratio, 1.0, 1024.0);
    }

    void ManipulatedViewer::do_mouse_button_callback(GLFWwindow* window, int button, int action, int /*mods*/)
    {
        if (button != GLFW_MOUSE_BUTTON_LEFT)
            return;

        if (action == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            is_dragging= GL_TRUE;
        }
        else
        {
            is_dragging = GL_FALSE;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    void ManipulatedViewer::do_cursor_position_callback(GLFWwindow* /*window*/)
    {
        if (is_dragging)
        {
            alpha += (GLfloat)(cursor_x - prev_cursor_x) / 5.f;
            beta += (GLfloat)(cursor_y - prev_cursor_y) / 5.f;
        }
    }

    void ManipulatedViewer::do_scroll_callback(GLFWwindow* /*window*/, double /*x*/, double y)
    {
        zoom += static_cast<float>(y) / 2.f;
        if (zoom < 0)
            zoom = 0;
    }

    void ManipulatedViewer::do_draw()
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
    }
}