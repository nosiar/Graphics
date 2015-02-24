#include "ManipulatedViewer.h"

namespace nosiar
{

ManipulatedViewer::ManipulatedViewer(int width, int height) : ViewerBase(width, height)
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

void ManipulatedViewer::do_mouse_button_callback(GLFWwindow* window, int button, int action, int /*mods*/)
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

void ManipulatedViewer::do_cursor_position_callback(GLFWwindow* /*window*/, double x, double y)
{
    if (locked)
    {
        alpha += (GLfloat)(x - cursorX) / 5.f;
        beta += (GLfloat)(y - cursorY) / 5.f;
    }

    cursorX = (int)x;
    cursorY = (int)y;
}

void ManipulatedViewer::do_scroll_callback(GLFWwindow* /*window*/, double /*x*/, double y)
{
    zoom += (float)y / 4.f;
    if (zoom < 0)
        zoom = 0;
}

}