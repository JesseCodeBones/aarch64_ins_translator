#include <iostream>
#include "./aarch64cpp.hpp"

uint32_t Aarch64CPP::adc(uint8_t sf,  uint8_t rd, uint8_t rn, uint8_t rm) {
        uint32_t result = 0b0011010000000000000000000000000;
        result = (sf & 0b1) << 31 | result;
        result = (rd & 0b11111) << 0 | result;
        result = (rn & 0b11111) << 5 | result;
        result = (rm & 0b11111) << 16 | result;
        return result;
}

uint32_t Aarch64CPP::adcs(uint8_t sf,  uint8_t rd, uint8_t rn, uint8_t rm){
uint32_t result = 0b00111010000000000000000000000000;
        result = (sf & 0b1) << 31 | result;
        result = (rd & 0b11111) << 0 | result;
        result = (rn & 0b11111) << 5 | result;
        result = (rm & 0b11111) << 16 | result;
        return result;
}

uint32_t Aarch64CPP::add_extended_register(uint8_t sf, uint8_t rd, uint8_t rn, uint8_t rm, uint8_t option, uint8_t imm3) {
        uint32_t result = 0b00001011001000000000000000000000;
        result = (sf & 0b1) << 31 | result;
        result = (rd & 0b11111) << 0 | result;
        result = (rn & 0b11111) << 5 | result;
        result = (rm & 0b11111) << 16 | result;
        result = (option & 0b111) << 13 | result;
        result = (imm3 & 0b111) << 10 | result;
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



