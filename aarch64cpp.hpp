#include <stdint.h>
class Aarch64CPP{
public:

    /**
        @param setFlags 0 32bit, 1 64bit
        @param rd Destination register
        @param rn First operand register
        @param rm Second operand register

        https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADC--Add-with-Carry-

     */
    static uint32_t adc(uint8_t sf,  uint8_t rd, uint8_t rn, uint8_t rm);

    /**
        @param setFlags 0 32bit, 1 64bit
        @param rd Destination register
        @param rn First operand register
        @param rm Second operand register
        differece between adc and adcs is that adcs sets status flags
        https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADCS--Add-with-Carry--setting-flags-
     */
    static uint32_t adcs(uint8_t sf,  uint8_t rd, uint8_t rn, uint8_t rm);
    static uint32_t mov_wide_immediate(uint8_t hw,  uint16_t imm16, uint8_t rd);
    static uint32_t ret_rn(uint8_t rn);
    
};