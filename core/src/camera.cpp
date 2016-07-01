#include "core/itf/camera.h"

#include "core/itf/film.h"
#include "core/itf/ray.h"

using namespace lb;

Camera::Camera(std::unique_ptr<Film> film, const Vector3d& location):
    film_(std::move(film)),
    location_(location)
{
}
