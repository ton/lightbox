#ifndef LB_UI_WINDOW_H
#define LB_UI_WINDOW_H

namespace lb {

class Renderer;

namespace ui {

/// Base class for the main window of LightBox.
class Window
{
    public:
        Window(unsigned int width, unsigned int height);
        virtual ~Window();

        /// Returns the width in pixels of the drawable window area.
        ///
        /// \returns the width in pixels of the drawable window area
        unsigned int width() const { return width_; }
        /// Returns the height in pixels of the drawable window area.
        ///
        /// \returns the height in pixels of the drawable window area
        unsigned int height() const { return height_; }

        /// Shows the window, and uses the given \a renderer to render an image
        /// to the drawable area of the window.
        ///
        /// \param renderer the renderer to use for rendering an image to the
        ///     drawable are of the window
        virtual void show(const Renderer &renderer) = 0;

    private:
        /// Width in pixels of the drawable window area.
        int width_;
        /// Height in pixels of the drawable window area.
        int height_;
};

}}

#endif
