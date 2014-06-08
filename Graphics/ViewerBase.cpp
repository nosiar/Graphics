#include "ViewerBase.h"

namespace nosiar
{
    Viewer_base::Viewer_base()
        : mouse_button{ Mouse_button::none }, modifier{ Modifier::none }
        , eye({ 0.0f, 0.0f, 10.0f }), rotation_angles({ 0.0f, 0.0f, 0.0f })
    {
    }

    void Viewer_base::display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        GLfloat lightKa[4] = { 0.8f, 0.6f, 0.5f, 1.f };
        GLfloat lightKd[4] = { 0.9f, 0.9f, 0.9f, 1.f };
        GLfloat lightKs[4] = { 0.9f, 0.9f, 0.9f, 1.f };
        GLfloat lightPos[4] = { 0.f, 0.f, 10.f, 1.f };

        glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

        glTranslatef(-eye[0], -eye[1], -eye[2]);

        //	/* rotates the screen by the angles provided by rot array */
        glRotatef(rotation_angles[0], 1.0f, 0.0f, 0.0f);
        glRotatef(rotation_angles[1], 0.0f, 1.0f, 0.0f);
        glRotatef(rotation_angles[2], 0.0f, 0.0f, 1.0f);

        draw();

        glutSwapBuffers();
    }

    void Viewer_base::reshape(int w, int h)
    {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, .1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void Viewer_base::idle()
    {
        glutPostRedisplay();
    }

    void Viewer_base::motion(int x, int y)
    {
        switch (mouse_button)
        {
        case Mouse_button::none:
            break;
        case Mouse_button::left:
            if (modifier == Modifier::none)
            {
                rotation_angles[0] -= (prev_mouse_y - y);
                rotation_angles[1] -= (prev_mouse_x - x);
                clamp_angles();
            }
            else
            {
                eye[0] += (prev_mouse_x - x) * 0.01f;
                eye[1] -= (prev_mouse_y - y) * 0.01f;
            }
            break;
        case Mouse_button::right:
            eye[2] -= (prev_mouse_y - y) * 0.05f;
            break;
        default:
            break;
        }

        prev_mouse_x = x;
        prev_mouse_y = y;
    }

    void Viewer_base::mouse(int button, int state, int x, int y)
    {
        switch (state)
        {
        case GLUT_DOWN:
            prev_mouse_x = x;
            prev_mouse_y = y;

            mouse_button = static_cast<Mouse_button>(button);
            modifier = static_cast<Modifier>(glutGetModifiers());
            break;
        case GLUT_UP:
            mouse_button = Mouse_button::none;
            modifier = Modifier::none;
            break;
        default:
            break;
        }
    }

    void Viewer_base::clamp_angles()
    {
        for (int i = 0; i < 3; ++i)
            if (rotation_angles[i] > 360 || rotation_angles[i] < -360)
                rotation_angles[i] = 0;
    }
}