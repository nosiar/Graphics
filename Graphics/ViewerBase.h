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

        void initialize();
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        void cursor_position_callback(GLFWwindow* window, double x, double y);
        void scroll_callback(GLFWwindow* window, double x, double y);

        void update();
        void draw(GLFWwindow* window);

        void draw_axis();
        void draw_grid();

        int width() const { return width_; }
        int height() const { return height_; }

    private:
        virtual void do_key_callback(GLFWwindow* /*window*/, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/) {}
        virtual void do_framebuffer_size_callback(GLFWwindow* /*window*/) {}
        virtual void do_mouse_button_callback(GLFWwindow* /*window*/, int /*button*/, int /*action*/, int /*mods*/) {}
        virtual void do_cursor_position_callback(GLFWwindow* /*window*/) {}
        virtual void do_scroll_callback(GLFWwindow* /*window*/, double /*x*/, double /*y*/) {}
        virtual void do_initialize() {}

        virtual void do_update() {}
        virtual void do_draw(GLFWwindow* /*window*/) {}

    protected:
        int cursor_x;
        int cursor_y;
        int prev_cursor_x;
        int prev_cursor_y;

        int width_;
        int height_;
    };
}
