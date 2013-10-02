#include "renderers/itf/static_noise_renderer.h"

#include <iostream>

namespace lb {

StaticNoiseRenderer::StaticNoiseRenderer():
    Renderer()
{
}

void StaticNoiseRenderer::render(unsigned int width, unsigned int height, uint32_t *pixels) const
{
    uint32_t *pixel = &(pixels[0]);
    for (unsigned int j = 0; j < height; ++j)
    {
        char gray = rand();
        for (unsigned int i = 0; i < width; ++i)
        {
            gray += 25;
            *pixel++ = (gray << 16) + (gray << 8) + gray;
        }
    }
}

}
