#ifndef LB_PERSPECTIVE_CAMERA_H
#define LB_PERSPECTIVE_CAMERA_H

#include "core/itf/camera.h"

namespace lb {

class PerspectiveCamera : public Camera
{
    public:
        PerspectiveCamera(std::unique_ptr<Film> film);

        void calculateRay(const Sample& s, Ray& r) const;
};

}

#endif
