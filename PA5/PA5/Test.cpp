/**
 * @file Test.cpp
 * @author Benjamin Swanzey (benjamin.swanzey@wsu.edu)
 * @brief Implements unit tests of our queue and simulation.
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) Benjamin Swanzey 2023
 * 
 */

#include "Test.h"
UTEST_STATE();

UTEST(HiMom, TEST) {
    int i = 1;
    ASSERT_TRUE(i);  // pass!
    ASSERT_TRUE(42); // pass!
}

int RunTests(int argc, const char *const argv[]) {
  return utest_main(argc, argv);
}
