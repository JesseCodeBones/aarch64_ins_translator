#include "aarch64cpp.hpp"
uint32_t Aarch64CPP::adc(uint8_t sf, uint8_t rd, uint8_t rn, uint8_t rm) {
  uint32_t result = 0b0011010000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  return result;
}

uint32_t Aarch64CPP::adcs(uint8_t sf, uint8_t rd, uint8_t rn, uint8_t rm) {
  uint32_t result = 0b00111010000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  return result;
}

uint32_t Aarch64CPP::add_extended_register(uint8_t sf, uint8_t rd, uint8_t rn,
                                           uint8_t rm, uint8_t option,
                                           uint8_t imm3) {
  uint32_t result = 0b00001011001000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  result = (option & 0b111) << 13 | result;
  result = (imm3 & 0b111) << 10 | result;
  return result;
}

uint32_t Aarch64CPP::add_immediate(uint8_t sf, uint8_t rd, uint8_t rn,
                                   uint16_t imm12, uint8_t shift) {
  uint32_t result = 0b00010001000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (imm12 & 0b111111111111) << 10 | result;
  result = (shift & 0b1) << 22 | result;
  return result;
}

uint32_t Aarch64CPP::add_shift_register(uint8_t sf, uint8_t rd, uint8_t rn,
                                        uint8_t rm, uint8_t shift,
                                        uint8_t imm6) {
  uint32_t result = 0b00001011000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  result = (shift & 0b11) << 22 | result;
  result = (imm6 & 0b111111) << 10 | result;
  return result;
}

uint32_t Aarch64CPP::add_immediate_set_flags(uint8_t sf, uint8_t rd, uint8_t rn,
                                             uint16_t imm12, uint8_t shift) {
  uint32_t result = 0b00110001000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (imm12 & 0b111111111111) << 10 | result;
  result = (shift & 0b1) << 22 | result;
  return result;
}

uint32_t Aarch64CPP::add_shifted_register_set_flags(uint8_t sf, uint8_t rd,
                                                    uint8_t rn, uint8_t rm,
                                                    uint8_t shift,
                                                    uint8_t imm6) {
  uint32_t result = 0b00101011000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  result = (shift & 0b11) << 22 | result;
  result = (imm6 & 0b111111) << 10 | result;
  return result;
}

