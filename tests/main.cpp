#include "common/test/exception_test.h"

#include "core/test/mesh_test.h"
#include "core/test/ray_test.h"

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
