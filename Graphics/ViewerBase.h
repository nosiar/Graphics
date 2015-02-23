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
    public:
        Viewer_base(int width, int height);
        virtual ~Viewer_base() {}

        void draw_axis();

        void init();
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        void cursor_position_callback(GLFWwindow* window, double x, double y);
        void scroll_callback(GLFWwindow* window, double x, double y);
        void draw(GLFWwindow* window);

        int get_width() const { return _width; }
        int get_height() const { return _height; }

    private:
        virtual void do_key_callback(GLFWwindow* /*window*/, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/) {}
        virtual void do_init() {}
        virtual void draw_scene() {}

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
