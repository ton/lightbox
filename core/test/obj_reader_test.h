#include "core/itf/obj_reader.h"

#include "tests/base_test.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace lb;
using namespace lb::math;

BENCHMARK_TEST_FIXTURE(ObjReaderTest);

/// Tests loading a triangle mesh from OBJ.
TEST_F(ObjReaderTest, TestLoadTriangleMesh)
{
    // Open a very simple obj file describing a single triangle.
    std::ifstream objFile(getInputFile("triangle.obj"), std::ifstream::in);
    std::unique_ptr<Mesh> m = ObjReader().loadMesh(objFile);

    // The mesh should contain exactly one triangle.
    EXPECT_EQ(1, m->triangles().size());

    // Test that the triangle was correctly read.
    Triangle expected(Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0), Point(0.0, 1.0, 0.0));
    EXPECT_EQ(expected, m->triangles().front());
}

/// Tests that loading an invalid OBJ file results in a parse exception.
TEST_F(ObjReaderTest, TestLoadInvalidObjFile)
{
    // Open a very simple obj file describing a single triangle.
    std::ifstream objFile(getInputFile("invalid.obj"), std::ifstream::in);

    // Loading an invalid OBJ file should throw a parse exception.
    EXPECT_THROW(ObjReader().loadMesh(objFile), lb::ParseException);
}

/// Tests loading a cube mesh from OBJ.
TEST_F(ObjReaderTest, TestLoadCubeMesh)
{
    // Open a very simple obj file describing a single triangle.
    std::ifstream objFile(getInputFile("cube.obj"), std::ifstream::in);
    std::unique_ptr<Mesh> m(ObjReader().loadMesh(objFile));

    // The mesh should contain exactly twelve triangles.
    EXPECT_EQ(12, m->triangles().size());
}
