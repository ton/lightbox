#ifndef LB_INTEGRATOR_H
#define LB_INTEGRATOR_H

namespace lb {

class Ray;
class Scene;

class Integrator
{
    public:
        virtual float radiance(const Scene& scene, const Ray& ray) const = 0;
};

class SurfaceIntegrator : public Integrator { };

}

#endif
