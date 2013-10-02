#include "mesh/itf/mesh.h"
#include "renderers/itf/static_noise_renderer.h"
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

    // Load the triangle mesh.
    lb::mesh::Mesh m = lb::mesh::Mesh::loadFromObj(objMeshFile);

    // Create the CPU based triangle renderer.
    lb::ui::SdlWindow window("LightBox", WINDOW_WIDTH, WINDOW_HEIGHT);
    window.show(lb::StaticNoiseRenderer());

    return 0;
}
