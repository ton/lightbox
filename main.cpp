#include "cameras/itf/pinhole_camera.h"

#include "core/itf/film.h"
#include "core/itf/mesh.h"
#include "core/itf/obj_reader.h"
#include "core/itf/scene.h"

#include "films/itf/memory_film.h"

#include "integrators/itf/raycast_integrator.h"

#include "math/itf/vector_3d.h"

#include "samplers/itf/simple_sampler.h"

#include "ui/sdl/itf/sdl_window.h"

#include <fstream>
#include <iostream>
#include <sstream>

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

void printUsage()
{
    std::cout << "Usage: lightbox <filename.obj> [-h]" << std::endl;
}

int main(int argc, char **argv)
{
    // Determine the name of the OBJ mesh to render.
    if (argc != 2)
    {
        printUsage();
        return 1;
    }

    if (argv[1] == "-h")
    {
        printUsage();
        return 0;
    }

    std::string objMeshFileName = argv[1];
    std::ifstream objMeshFile(objMeshFileName);
    if (!objMeshFile)
    {
        std::cerr << "Could not open OBJ file '" << objMeshFileName << "'." << std::endl;
        return 1;
    }

    std::unique_ptr<uint32_t> offscreenBuffer(new uint32_t[WINDOW_WIDTH * WINDOW_HEIGHT]);

    std::unique_ptr<lb::Film> film(std::make_unique<lb::MemoryFilm>(WINDOW_WIDTH, WINDOW_HEIGHT, offscreenBuffer.get()));
    std::unique_ptr<lb::Camera> camera(new lb::PinholeCamera(std::move(film),
                lb::Vector3d(0.0, 0.0, 8.0), lb::Vector3d(0.0, 0.0, -8.0), lb::Vector3d(0.0, 1.0, 0.0)));

    lb::Scene scene(
            std::make_unique<lb::RaycastIntegrator>(),
            std::make_unique<lb::SimpleSampler>(lb::Point2d(), lb::Point2d(WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1)),
            lb::ObjReader().loadMesh(objMeshFile),
            std::move(camera));

    // TODO: The SDL window should be the memory film ideally?
    lb::ui::SdlWindow window("LightBox", WINDOW_WIDTH, WINDOW_HEIGHT, offscreenBuffer.get());
    window.show(scene);

    return 0;
}
