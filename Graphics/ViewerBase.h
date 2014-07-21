#pragma once

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <array>

#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport) 
#endif

namespace nosiar
{
    class GRAPHICS_API Viewer_base
    {
        friend class Application;

    public:
        Viewer_base();
        virtual ~Viewer_base() {}

        virtual void init() {};
        virtual void draw_scene() {};

        void draw_axis();

    private:
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        void cursor_position_callback(GLFWwindow* window, double x, double y);
        void scroll_callback(GLFWwindow* window, double x, double y);
        void draw(GLFWwindow* window);

    protected:

        GLfloat alpha, beta;
        GLfloat zoom;

        GLboolean locked;

        int cursorX;
        int cursorY;

        int _width;
        int _height;
    };
}
