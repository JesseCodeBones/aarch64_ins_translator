#include <chrono>
#include <gtest/gtest.h>
#include <stdexcept>
#include <thread>

#include "../aarch64cpp.hpp"

TEST(demo_test, always_change) {
  uint32_t result = Aarch64CPP::adc(1, 1, 1, 1, 1, 1);
  ASSERT_EQ(4194369569, result);
}