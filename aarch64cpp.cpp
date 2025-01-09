#include "./aarch64cpp.hpp"
#include <cstdint>

uint32_t Aarch64CPP::ret_rn(uint8_t rn) {
  uint32_t result = 0xd65f0000;
  result = (rn & 0b11111) << 5 | result;
  return result;
}

uint32_t Aarch64CPP::move_imm16_zero(uint8_t sf, uint8_t hw, uint16_t imm16,
                                     uint8_t rd) {
  uint32_t result = 0b01010010100000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (hw & 0b11) << 21 | result;
  result = (imm16 & 0b1111111111111111) << 5 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::move_imm16_keep(uint8_t sf, uint8_t hw, uint16_t imm16,
                                     uint8_t rd) {
  uint32_t result = 0b01110010100000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (hw & 0b11) << 21 | result;
  result = (imm16 & 0b1111111111111111) << 5 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}
