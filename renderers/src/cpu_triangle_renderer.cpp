#include "renderers/itf/cpu_triangle_renderer.h"

#include "math/itf/vector.h"
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
    Triangle t(Vertex(0.0 + j % 200, 0.0, 0.0), Vertex(200.0 + j % 200, 0.0, 0.0), Vertex(100.0 + j % 200, 200.0, 0.0));
    j += 2;

    Vector e1 = t.b - t.a;
    Vector e2 = t.c - t.a;

    Vector o(0.0, 0.0, -800.0);
    Vector tt = o - t.a;

    Vector q = cross(tt, e1);

    uint32_t *pixel = &(pixels[0]);
    for (unsigned int j = 0; j < height; ++j)
    {
        lb::math::Vector ray(-0.5 * width, 0.5 * height - j, 800);

        for (unsigned int i = 0; i < width; ++i)
        {
            ray.x += 1;

            Vector p = cross(ray.normalize(), e2);

            double k = dot(q, e2) / dot(p, e1);
            double l = dot(p, tt) / dot(p, e1);
            double m = dot(q, ray.normalize()) / dot(p, e1);

            if (1 - l - m >= 0 && l >= 0 && l <= 1 && m >= 0 && m <= 1)
            {
                *pixel++ = (0xff << 16) + (0xff << 8) + 0xff;
            }
            else
                *pixel++ = 0x00;
        }
    }
}