uint32_t Aarch64CPP::add_pc_and_imm(uint8_t immlo, uint32_t immhi, uint8_t rd) {
  uint32_t result = 0b00010000000000000000000000000000;
  result = (immlo & 0b11) << 29 | result;
  result = (immhi & 0b1111111111111111111) << 5 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::add_pc_and_imm_page(uint8_t immlo, uint32_t immhi,
                                         uint8_t rd) {
  uint32_t result = 0b10010000000000000000000000000000;
  result = (immlo & 0b11) << 29 | result;
  result = (immhi & 0b1111111111111111111) << 5 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::mov_wide_immediate(uint8_t hw, uint16_t imm16,
                                        uint8_t rd) {
  uint32_t result = 0b1010010100000000000000000000000;
  result = (hw & 0b11) << 21 | result;
  result = (imm16 & 0b1111111111111111) << 5 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::add_with_tag(uint8_t rd, uint8_t rn,
                                  uint8_t imm4_tag_offset,
                                  uint8_t imm6_offset) {
  uint32_t result = 0b10010001100000000000000000000000;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (imm4_tag_offset & 0b1111) << 10 | result;
  result = (imm6_offset & 0b111111) << 16 | result;
  return result;
}

uint32_t Aarch64CPP::add_extended_register_set_flags(uint8_t sf, uint8_t rd,
                                                     uint8_t rn, uint8_t rm,
                                                     uint8_t option,
                                                     uint8_t imm3) {
  uint32_t result = 0b00101011001000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  result = (option & 0b111) << 13 | result;
  result = (imm3 & 0b111) << 10 | result;
  return result;
}

uint32_t Aarch64CPP::logic_and_immediate(uint8_t sf, uint8_t rd, uint8_t rn,
                                         uint8_t n, uint8_t immr,
                                         uint8_t imms) {
  uint32_t result = 0b00010010000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (n & 0b1) << 22 | result;
  result = (immr & 0b111111) << 16 | result;
  result = (imms & 0b111111) << 10 | result;
  return result;
}

uint32_t Aarch64CPP::logic_and_shifted_register(uint8_t sf, uint8_t rd,
                                                uint8_t rn, uint8_t rm,
                                                uint8_t shift, uint8_t imm6) {
  uint32_t result = 0b00001010000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  result = (shift & 0b11) << 22 | result;
  result = (imm6 & 0b111111) << 10 | result;
  return result;
}

uint32_t Aarch64CPP::logic_and_immediate_set_flags(uint8_t sf, uint8_t rd,
                                                   uint8_t rn, uint8_t n,
                                                   uint8_t immr, uint8_t imms) {
  uint32_t result = 0b01110010000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (n & 0b1) << 22 | result;
  result = (immr & 0b111111) << 16 | result;
  result = (imms & 0b111111) << 10 | result;
  return result;
}

uint32_t
Aarch64CPP::logic_and_shifted_register_set_flags(uint8_t sf, uint8_t rd,
                                                 uint8_t rn, uint8_t rm,
                                                 uint8_t shift, uint8_t imm6) {
  uint32_t result = 0b01101010000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  result = (shift & 0b11) << 22 | result;
  result = (imm6 & 0b111111) << 10 | result;
  return result;
}

uint32_t Aarch64CPP::arithmetic_shift_right_immediate(uint8_t sf, uint8_t rd,
                                                      uint8_t rn, uint8_t n,
                                                      uint8_t immr, uint8_t x) {
  uint32_t result = 0b00010011000000000111110000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (n & 0b1) << 22 | result;
  result = (immr & 0b111111) << 16 | result;
  result = (x & 0b1) << 15 | result;
  return result;
}

uint32_t Aarch64CPP::arithmetic_shift_right_register(uint8_t sf, uint8_t rd,
                                                     uint8_t rn, uint8_t rm) {
  uint32_t result = 0b00011010110000000010100000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  return result;
}

uint32_t Aarch64CPP::arithmetic_shift_right_variable(uint8_t sf, uint8_t rd,
                                                     uint8_t rn, uint8_t rm) {
  uint32_t result = 0b00011010110000000010100000000000;
  result = (sf & 0b1) << 31 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  return result;
}

uint32_t Aarch64CPP::address_translate(uint8_t op1, uint8_t x, uint8_t op2,
                                       uint8_t rt) {
  uint32_t result = 0b11010101000010000111100000000000;
  result = (op1 & 0b111) << 16 | result;
  result = (x & 0b1) << 8 | result;
  result = (op2 & 0b111) << 5 | result;
  result = (rt & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::authenticate_data_address_A(uint8_t z, uint8_t rd,
                                                 uint8_t rn) {
  uint32_t result = 0b11011010110000010001100000000000;
  result = (z & 0b1) << 13 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  return result;
}

uint32_t Aarch64CPP::authenticate_data_address_B(uint8_t z, uint8_t rd,
                                                 uint8_t rn) {
  uint32_t result = 0b11011010110000010001110000000000;
  result = (z & 0b1) << 13 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  return result;
}

uint32_t Aarch64CPP::authenticate_instruction_address_A(uint8_t z, uint8_t rd,
                                                        uint8_t rn) {
  uint32_t result = 0b11011010110000010001000000000000;
  result = (z & 0b1) << 13 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  return result;
}

uint32_t Aarch64CPP::authenticate_instruction_address_B(uint8_t z, uint8_t rd,
                                                        uint8_t rn) {
  uint32_t result = 0b11011010110000010001010000000000;
  result = (z & 0b1) << 13 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  return result;
}
uint32_t Aarch64CPP::ax_flag() {
  return 0b11010101000000000100000001011111;
}