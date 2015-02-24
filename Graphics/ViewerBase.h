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
    class GRAPHICS_API ViewerBase
    {
    public:
        ViewerBase(int width, int height);
        virtual ~ViewerBase() {}

        void draw_axis();

        void initialize();
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        void cursor_position_callback(GLFWwindow* window, double x, double y);
        void scroll_callback(GLFWwindow* window, double x, double y);
        void draw(GLFWwindow* window);

        int width() const { return width_; }
        int height() const { return height_; }

    private:
        virtual void do_key_callback(GLFWwindow* /*window*/, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/) {}
        virtual void do_framebuffer_size_callback(GLFWwindow* /*window*/, int /*width*/, int /*height*/) {}
        virtual void do_mouse_button_callback(GLFWwindow* /*window*/, int /*button*/, int /*action*/, int /*mods*/) {}
        virtual void do_cursor_position_callback(GLFWwindow* /*window*/, double /*x*/, double /*y*/) {}
        virtual void do_scroll_callback(GLFWwindow* /*window*/, double /*x*/, double /*y*/) {}
        virtual void do_initialize() {}
        virtual void draw_scene() {}

    protected:
        GLfloat alpha, beta;
        GLfloat zoom;

        GLboolean locked;

        int cursorX;
        int cursorY;

        int width_;
        int height_;
    };
}
