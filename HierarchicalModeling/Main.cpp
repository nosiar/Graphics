#include "Application.h"
#include "Viewer.h"

int main()
{
    nosiar::Application::initialize("Hierarchical Modeling", new Viewer);
}