#include "cameras/itf/perspective_camera.h"

#include "core/itf/film.h"

using namespace lb;

PerspectiveCamera::PerspectiveCamera(std::unique_ptr<Film> film):
    Camera(std::move(film), Vector3d())
{
}

void PerspectiveCamera::calculateRay(const Sample& s, Ray& r) const
{
}
