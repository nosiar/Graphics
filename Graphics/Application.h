#pragma once

#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport) 
#endif

#include <GLFW/glfw3.h>

namespace nosiar
{
    class ViewerBase;

    class GRAPHICS_API Application
    {
    public:
        static void initialize(const char* title, ViewerBase* v);
        static void finalize();

        /*static void start();
        static void pause();*/

        static int get_real_time();
        static int get_time();

        Application() = delete;
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;

    private:
        static void error_callback(int error, const char* description);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void cursor_position_callback(GLFWwindow* window, double x, double y);
        static void scroll_callback(GLFWwindow* window, double x, double y);

    private:
        static ViewerBase* viewer;
        static long long start_time;
        static int paused_time;
    };
}