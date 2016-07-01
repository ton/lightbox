#ifndef LB_PINHOLE_CAMERA_H
#define LB_PINHOLE_CAMERA_H

#include "core/itf/camera.h"

#include "math/itf/vector_3d.h"

namespace lb {

class PinholeCamera : public Camera
{
    public:
        PinholeCamera(std::unique_ptr<Film> film, const Vector3d& location, const Vector3d& lookAt, const Vector3d& up);

        void calculateRay(const Sample& s, Ray& r) const;

    private:
        Vector3d lookAt_;

        Vector3d left_;
        Vector3d top_;

        /// Vector in object space pointing to the next image sample along the
        /// horizontal axis of the film (from left to right).
        Vector3d dx_;
        /// Vector in object space pointing to the next image location along the
        /// vertical axis of the film (from top to bottom).
        Vector3d dy_;
};

}

#endif
