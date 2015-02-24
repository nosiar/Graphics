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
    virtual void do_update(int elapsed_time) override;
    virtual void draw_scene() override;
    void draw_background();

private:
    nosiar::Texture* texture_back;
    nosiar::Texture* texture_sun;
    nosiar::Texture* texture_earth;
    nosiar::Texture* texture_moon;

    GLUquadric *sphere;

    static const float sun_rot_per_tick;
    static const float earth_rot_per_tick;
    static const float moon_rot_per_tick;

    static const float earth_rev_per_tick;
    static const float moon_rev_per_tick;

    float sun_rotation = 0.0f;
    float earth_rotation = 0.0f;
    float moon_rotation = 0.0f;

    float earth_revolution = 0.0f;
    float moon_revolution = 0.0f;
};