#include <cstdint>
#include "aarch64cpp.hpp"

uint32_t Aarch64CPP::exclusive_or_not_shifted_register(uint8_t sf,
                                                       uint8_t shift,
                                                       uint8_t rm, uint8_t imm6,
                                                       uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b01001010001000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (shift & 0b11) << 22;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (imm6 & 0b111111) << 10;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::exclusive_or_immediate(uint8_t sf, uint8_t N, uint8_t immr,
                                            uint8_t imms, uint8_t rn,
                                            uint8_t rd) {
  uint32_t instruction = 0b01010010000000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (N & 0b1) << 22;
  instruction |= (immr & 0b11111) << 16;
  instruction |= (imms & 0b11111) << 10;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::exclusive_or_register(uint8_t sf, uint8_t shift,
                                           uint8_t rm, uint8_t imm6, uint8_t rn,
                                           uint8_t rd) {
  uint32_t instruction = 0b01001010000000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (shift & 0b11) << 22;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (imm6 & 0b111111) << 10;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::extract_register_from_a_pair_registers(
    uint8_t sf, uint8_t N, uint8_t rm, uint8_t imms, uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b00010011100000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (N & 0b1) << 22;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (imms & 0b111111) << 10;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}
