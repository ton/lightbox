#include "core/itf/scene.h"

#include "core/itf/camera.h"
#include "core/itf/integrator.h"
#include "core/itf/mesh.h"
#include "core/itf/ray.h"
#include "core/itf/sampling.h"

#include "math/itf/vector_2d.h"

#include <iostream>

using namespace lb;

Scene::Scene(
        std::unique_ptr<SurfaceIntegrator> surfaceIntegrator,
        std::unique_ptr<Sampler> sampler,
        std::unique_ptr<Mesh> mesh,
        std::unique_ptr<Camera> camera):
    sampler_(std::move(sampler)),
    surfaceIntegrator_(std::move(surfaceIntegrator)),
    mesh_(std::move(mesh)),
    camera_(std::move(camera))
{
}

void Scene::render() const
{
    Sample imageSample { };
    Ray ray;

    while (sampler_->calculateNextSample(imageSample))
    {
        camera_->calculateRay(imageSample, ray);
        camera_->film().addSample(imageSample, radiance(ray));
    }
}

bool Scene::intersects(const Ray& r) const
{
    return mesh_->intersects(r);
}

float Scene::radiance(const Ray& ray) const
{
    return surfaceIntegrator_->radiance(*this, ray);
}
