#pragma once

#include <GL/freeglut.h>
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
        virtual void draw() {};
        virtual void tick() {};

        void draw_axis();

    private:
        void display();
        void reshape(int w, int h);
        void idle();
        void motion(int x, int y);
        void mouse(int button, int state, int x, int y);
        void clamp_angles();

    protected:
        enum class Mouse_button : char {
            none = -1,
            left = GLUT_LEFT_BUTTON,
            right = GLUT_RIGHT_BUTTON,
        };

        enum class Modifier : char {
            none = 0,
            shift = GLUT_ACTIVE_SHIFT,
            ctrl = GLUT_ACTIVE_CTRL,
            alt = GLUT_ACTIVE_ALT,
        };

        Mouse_button mouse_button;
        Modifier modifier;

        int prev_mouse_x;
        int prev_mouse_y;
        
        int width;
        int height;

        std::array<float, 3> eye;
        std::array<float, 3> rotation_angles;
    };
}
