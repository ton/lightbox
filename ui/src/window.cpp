#include "ui/itf/window.h"

using namespace lb::ui;

/// Constructs a UI window for displaying a renderer scene.
Window::Window(unsigned int width, unsigned int height):
    width_(width),
    height_(height)
{
}

/// Destructor.
Window::~Window()
{
}
