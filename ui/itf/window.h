#ifndef LB_UI_WINDOW_H
#define LB_UI_WINDOW_H

namespace lb {

class Scene;

namespace ui {

/// Base class for the main window of LightBox.
class Window
{
    public:
        Window(unsigned int width, unsigned int height);
        virtual ~Window();

        /// Returns the width in pixels of the drawable window area.
        unsigned int width() const { return width_; }
        /// Returns the height in pixels of the drawable window area.
        unsigned int height() const { return height_; }

        /// Shows the window, and renders the given scene as an image to the
        /// drawable area of the window.
        virtual void show(Scene& scene) = 0;

    private:
        /// Width in pixels of the drawable window area.
        int width_;
        /// Height in pixels of the drawable window area.
        int height_;
};

}}

#endif
