#include "renderers/itf/cpu_triangle_renderer.h"

#include "math/itf/vector.h"
#include "core/itf/ray.h"
#include "core/itf/triangle.h"

#include <iostream>

using namespace lb;
using namespace lb::math;

CpuTriangleRenderer::CpuTriangleRenderer():
    Renderer()
{
}

void CpuTriangleRenderer::render(unsigned int width, unsigned int height, uint32_t *pixels) const
{
    static int j = 0;
    Triangle a(Vertex(0.0 + j % 200, 0.0, 0.0), Vertex(200.0 + j % 200, 0.0, 0.0), Vertex(200.0 + j % 200, 200.0, 0.0));
    Triangle b(Vertex(0.0 + j % 200, 0.0, 0.0), Vertex(200.0 + j % 200, 200.0, 0.0), Vertex(0.0 + j % 200, 200.0, 0.0));
    j += 2;

    uint32_t *pixel = &(pixels[0]);
    for (unsigned int j = 0; j < height; ++j)
    {
        lb::Ray ray(Vector(0.0, 0.0, 800), Vector(-0.5 * width, 0.5 * height - j, -800));

        for (unsigned int i = 0; i < width; ++i)
        {
            ray.d.x += 1;

            if (ray.intersectsMollerTrumbore(a) || ray.intersectsMollerTrumbore(b))
            {
                *pixel++ = (0xff << 16) + (0xff << 8) + 0xff;
            }
            else
                *pixel++ = 0x00;
        }
    }
}
