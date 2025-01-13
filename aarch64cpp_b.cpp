#include <cstdint>
#include <stdexcept>
#include "./aarch64cpp.hpp"
uint32_t Aarch64CPP::branch_immediate(uint32_t imm26) {
  uint32_t result = 0b000101 << 26;
  result = (imm26 & 0b11111111111111111111111111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::branch_immediate_conditional(uint32_t imm19,
                                                  uint32_t cond) {
  uint32_t result = 0b010101 << 26;
  result = (imm19 & 0b1111111111111111111) << 5 | result;
  result = (cond & 0b1111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::branch_immediate_consistent_conditional(uint32_t imm19,
                                                             uint32_t cond) {
  uint32_t result = 0b01010100000000000000000000010000;
  result = (imm19 & 0b1111111111111111111) << 5 | result;
  result = (cond & 0b1111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::bitfield_clear(uint8_t sf, uint8_t N, uint8_t immr,
                                    uint8_t imms, uint8_t rd) {
  uint32_t result = 0b00110011000000000000001111100000;
  result = (sf & 0b1) << 31 | result;
  result = (N & 0b1) << 22 | result;
  result = (immr & 0b111111) << 16 | result;
  result = (imms & 0b111111) << 10 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::bitfield_insert(uint8_t sf, uint8_t N, uint8_t immr,
                                     uint8_t imms, uint8_t rd, uint8_t rn) {
  uint32_t result = 0b00110011000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (N & 0b1) << 22 | result;
  result = (immr & 0b111111) << 16 | result;
  result = (imms & 0b111111) << 10 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::bitfield_move(uint8_t sf, uint8_t N, uint8_t immr,
                                   uint8_t imms, uint8_t rd, uint8_t rn) {
  uint32_t result = 0b00110011000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (N & 0b1) << 22 | result;
  result = (immr & 0b111111) << 16 | result;
  result = (imms & 0b111111) << 10 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::bitfield_extract_insert_low(uint8_t sf, uint8_t N,
                                                 uint8_t immr, uint8_t imms,
                                                 uint8_t rd, uint8_t rn) {
  uint32_t result = 0b00110011000000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (N & 0b1) << 22 | result;
  result = (immr & 0b111111) << 16 | result;
  result = (imms & 0b111111) << 10 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rd & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::bitwise_bit_clear(uint8_t sf, uint8_t opc, uint8_t shift,
                                       uint8_t rd, uint8_t rn, uint8_t rm,
                                       uint8_t imm6) {
  uint32_t result = 0b00001010001000000000000000000000;
  result = (sf & 0b1) << 31 | result;
  result = (opc & 0b11) << 29 | result;
  result = (shift & 0b11) << 22 | result;
  result = (rd & 0b11111) << 0 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 16 | result;
  result = (imm6 & 0b111111) << 10 | result;
  return result;
}

uint32_t Aarch64CPP::branch_with_link_immediate(uint32_t imm26) {
  uint32_t result = 0b100101 << 26;
  result = (imm26 & 0b11111111111111111111111111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::branch_with_link_register(uint8_t rn) {
  uint32_t result = 0b11010110001111110000000000000000;
  result = (rn & 0b11111) << 5 | result;
  return result;
}

uint32_t Aarch64CPP::branch_with_link_register_pointer_authentication(uint8_t Z, uint8_t M, uint8_t rn, uint8_t rm) {


  bool legal = (Z == 0 && M == 0 && rm == 0b11111) || (Z == 1 && M == 0) || (Z == 0 && M == 1 && rm == 0b11111) || (Z == 1 && M == 1);
  if(!legal) {
    throw std::runtime_error("Illegal arguments");
  }

  uint32_t result = 0b11010110001111110000100000000000;
  result = (Z & 0b1) << 24 | result;
  result = (M & 0b1) << 10 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::branch_register(uint8_t rn){
  uint32_t result = 0b11010110000111110000000000000000;
  result = (rn & 0b11111) << 5 | result;
  return result;
}

uint32_t Aarch64CPP::branch_register_pointer_authentication(uint8_t Z, uint8_t M, uint8_t rn, uint8_t rm){
  bool legal = (Z == 0 && M == 0 && rm == 0b11111) || (Z == 1 && M == 0) || (Z == 0 && M == 1 && rm == 0b11111) || (Z == 1 && M == 1);
  if(!legal) {
    throw std::runtime_error("Illegal arguments");
  }
  uint32_t result = 0b11010110000111110000100000000000;
  result = (Z & 0b1) << 24 | result;
  result = (M & 0b1) << 10 | result;
  result = (rn & 0b11111) << 5 | result;
  result = (rm & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::branch_record_buffer(uint8_t op2, uint8_t rt){
  uint32_t result = 0b11010101000010010111001000000000;
  result = (op2 & 0b111) << 5 | result;
  result = (rt & 0b11111) << 0 | result;
  return result;
}

uint32_t Aarch64CPP::break_point(uint16_t imm16){
  uint32_t result = 0b11010100001000000000000000000000;
  result = (imm16 & 0b1111111111111111) << 5 | result;
  return result;
}

uint32_t Aarch64CPP::branch_target_identifier(uint8_t op2){
  uint32_t result = 0b11010101000000110010010000011111;
  result = (op2 & 0b11) << 6 | result;
  return result;
}