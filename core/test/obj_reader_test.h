#include "core/src/obj_reader.h"

#include "tests/base_test.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace lb;

BENCHMARK_TEST_FIXTURE(ObjReaderTest);

/// Tests loading a triangle mesh from OBJ.
TEST_F(ObjReaderTest, TestLoadTriangleMesh)
{
    // Open a very simple obj file describing a single triangle.
    std::ifstream objFile(getInputFile("triangle.obj"), std::ifstream::in);
    Mesh m = ObjReader(objFile).mesh();

    // The mesh should contain exactly one triangle.
    EXPECT_EQ(1, m.triangles().size());

    // Test that the triangle was correctly read.
    Triangle expected(Vertex(0.0, 0.0, 0.0), Vertex(1.0, 0.0, 0.0), Vertex(0.0, 1.0, 0.0));
    EXPECT_EQ(expected, m.triangles().front());
}

/// Tests that loading an invalid OBJ file results in a parse exception.
TEST_F(ObjReaderTest, TestLoadInvalidObjFile)
{
    // Open a very simple obj file describing a single triangle.
    std::ifstream objFile(getInputFile("invalid.obj"), std::ifstream::in);

    // Loading an invalid OBJ file should throw a parse exception.
    EXPECT_THROW(ObjReader o(objFile), lb::ParseException);
}

/// Tests loading a cube mesh from OBJ.
TEST_F(ObjReaderTest, TestLoadCubeMesh)
{
    // Open a very simple obj file describing a single triangle.
    std::ifstream objFile(getInputFile("cube.obj"), std::ifstream::in);
    Mesh m = ObjReader(objFile).mesh();

    // The mesh should contain exactly twelve triangles.
    EXPECT_EQ(12, m.triangles().size());
}
