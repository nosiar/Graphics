#include <GL/freeglut.h>
#include "Application.h"
#include "Viewer.h"

int main(int argc, char* argv[])
{
    nosiar::Application::initialize(argc, argv, new Viewer);
}