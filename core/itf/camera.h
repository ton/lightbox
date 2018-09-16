#ifndef LB_CAMERA_H
#define LB_CAMERA_H

#include "core/itf/film.h"

#include "math/itf/vector_3d.h"

#include <memory>

namespace lb {

class Ray;
class Sample;

/// Class representing an unstructured triangle mesh.
class Camera
{
    public:
        Camera(std::unique_ptr<Film> film, const Vector3d& location);

        Film& film() const { return *film_; }
        const Vector3d& location() const { return location_; }

        virtual void calculateRay(const Sample& s, Ray& r) const = 0;

        void setLocation(const Vector3d& location) { location_ = location; }

        virtual void rotate() = 0;

    protected:
        std::unique_ptr<Film> film_;

        Vector3d location_;
};

}

#endif
