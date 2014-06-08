#pragma once

#include "ViewerBase.h"

namespace nosiar
{
    class Texture;
}

class Viewer : public nosiar::Viewer_base
{
public:
    Viewer();
    virtual ~Viewer();
    virtual void init();
    virtual void draw();
    virtual void tick();

    void draw_background();

private:
    nosiar::Texture* texture_back;
    nosiar::Texture* texture_sun;
    nosiar::Texture* texture_earth;
    nosiar::Texture* texture_moon;

    GLUquadricObj *sphere;

    int sun_rotation;
    int earth_rotation;
    int moon_rotation;

    int sun_revolution;
    int earth_revolution;
    int moon_revolution;
};