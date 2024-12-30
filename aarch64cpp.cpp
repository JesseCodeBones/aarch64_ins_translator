#include <iostream>
#include "./aarch64cpp.hpp"

uint32_t Aarch64CPP::adc(uint8_t sf, uint8_t subop, uint8_t setflags, uint8_t d, uint8_t n, uint8_t m){
        uint32_t result = 0b11010000000000000000000000000;
        result = (sf & 0b1) << 31 | result;
        result = (subop & 0b1) << 30 | result;
        result = (setflags & 0b1) << 29 | result;
        result = (d & 0b11111) << 0 | result;
        result = (n & 0b11111) << 5 | result;
        result = (m & 0b11111) << 16 | result;
        return result;
    }