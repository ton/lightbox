#ifndef LB_SCENE_H
#define LB_SCENE_H

#include <memory>

namespace lb {

class Camera;
class Mesh;
class Ray;
class Sampler;
class SurfaceIntegrator;

class Scene
{
    public:
        Scene(std::unique_ptr<SurfaceIntegrator> surfaceIntegrator,
                std::unique_ptr<Sampler> sampler,
                std::unique_ptr<Mesh> mesh,
                std::unique_ptr<Camera> camera);

        Camera& camera() { return *camera_; }

        void render() const;
        bool intersects(const Ray& ray) const;

        /// Evaluates the radiance along the given ray for this scene.
        float radiance(const Ray& ray) const;

    private:
        /// Sampler responsible for sampling the image plane (?).
        std::unique_ptr<Sampler> sampler_;

        /// The surface integrator is responsible for calculating the integrals
        /// in the surface light transportation model.
        std::unique_ptr<SurfaceIntegrator> surfaceIntegrator_;

        /// The mesh associated with this scene. Contains all primitive data.
        std::unique_ptr<Mesh> mesh_;
        /// Camera used for viewing the scene.
        std::unique_ptr<Camera> camera_;
};

}

#endif
