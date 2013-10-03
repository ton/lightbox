#ifndef LB_CPU_TRIANGLE_RENDERER_H
#define LB_CPU_TRIANGLE_RENDERER_H

#include "core/itf/renderer.h"

namespace lb {

/// Class representing an unstructured triangle mesh.
class CpuTriangleRenderer: public Renderer
{
    public:
        CpuTriangleRenderer();

        void render(unsigned int width, unsigned int height, uint32_t *pixels) const;
};

}

#endif
