#include "./aarch64cpp.hpp"
#include <stdexcept>

uint32_t Aarch64CPP::compare_and_swap_world_or_double_world(uint8_t x, uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt){
    uint32_t instruction = 0b10001000101000000111110000000000;
    instruction |= (x & 0b1) << 30;
    instruction |= (L & 0b1) << 22;
    instruction |= (rs & 0b11111) << 16;
    instruction |= (oO & 0b1) << 15;
    instruction |= (rn & 0b11111) << 5;
    instruction |= (rt & 0b11111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::compare_and_swap_byte(uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt){
    uint32_t instruction = 0b00001000101000000111110000000000;
    instruction |= (L & 0b1) << 22;
    instruction |= (rs & 0b11111) << 16;
    instruction |= (oO & 0b1) << 15;
    instruction |= (rn & 0b11111) << 5;
    instruction |= (rt & 0b11111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::compare_and_swap_half_world(uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt){
    uint32_t instruction = 0b01001000101000000111110000000000;
    instruction |= (L & 0b1) << 22;
    instruction |= (rs & 0b11111) << 16;
    instruction |= (oO & 0b1) << 15;
    instruction |= (rn & 0b11111) << 5;
    instruction |= (rt & 0b11111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::compare_and_swap_pair_of_words(uint8_t sz, uint8_t L, uint8_t rs, uint8_t oO, uint8_t rn, uint8_t rt) {
    uint32_t instruction = 0b00001000001000000111110000000000;
    instruction |= (sz & 0b1) << 30;
    instruction |= (L & 0b1) << 22;
    instruction |= (rs & 0b11111) << 16;
    instruction |= (oO & 0b1) << 15;
    instruction |= (rn & 0b11111) << 5;
    instruction |= (rt & 0b11111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::compare_and_branch_on_non_zero(uint8_t sf, uint32_t imm19, uint8_t rt){

    uint32_t instruction = 0b00110101000000000000000000000000;
    instruction |= (sf & 0b1) << 31;
    instruction |= (imm19 & 0b1111111111111111111) << 5;
    instruction |= (rt & 0b11111) << 0;
    return instruction;
}


uint32_t Aarch64CPP::compare_and_branch_on_zero(uint8_t sf, uint32_t imm19, uint8_t rt){

    uint32_t instruction = 0b00110100000000000000000000000000;
    instruction |= (sf & 0b1) << 31;
    instruction |= (imm19 & 0b1111111111111111111) << 5;
    instruction |= (rt & 0b11111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::conditional_compare_negative_with_immediate(uint8_t sf, uint8_t imm5, uint8_t cond, uint8_t rn, uint8_t nzcv){
    uint32_t instruction = 0b00111010010000000000100000000000;
    instruction |= (sf & 0b1) << 31;
    instruction |= (imm5 & 0b11111) << 16;
    instruction |= (cond & 0b1111) << 12;
    instruction |= (rn & 0b11111) << 5;
    instruction |= (nzcv & 0b1111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::conditional_compare_negative_with_register(uint8_t sf, uint8_t rm, uint8_t cond, uint8_t rn, uint8_t nzcv) {

    uint32_t instruction = 0b00111010010000000000000000000000;
    instruction |= (sf & 0b1) << 31;
    instruction |= (rm & 0b11111) << 16;
    instruction |= (cond & 0b1111) << 12;
    instruction |= (rn & 0b11111) << 5;
    instruction |= (nzcv & 0b1111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::conditional_compare_with_immediate(uint8_t sf, uint8_t imm5, uint8_t cond, uint8_t rn, uint8_t nzcv){
    uint32_t instruction = 0b01111010010000000000100000000000;
    instruction |= (sf & 0b1) << 31;
    instruction |= (imm5 & 0b11111) << 16;
    instruction |= (cond & 0b1111) << 12;
    instruction |= (rn & 0b11111) << 5;
    instruction |= (nzcv & 0b1111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::conditional_compare_with_register(uint8_t sf, uint8_t rm, uint8_t cond, uint8_t rn, uint8_t nzcv) {

    uint32_t instruction = 0b01111010010000000000000000000000;
    instruction |= (sf & 0b1) << 31;
    instruction |= (rm & 0b11111) << 16;
    instruction |= (cond & 0b1111) << 12;
    instruction |= (rn & 0b11111) << 5;
    instruction |= (nzcv & 0b1111) << 0;
    return instruction;
}

uint32_t Aarch64CPP::carry_flag_invert(){
    return 0b11010101000000000100000000011111;
}

uint32_t Aarch64CPP::conditional_increment_returns(uint8_t sf, uint8_t rm, uint8_t cond, uint8_t rn, uint8_t rd){
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

uint32_t Aarch64CPP::conditional_invert_returns(uint8_t sf, uint8_t rm, uint8_t cond, uint8_t rn, uint8_t rd){
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