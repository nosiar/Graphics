#pragma once

#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport) 
#endif

#include "ViewerBase.h"

namespace nosiar
{
    class GRAPHICS_API ManipulatedViewer : public ViewerBase
    {
    public:
        ManipulatedViewer(int width, int height);
        virtual ~ManipulatedViewer();

    private:
        virtual void do_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
        virtual void do_framebuffer_size_callback(GLFWwindow* window) override;
        virtual void do_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) override;
        virtual void do_cursor_position_callback(GLFWwindow* window) override;
        virtual void do_scroll_callback(GLFWwindow* window, double x, double y) override;
        virtual void do_draw() override;

        virtual void draw_scene() {};

    protected:
        GLboolean is_dragging;

        GLfloat alpha, beta;
        GLfloat zoom;
    };
}
