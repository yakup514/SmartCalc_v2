#include "gtest/gtest.h"
#include "def_calc_test.h"
#include "debit_calc_test.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
