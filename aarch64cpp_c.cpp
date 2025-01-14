#include <cstdint>
#include <stdexcept>
#include "./aarch64cpp.hpp"

uint32_t Aarch64CPP::compare_and_swap_world_or_double_world(
    uint8_t x, uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt) {
  uint32_t instruction = 0b10001000101000000111110000000000;
  instruction |= (x & 0b1) << 30;
  instruction |= (L & 0b1) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (oO & 0b1) << 15;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::compare_and_swap_byte(uint8_t L, uint8_t rs, uint8_t oO,
                                           uint8_t rn, uint8_t rt) {
  uint32_t instruction = 0b00001000101000000111110000000000;
  instruction |= (L & 0b1) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (oO & 0b1) << 15;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::compare_and_swap_half_world(uint8_t L, uint8_t rs,
                                                 uint8_t oO, uint8_t rn,
                                                 uint8_t rt) {
  uint32_t instruction = 0b01001000101000000111110000000000;
  instruction |= (L & 0b1) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (oO & 0b1) << 15;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::compare_and_swap_pair_of_words(uint8_t sz, uint8_t L,
                                                    uint8_t rs, uint8_t oO,
                                                    uint8_t rn, uint8_t rt) {
  uint32_t instruction = 0b00001000001000000111110000000000;
  instruction |= (sz & 0b1) << 30;
  instruction |= (L & 0b1) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (oO & 0b1) << 15;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::compare_and_branch_on_non_zero(uint8_t sf, uint32_t imm19,
                                                    uint8_t rt) {

  uint32_t instruction = 0b00110101000000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (imm19 & 0b1111111111111111111) << 5;
  instruction |= (rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::compare_and_branch_on_zero(uint8_t sf, uint32_t imm19,
                                                uint8_t rt) {

  uint32_t instruction = 0b00110100000000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (imm19 & 0b1111111111111111111) << 5;
  instruction |= (rt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::conditional_compare_negative_with_immediate(
    uint8_t sf, uint8_t imm5, uint8_t cond, uint8_t rn, uint8_t nzcv) {
  uint32_t instruction = 0b00111010010000000000100000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (imm5 & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (nzcv & 0b1111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::conditional_compare_negative_with_register(
    uint8_t sf, uint8_t rm, uint8_t cond, uint8_t rn, uint8_t nzcv) {

  uint32_t instruction = 0b00111010010000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (nzcv & 0b1111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::conditional_compare_with_immediate(
    uint8_t sf, uint8_t imm5, uint8_t cond, uint8_t rn, uint8_t nzcv) {
  uint32_t instruction = 0b01111010010000000000100000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (imm5 & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (nzcv & 0b1111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::conditional_compare_with_register(uint8_t sf, uint8_t rm,
                                                       uint8_t cond, uint8_t rn,
                                                       uint8_t nzcv) {

  uint32_t instruction = 0b01111010010000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (nzcv & 0b1111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::carry_flag_invert() {
  return 0b11010101000000000100000000011111;
}

uint32_t Aarch64CPP::conditional_increment_returns(uint8_t sf, uint8_t rm,
                                                   uint8_t cond, uint8_t rn,
                                                   uint8_t rd) {
  if (rm == 0b11111 || rn == 0b11111) {
    throw std::runtime_error("rm could not be 0b11111");
  }

  uint32_t instruction = 0b00011010100000000000010000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::conditional_invert_returns(uint8_t sf, uint8_t rm,
                                                uint8_t cond, uint8_t rn,
                                                uint8_t rd) {
  if (rm == 0b11111 || rn == 0b11111) {
    throw std::runtime_error("rm could not be 0b11111");
  }

  uint32_t instruction = 0b01011010100000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::clear_exclusive_clears() {
  return 0b11010101000000110011000001011111;
}

uint32_t Aarch64CPP::count_leading_sign_bits(uint8_t sf, uint8_t rn,
                                             uint8_t rd) {
  uint32_t instruction = 0b01011010110000000001010000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::count_leading_zeros(uint8_t sf, uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b01011010110000000001000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::compare_negative_extended_register_add(
    uint8_t sf, uint8_t rm, uint8_t option, uint8_t imm3, uint8_t rn) {
  uint32_t instruction = 0b00101011001000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (option & 0b111) << 13;
  instruction |= (imm3 & 0b111) << 10;
  instruction |= (rn & 0b11111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::compare_negative_immediate_add(uint8_t sf, uint8_t sh,
                                                    uint8_t imm12, uint8_t rn) {
  uint32_t instruction = 0b00110001000000000000000000011111;
  instruction |= (sf & 0b1) << 31;
  instruction |= (sh & 0b1) << 22;
  instruction |= (imm12 & 0b111111111111) << 10;
  instruction |= (rn & 0b11111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::compare_negative_shifted_register_add(
    uint8_t sf, uint8_t shift, uint8_t rm, uint8_t imm6, uint8_t rn) {

  uint32_t instruction = 0b00101011000000000000000000011111;
  instruction |= (sf & 0b1) << 31;
  instruction |= (shift & 0b11) << 22;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (imm6 & 0b111111) << 10;
  instruction |= (rn & 0b11111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::compare_negative_extended_register_sub(
    uint8_t sf, uint8_t rm, uint8_t option, uint8_t imm3, uint8_t rn) {
  uint32_t instruction = 0b01101011001000000000000000011111;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (option & 0b111) << 13;
  instruction |= (imm3 & 0b111) << 10;
  instruction |= (rn & 0b11111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::compare_negative_immediate_sub(uint8_t sf, uint8_t sh,
                                                    uint8_t imm12, uint8_t rn) {
  uint32_t instruction = 0b01110001000000000000000000011111;
  instruction |= (sf & 0b1) << 31;
  instruction |= (sh & 0b1) << 22;
  instruction |= (imm12 & 0b111111111111) << 10;
  instruction |= (rn & 0b11111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::compare_negative_shifted_register_sub(
    uint8_t sf, uint8_t shift, uint8_t rm, uint8_t imm6, uint8_t rn) {

  uint32_t instruction = 0b01101011000000000000000000011111;
  instruction |= (sf & 0b1) << 31;
  instruction |= (shift & 0b11) << 22;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (imm6 & 0b111111) << 10;
  instruction |= (rn & 0b11111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::compare_with_tag_sub(uint8_t xm, uint8_t xn) {
  uint32_t instruction = 0b10111010110000000000000000011111;
  instruction |= (xm & 0b11111) << 16;
  instruction |= (xn & 0b11111) << 5;
  return instruction;
}

uint32_t Aarch64CPP::conditional_negate_returns(uint8_t sf, uint8_t rm,
                                                uint8_t cond, uint8_t rn,
                                                uint8_t rd) {
  uint32_t instruction = 0b01011010100000000000010000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::cache_prefetch_prediction(uint8_t xt) {
  uint32_t instruction = 0b11010101000010110111001111100000;
  instruction |= (xt & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::memory_copy_forward(uint8_t sz, uint8_t op1, uint8_t rs,
                                         uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b11010101000000000000000000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::memroy_copy_read_and_write_no_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b00011001000000001100010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::memroy_copy_read_no_temporal(uint8_t sz, uint8_t op1,
                                                  uint8_t rs, uint8_t rn,
                                                  uint8_t rd) {

  uint32_t instruction = 0b00011001000000001000010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::memory_copy_read_unprivileged(uint8_t sz, uint8_t op1,
                                                   uint8_t rs, uint8_t rn,
                                                   uint8_t rd) {
  uint32_t instruction = 0b00011001000000000010010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t
Aarch64CPP::memory_copy_read_unprivileged_reads_and_writes_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b00011001000000001110010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::memory_copy_reads_unprivileged_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b00011001000000001010010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::memory_copy_writes_unprivileged(uint8_t sz, uint8_t op1,
                                                     uint8_t rs, uint8_t rn,
                                                     uint8_t rd) {
  uint32_t instruction = 0b00011101000000000001010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t
Aarch64CPP::memory_copy_writes_unprivileged_reads_and_writes_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b00011101000000001101010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::memory_copy_writes_unprivileged_reads_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b00011101000000001001010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::memory_copy_writes_unprivileged_and_non_temporal(
    uint8_t sz, uint8_t op1, uint8_t rs, uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b00011101000000000101010000000000;
  instruction |= (sz & 0b11) << 30;
  instruction |= (op1 & 0b11) << 22;
  instruction |= (rs & 0b11111) << 16;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::crc(uint8_t sf, uint8_t rm, uint8_t c, uint8_t sz,
                         uint8_t rn, uint8_t rd) {
  uint32_t instruction = 0b00011010110000000100000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (c & 0b1) << 12;
  instruction |= (sz & 0b1) << 10;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::consumption_speculative_data_barrier() {
  return 0b11010101000000110010001010011111;
}

uint32_t Aarch64CPP::conditional_select(uint8_t sf, uint8_t rn, uint8_t rm,
                                        uint8_t cond, uint8_t rd) {
  uint32_t instruction = 0b00011010100000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rm & 0b11111) << 0;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::conditional_set_alias(uint8_t sf, uint8_t cond,
                                           uint8_t rd) {
  uint32_t instruction = 0b00011010100111110000011111100000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::conditional_set_mask(uint8_t sf, uint8_t cond,
                                          uint8_t rd) {
  uint32_t instruction = 0b01011010100111110000001111100000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}
uint32_t Aarch64CPP::conditional_select_increment_returns(
    uint8_t sf, uint8_t rn, uint8_t rm, uint8_t cond, uint8_t rd) {
  uint32_t instruction = 0b00011010100000000000010000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::condition_select_invert_returns(uint8_t sf, uint8_t rn,
                                                     uint8_t rm, uint8_t cond,
                                                     uint8_t rd) {
  uint32_t instruction = 0b01011010100000000000000000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}

uint32_t Aarch64CPP::condition_select_negation_returns(uint8_t sf, uint8_t rn,
                                                       uint8_t rm, uint8_t cond,
                                                       uint8_t rd) {
  uint32_t instruction = 0b01011010100000000000010000000000;
  instruction |= (sf & 0b1) << 31;
  instruction |= (rn & 0b11111) << 5;
  instruction |= (rm & 0b11111) << 16;
  instruction |= (cond & 0b1111) << 12;
  instruction |= (rd & 0b11111) << 0;
  return instruction;
}