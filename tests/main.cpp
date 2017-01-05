#include "common/test/exception_test.h"

#include "core/test/bounding_box_test.h"
#include "core/test/mesh_test.h"
#include "core/test/obj_reader_test.h"
#include "core/test/ray_test.h"

#include "math/test/quaternion_test.h"

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
