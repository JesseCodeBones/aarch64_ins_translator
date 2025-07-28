//
// Created by jesse on 7/15/25.
//

#include "aarch64cpp_l.cpp"

#include "aarch64cpp.hpp"

uint32_t Aarch64CPP::atomic_single_copy_64_bytes(uint8_t Rn, uint8_t Rt) {
  uint32_t instruction = 0b11111000001111111101000000000000;
  instruction |= (Rn & 0b11111) << 5;
  instruction |= (Rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::atomic_load_add(uint8_t size, uint8_t flag_A, uint8_t flag_R, uint8_t Rs, uint8_t Rn, uint8_t Rt) {
  uint32_t instruction = 0b10111000001000000000000000000000;
  instruction |= (size & 0b11) << 30;
  instruction |= (flag_A & 0b1) << 23;
  instruction |= (flag_R & 0b1) << 22;
  instruction |= (Rs & 0b11111) << 16;
  instruction |= (Rn & 0b11111) << 5;
  instruction |= (Rt & 0b11111) << 0;
  return instruction;
}
