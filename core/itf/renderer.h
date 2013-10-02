#ifndef LB_RENDERER_H
#define LB_RENDERER_H

#include <cstdint>
#include <memory>

namespace lb {

/// Base class for various renderer implementations. All renderers operate on a
/// pixel buffer for now, that is blitted to the screen using a concrete window
/// implementation.
class Renderer
{
    public:
        /// Constructor.
        Renderer() { }
        /// Destructor.
        virtual ~Renderer() { }

        /// Renders an image to the given pixel buffer with a resolution of \a
        /// width by \a height pixels.
        ///
        /// \param width the width of the pixel buffer
        /// \param height the height of the pixel buffer
        /// \param pixels the pixel buffer
        virtual void render(unsigned int width, unsigned int height, uint32_t *pixels) const = 0;
};

}

#endif
