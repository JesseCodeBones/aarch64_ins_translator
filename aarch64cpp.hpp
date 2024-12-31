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

    /**
        @param setFlags 0 32bit, 1 64bit
        @param rd Destination register
        @param rn First operand register
        @param rm Second operand register
        @param option 0b000  UXTB, 0b001 UXTH, 0b010 UXTW, 0b011 UXTX, 0b100 SXTB, 0b101 SXTH, 0b110 SXTW, 0b111 SXTX
        @param imm3 0-7, amount to left shift
        add extended register instruction
        https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADD--extended-register---Add--extended-register--
     */
    static uint32_t add_extended_register(uint8_t sf, uint8_t rd, uint8_t rn, uint8_t rm, uint8_t option, uint8_t imm3);

    static uint32_t mov_wide_immediate(uint8_t hw,  uint16_t imm16, uint8_t rd);
    static uint32_t ret_rn(uint8_t rn);
    
};