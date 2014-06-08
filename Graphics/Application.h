#pragma once

#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport) 
#endif

namespace nosiar
{
    class Viewer_base;

    class GRAPHICS_API Application
    {
    public:
        static void initialize(int argc, char* argv[], Viewer_base* v);
        static void finalize();

        Application() = delete;
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;

    private:
        static void display();
        static void reshape(int w, int h);
        static void idle();
        static void motion(int x, int y);
        static void mouse(int button, int state, int x, int y);
    private:
        static Application* p;
        static Viewer_base* viewer;
    };
}