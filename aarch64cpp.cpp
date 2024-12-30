#include <iostream>
#include "./aarch64cpp.hpp"

uint32_t Aarch64CPP::adc(uint8_t sf,  uint8_t d, uint8_t n, uint8_t m) {
        uint32_t result = 0b0011010000000000000000000000000;
        result = (sf & 0b1) << 31 | result;
        result = (d & 0b11111) << 0 | result;
        result = (n & 0b11111) << 5 | result;
        result = (m & 0b11111) << 16 | result;
        return result;
}
uint32_t Aarch64CPP::mov_wide_immediate(uint8_t hw,  uint16_t imm16, uint8_t rd) {
        uint32_t result = 0b1010010100000000000000000000000;
        result = (hw & 0b11) << 21 | result;
        result = (imm16 & 0b1111111111111111) << 5 | result;
        result = (rd & 0b11111) << 0 | result;
        return result;
}
uint32_t Aarch64CPP::ret_rn(uint8_t rn) {
       uint32_t result = 0xd65f0000;
       result = (rn & 0b11111) << 5 | result;
       return result;
}