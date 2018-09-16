#include "cameras/itf/pinhole_camera.h"

#include "core/itf/film.h"
#include "core/itf/ray.h"
#include "core/itf/sampling.h"

#include "math/itf/constants.h"
#include "math/itf/quaternion.h"

#include <iostream>

using namespace lb;

// #define SINE

/// Constructs a pinhole camera, where the image plane's origin is pointed to
/// the by the look at vector relative from the camera's location. Together with
/// the look at vector, the up vector defines the camera's roll, pitch, and
/// tilt. Note: up vector should be a unit vector preferably.
PinholeCamera::PinholeCamera(std::unique_ptr<Film> film,
        const Point3d& location, const Vector3d& lookAt, const Vector3d& up):
    Camera(std::move(film), location),
    lookAt_(lookAt.normalized()),
    left_(cross(up, lookAt_)),
    up_(cross(lookAt_, left_)),
    cLocation_(location),
    dx_(-2 * left_ / (film_->xResolution() - 1)),
    dy_(-2 * up_ / (film_->yResolution() - 1)),
    rotationStep_(0)
{
}

void PinholeCamera::calculateRay(const Sample& s, Ray& r) const
{
    r.o = location_;
    r.d = ((r.o + lookAt_ + left_ + s.imageX * dx_ + up_ + s.imageY * dy_) - r.o).normalized();
}

void PinholeCamera::rotate()
{
    double alpha = rotationStep_++ * (lb::PI / 50.0);
    double beta = std::sin(rotationStep_ / 50.0) * (lb::PI / 4.0);

    static const Quaternion l({0, 1, 0}, lb::PI / 50.0);

    Quaternion p({0, 1, 0}, alpha);
    Quaternion q({1, 0, 0}, beta);

    Quaternion pq = (p * q);

    location_ = pq.rotate(cLocation_);
    left_ = l.rotate(left_);

    lookAt_ = (-location_).normalized();

    up_ = cross(lookAt_, left_);

    dx_ = -2 * left_ / (film_->xResolution() - 1);
    dy_ = -2 * up_ / (film_->yResolution() - 1);
}
