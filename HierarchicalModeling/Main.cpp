#include "Application.h"
#include "Viewer.h"

int main()
{
    nosiar::Application::create("Hierarchical Modeling", new Viewer(700, 700));
}