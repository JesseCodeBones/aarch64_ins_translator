#include <cstdint>
#include "aarch64cpp.hpp"

uint32_t Aarch64CPP::tag_mask_insert(uint8_t xm, uint8_t xn, uint8_t xd) {
  uint32_t instruction = 0b10011010110000000001010000000000;
  instruction |= (xm & 0b11111) << 16;
  instruction |= (xn & 0b11111) << 5;
  instruction |= (xd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::halt_instruction(uint16_t imm16) {
  uint32_t instruction = 0b11010100010000000000000000000000;
  instruction |= (imm16 & 0b1111111111111111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::hypervisor_call(uint16_t imm16) {
  uint32_t instruction = 0b11010100000000000000000000000010;
  instruction |= (imm16 & 0b1111111111111111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::instruction_cache(uint8_t op1, uint8_t CRm, uint8_t op2,
                                       uint8_t Rt) {
  uint32_t instruction = 0b11010101000010000111000000000000;
  instruction |= (op1 & 0b111) << 16;
  instruction |= (CRm & 0b1111) << 8;
  instruction |= (op2 & 0b111) << 5;
  instruction |= (Rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::instruction_synchronization_barrier(uint8_t CRm) {
  uint32_t instruction = 0b11010101000000110011000011011111;
  instruction |= (CRm & 0b1111) << 8;
  return instruction;
}
