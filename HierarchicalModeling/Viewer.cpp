#include "Viewer.h"
#include "Texture.h"

Viewer::Viewer()
{
}

Viewer::~Viewer()
{
    delete texture_sun;
    delete texture_earth;
    delete texture_moon;

    gluDeleteQuadric(sphere);
}

void Viewer::init()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    texture_sun = new nosiar::Texture("texture/sun.png", nullptr, nullptr);
    texture_earth = new nosiar::Texture("texture/earth.png", nullptr, nullptr);
    texture_moon = new nosiar::Texture("texture/moon.png", nullptr, nullptr);

    sphere = gluNewQuadric();

    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
}

void Viewer::draw()
{
    glBindTexture(GL_TEXTURE_2D, texture_sun->ColorMap());
    gluSphere(sphere, 2.0, 20, 20);

    glTranslatef(2, 0, 0);
    glBindTexture(GL_TEXTURE_2D, texture_earth->ColorMap());
    gluSphere(sphere, 2.0, 20, 20);

    glTranslatef(-4, 0, 0);
    glBindTexture(GL_TEXTURE_2D, texture_moon->ColorMap());
    gluSphere(sphere, 2.0, 20, 20);
}