#include "core/itf/ray.h"
#include "core/itf/triangle.h"

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include <iomanip>
#include <iostream>
#include <chrono>

namespace po = boost::program_options;

void runIntersectionTests(unsigned int tests)
{
    // Define a triangle, and intersect it repeatedly, measuring the number of
    // intersection tests per second.
    lb::Triangle t(lb::Vertex(0.0, 0.0, 0.0), lb::Vertex(200.0, 0.0, 0.0), lb::Vertex(100.0, 200.0, 0.0));

    for (unsigned int j = 0; j < tests; ++j)
    {
        lb::Ray r(lb::math::Vector(0.0, 0.0, -200 + j), lb::math::Vector(-300, 300, 800));
        r.intersects(t);
    }
}

int main(int argc, char **argv)
{
    unsigned int intersectionTests = 1e07;
    unsigned int iterations = 10;

    po::options_description description("Available options");
    description.add_options()
        ("help,h", "Shows this help message")
        ("iterations,i", po::value<unsigned int>(&iterations), "Number of times to run the intersection tests")
        ("tests,t", po::value<unsigned int>(&intersectionTests), "Number of intersection tests");

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

    std::cout << "Starting benchmark with " << intersectionTests << " intersection tests for " << iterations << " iterations." << std::endl << std::endl;

    // Run the intersection test once, to prevent cluttered overall benchmark
    // results due to cache warmup effects.
    runIntersectionTests(intersectionTests);

    // Rasterize the triangle, multiple times.
    double totalSeconds = 0;
    for (unsigned int i = 0; i < iterations; ++i)
    {
        std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

        runIntersectionTests(intersectionTests);

        double seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
        long intersectionsPerSecond = intersectionTests / seconds;

        std::cout << std::setprecision(4) << std::fixed;
        std::cout << "Tested " << intersectionTests << " rays in " << seconds << "s, " << intersectionsPerSecond << " tests per second." << std::endl;

        totalSeconds += seconds;
    }

    std::cout << std::endl << "Overall tested " << intersectionTests * iterations << " rays in " << totalSeconds << "s, " <<
        (unsigned int)((intersectionTests * iterations) / totalSeconds) << " tests per second." << std::endl;

    return 0;
}
