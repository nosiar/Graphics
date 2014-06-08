#include "Application.h"
#include <GL/freeglut.h>
#include "ViewerBase.h"

namespace nosiar
{
    Application* Application::p;
    Viewer_base* Application::viewer;

    void Application::initialize(int argc, char* argv[], Viewer_base* v)
    {
        viewer = v;

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(700, 700);
        glutInitWindowPosition(250, 250);
        glutCreateWindow(argv[0]);

        viewer->init();

        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutIdleFunc(idle);
        glutMouseFunc(mouse);
        glutMotionFunc(motion);

        glutMainLoop();

        finalize();
    }

    void Application::finalize()
    {
        delete viewer;
    }

    void Application::display()
    {
        viewer->display();
    }

    void Application::reshape(int w, int h)
    {
        viewer->reshape(w, h);
    }

    void Application::idle()
    {
        viewer->idle();
    }

    void Application::motion(int x, int y)
    {
        viewer->motion(x, y);
    }

    void Application::mouse(int button, int state, int x, int y)
    {
        viewer->mouse(button, state, x, y);
    }
}