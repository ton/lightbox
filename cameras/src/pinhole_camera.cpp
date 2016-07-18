#include "cameras/itf/pinhole_camera.h"

#include "core/itf/film.h"
#include "core/itf/ray.h"
#include "core/itf/sampling.h"

using namespace lb;

/// Constructs a pinhole camera, where the image plane's origin is pointed to
/// the by the look at vector relative from the camera's location. Together with
/// the look at vector, the up vector defines the camera's roll, pitch, and
/// tilt. Note: up vector should be a unit vector preferably.
PinholeCamera::PinholeCamera(std::unique_ptr<Film> film,
        const Point3d& location, const Vector3d& lookAt, const Vector3d& up):
    Camera(std::move(film), location),
    lookAt_(lookAt),
    left_(-cross(lookAt, up)),
    top_(cross(lookAt.normalize(), left_)),
    dx_(-2 * left_ / (film_->xResolution() - 1)),
    dy_(-2 * top_ / (film_->yResolution() - 1))
{
}

void PinholeCamera::calculateRay(const Sample& s, Ray& r) const
{
    r.o = location_;
    r.d = ((r.o + lookAt_ + left_ + s.imageX * dx_ + top_ + s.imageY * dy_) - r.o).normalize();
}
