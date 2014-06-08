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

private:
    nosiar::Texture* texture_sun;
    nosiar::Texture* texture_earth;
    nosiar::Texture* texture_moon;

    GLUquadricObj *sphere;
};