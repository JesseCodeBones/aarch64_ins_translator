#include "./aarch64cpp.hpp"
uint32_t Aarch64CPP::branch_immediate(uint32_t imm26) {
  uint32_t result = 0b000101 << 26;
  result = (imm26 & 0b11111111111111111111111111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::branch_immediate_conditional(uint32_t imm19, uint32_t cond) {
  uint32_t result = 0b010101 << 26;
  result = (imm19 & 0b1111111111111111111) << 5 | result;
  result = (cond & 0b1111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::branch_immediate_consistent_conditional(uint32_t imm19, uint32_t cond) {
  uint32_t result = 0b01010100000000000000000000010000;
  result = (imm19 & 0b1111111111111111111) << 5 | result;
  result = (cond & 0b1111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::bitfield_clear(uint8_t sf, uint8_t N, uint8_t immr, uint8_t imms, uint8_t rd) {
  uint32_t result = 0b00110011000000000000001111100000;
  result = (sf & 0b1) << 31 | result;
  result = (N & 0b1) << 22 | result;
  result = (immr & 0b111111) << 16 | result;
  result = (imms & 0b111111) << 10 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}
