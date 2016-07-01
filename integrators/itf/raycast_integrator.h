#ifndef LB_RAYCAST_INTEGRATOR_H
#define LB_RAYCAST_INTEGRATOR_H

#include "core/itf/integrator.h"

#include <memory>

namespace lb {

class Ray;
class Scene;

class RaycastIntegrator : public SurfaceIntegrator
{
    public:
        RaycastIntegrator();

        float radiance(const Scene& scene, const Ray& ray) const override;
};

}

#endif
