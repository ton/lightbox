#include "integrators/itf/raycast_integrator.h"

#include "core/itf/scene.h"

using namespace lb;

RaycastIntegrator::RaycastIntegrator()
{
}

float RaycastIntegrator::radiance(const Scene& scene, const Ray& ray) const
{
    return scene.intersects(ray) ? 1.0 : 0.0;
}
