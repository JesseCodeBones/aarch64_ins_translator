#include "aarch64cpp.hpp"

uint32_t Aarch64CPP::data_cache(uint8_t op1, uint8_t CRm, uint8_t op2,
                                uint8_t rt) {
  uint32_t instruction = 0b11010101000010000111000000000000;
  instruction |= (op1 & 0b111) << 16;
  instruction |= (CRm & 0b1111) << 8;
  instruction |= (op2 & 0b1111) << 5;
  instruction |= (rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::debug_change_pe_state_el1(uint16_t imm16) {
  uint32_t instruction = 0b11010100101000000000000000000001;
  instruction |= (imm16 & 0b1111111111111111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::debug_change_pe_state_el2(uint16_t imm16) {
  uint32_t instruction = 0b11010100101000000000000000000010;
  instruction |= (imm16 & 0b1111111111111111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::debug_change_pe_state_el3(uint16_t imm16) {
  uint32_t instruction = 0b11010100101000000000000000000011;
  instruction |= (imm16 & 0b1111111111111111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::data_gathering_hint() {
  return 0b11010101000000110010000011011111;
}

uint32_t Aarch64CPP::data_memory_barrier(uint8_t CRm) {
  uint32_t instruction = 0b11010101000000110011000010111111;
  instruction |= (CRm & 0b1111) << 8;
  return instruction;
}
uint32_t Aarch64CPP::debug_restore_process_state() {
  return 0b11010110101111110000001111100000;
}

uint32_t Aarch64CPP::data_synchronization_barrier(uint8_t CRm) {
  uint32_t instruction = 0b11010101000000110011000010011111;
  instruction |= (CRm & 0b1111) << 8;
  return instruction;
}

uint32_t Aarch64CPP::data_value_prediction(uint8_t rt) {
  uint32_t instruction = 0b11010101000010110111001110100000;
  instruction |= (rt & 0b11111) << 0;
  return instruction;
}