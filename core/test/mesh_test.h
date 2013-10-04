#include "core/itf/mesh.h"
#include "core/itf/triangle.h"

#include "tests/base_test.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace lb;

BENCHMARK_TEST_FIXTURE(MeshTest);

/// Tests loading a mesh object from OBJ.
TEST_F(MeshTest, TestLoadObj)
{
    // Open a very simple obj file describing a single triangle.
    std::ifstream objFile(getInputFile("triangle.obj"), std::ifstream::in);
    Mesh m = Mesh::loadFromObj(objFile);

    // The mesh should contain exactly one triangle.
    EXPECT_EQ(1, m.triangles().size());

    // Test that the triangle was correctly read.
    Triangle expected(Vertex(0.0, 0.0, 0.0), Vertex(1.0, 0.0, 0.0), Vertex(0.0, 1.0, 0.0));
    EXPECT_EQ(expected, m.triangles().front());
}
