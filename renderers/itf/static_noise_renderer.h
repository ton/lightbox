#ifndef LB_STATIC_NOISE_RENDERER_H
#define LB_STATIC_NOISE_RENDERER_H

#include "core/itf/renderer.h"

namespace lb {

/// Class representing an unstructured triangle mesh.
class StaticNoiseRenderer: public Renderer
{
    public:
        StaticNoiseRenderer();

        void render(unsigned int width, unsigned int height, uint32_t *pixels) const;
};

}

#endif
