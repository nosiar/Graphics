#pragma once

#include "ManipulatedViewer.h"

namespace nosiar
{
    class Texture;
}

class GLUquadric;

class Viewer : public nosiar::ManipulatedViewer
{
public:
    Viewer(int width, int height);
    virtual ~Viewer();

private:
    virtual void do_initialize() override;
    virtual void do_update() override;
    virtual void draw_scene() override;
    void draw_background();

private:
    nosiar::Texture* texture_back;
    nosiar::Texture* texture_sun;
    nosiar::Texture* texture_earth;
    nosiar::Texture* texture_moon;

    GLUquadric *sphere;

    int sun_rotation;
    int earth_rotation;
    int moon_rotation;

    int sun_revolution;
    int earth_revolution;
    int moon_revolution;
};