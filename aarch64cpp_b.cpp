#include "./aarch64cpp.hpp"
uint32_t Aarch64CPP::branch_immediate(uint32_t imm26) {
  uint32_t result = 0b000101 << 26;
  result = (imm26 & 0b11111111111111111111111111) << 0 | result;
  return result;
}