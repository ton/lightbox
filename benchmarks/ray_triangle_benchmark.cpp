#include "core/itf/ray.h"
#include "core/itf/triangle.h"

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include <iomanip>
#include <iostream>
#include <chrono>

namespace po = boost::program_options;

void runIntersectionTests(unsigned int width, unsigned int height, unsigned int frames, const lb::Triangle &t,
        bool (lb::Ray::*intersectionMethod)(const lb::Triangle &) const)
{
    for (unsigned int frame = 0; frame < frames; ++frame)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            lb::Ray ray(lb::Vertex(0.0, 0.0, 800), lb::math::Vector(-0.5 * width, 0.5 * height - j, -800));

            for (unsigned int i = 0; i < width; ++i)
            {
                ray.d.x += 1;

                (ray.*intersectionMethod)(t);
            }
        }
    }
}

enum IntersectionAlgorithm
{
    IA_DIDIER_BADOUEL,
    IA_MOLLER_TRUMBORE,
    IA_GEOMETRICALLY,
};

std::istream &operator>>(std::istream &in, IntersectionAlgorithm &ia)
{
    std::string token;
    in >> token;

    if (token == "didier_badouel")
    {
        ia = IA_DIDIER_BADOUEL;
    }
    else if (token == "geometrically")
    {
        ia = IA_GEOMETRICALLY;
    }
    else if (token == "moller_trumbore")
    {
        ia = IA_MOLLER_TRUMBORE;
    }

    return in;
}

std::ostream &operator<<(std::ostream &out, const IntersectionAlgorithm &ia)
{
    switch (ia)
    {
        case IA_DIDIER_BADOUEL:
            out << "didier_badouel";
            break;
        case IA_MOLLER_TRUMBORE:
            out << "moller_trumbore";
            break;
        case IA_GEOMETRICALLY:
            out << "geometrically";
            break;
    }

    return out;
}

int main(int argc, char **argv)
{
    unsigned int frames = 120;
    unsigned int iterations = 10;
    IntersectionAlgorithm algorithm = IA_MOLLER_TRUMBORE;

    po::options_description description("Available options");
    description.add_options()
        ("help,h", "Shows this help message")
        ("iterations,i", po::value<unsigned int>(&iterations), "Number of times to run the intersection tests")
        ("frames,f", po::value<unsigned int>(&frames), "Number of frames to render")
        ("type", po::value<IntersectionAlgorithm>(&algorithm), "Type of intersection test ['didier_badouel', 'moller_trumbore', 'geometrically']");

    po::variables_map vm;

    try
    {
        po::store(po::parse_command_line(argc, argv, description), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << "Ray/triangle intersection benchmark application." << std::endl << std::endl << description << std::endl;
            return 1;
        }
    }
    catch (const po::error &e)
    {
        std::cerr << "Error parsing command line: " << e.what() << "." << std::endl;
        return 1;
    }

    // Depending on the selected algorithm, use the correct intersection
    // algorithm.
    bool (lb::Ray::*intersectionMethod)(const lb::Triangle &) const;
    switch (algorithm)
    {
        case IA_DIDIER_BADOUEL:
            intersectionMethod = &lb::Ray::intersectsDidierBadouel;
            break;
        case IA_MOLLER_TRUMBORE:
            intersectionMethod = &lb::Ray::intersectsMollerTrumbore;
            break;
        case IA_GEOMETRICALLY:
            intersectionMethod = &lb::Ray::intersectsGeometrically;
            break;
    }

    // Determine the width and height in pixels of the frame to render
    // repeatedly.
    const unsigned int width = 640;
    const unsigned int height = 480;

    // For now, just intersect against a single triangle.
    lb::Triangle triangle(lb::Vertex(0.0, 0.0, 0.0), lb::Vertex(200.0, 0.0, 0.0), lb::Vertex(100.0, 200.0, 0.0));

    // Run the intersection test once for a single frame, to prevent cluttered
    // overall benchmark results due to cache warmup effects.
    runIntersectionTests(width, height, 1, triangle, intersectionMethod);

    // Total number of intersections per iteration to benchmark.
    const unsigned int intersections = width * height * frames;

    std::cout << "Starting benchmark performing " << intersections << " ray/triangle intersections for " << iterations << " iteration(s), using '" <<
        algorithm << "'..." << std::endl << std::endl;

    // Rasterize the triangle, multiple times.
    double totalSeconds = 0;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

        runIntersectionTests(width, height, frames, triangle, intersectionMethod);

        double seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
        long intersectionsPerSecond = (width * height * frames) / seconds;

        std::cout << std::setprecision(4) << std::fixed;
        std::cout << "Finished in " << seconds << "s, " << intersectionsPerSecond << " intersections per second." << std::endl;

        totalSeconds += seconds;
    }

    std::cout << std::endl << "Overall tested " << (intersections * iterations) << " rays in " << totalSeconds << "s, " <<
        (unsigned int)((intersections * iterations) / totalSeconds) << " intersections per second." << std::endl;

    return 0;
}
