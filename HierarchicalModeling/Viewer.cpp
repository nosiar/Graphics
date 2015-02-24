#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <thread>

#include "Viewer.h"
#include "Texture.h"

Viewer::Viewer(int width, int height) : ManipulatedViewer(width, height)
{
}

Viewer::~Viewer()
{
    delete texture_sun;
    delete texture_earth;
    delete texture_moon;

    gluDeleteQuadric(sphere);
}

void Viewer::do_initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_SMOOTH);

    glLineWidth(3);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 70.0 };
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    texture_back = new nosiar::Texture("texture/space.png", nullptr, nullptr);
    texture_sun = new nosiar::Texture("texture/sun.png", nullptr, nullptr);
    texture_earth = new nosiar::Texture("texture/earth.png", nullptr, nullptr);
    texture_moon = new nosiar::Texture("texture/moon.png", nullptr, nullptr);

    sphere = gluNewQuadric();

    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);

    sun_rotation = 0;
    earth_rotation = 0;
    moon_rotation = 0;

    sun_revolution = 0;
    earth_revolution = 0;
    moon_revolution = 0;
}

void Viewer::draw_background()
{
    glMatrixMode(GL_PROJECTION);

    glPushMatrix();

    glLoadIdentity();
    gluOrtho2D(-width_ / 2, width_ / 2, -height_ / 2, height_ / 2);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();

    glDepthMask(false);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, texture_back->ColorMap());
    glBegin(GL_QUADS);
    glTexCoord2i(1, 1); glVertex2i(width_ / 2, height_ / 2);
    glTexCoord2i(1, 0); glVertex2i(width_ / 2, -height_ / 2);
    glTexCoord2i(0, 0); glVertex2i(-width_ / 2, -height_ / 2);
    glTexCoord2i(0, 1); glVertex2i(-width_ / 2, height_ / 2);
    glEnd();

    glDepthMask(true);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Viewer::draw_scene()
{
    calculate();

    draw_background();

    GLfloat light_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat light_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);


    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-135.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(-30.0f, 1.0f, -1.0f, 0.0f);

    glPushMatrix();
    glRotatef(static_cast<float>(sun_rotation), 0.0f, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture_sun->ColorMap());

    glDisable(GL_LIGHTING);
    gluSphere(sphere, 2.0, 20, 20);
    glEnable(GL_LIGHTING);

    glPopMatrix();

    float rad = static_cast<float>(M_PI) * earth_revolution / 180;
    glTranslatef(8 * std::cos(rad), 5 * std::sin(rad), 0.0f);
    glTranslatef(2, 0, 0);

    glPushMatrix();

    glRotatef(-23, 1, 0, 0);
    glRotatef(static_cast<float>(earth_rotation), 0.0f, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture_earth->ColorMap());
    gluSphere(sphere, 0.8, 44, 44);

    glPopMatrix();

    glRotatef(15, 0, 1, 0);

    rad = static_cast<float>(M_PI) * moon_revolution / 180;
    glTranslatef(2 * std::cos(rad), 2 * std::sin(rad), 0.0f);
    glRotatef(static_cast<float>(moon_rotation), 0.0f, 0.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, texture_moon->ColorMap());
    gluSphere(sphere, 0.4, 20, 20);
}

void Viewer::calculate()
{
    sun_rotation = (sun_rotation + 1) % 360;
    earth_rotation = (earth_rotation + 10) % 360;
    moon_rotation = (moon_rotation + 13) % 360;

    earth_revolution = (earth_revolution + 5) % 360;
    moon_revolution = (moon_revolution + 13) % 360;


    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}