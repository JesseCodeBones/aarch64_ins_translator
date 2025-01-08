#include <cstdint>
#include <stdint.h>
class Aarch64CPP {
public:
  /**
      @param setFlags 0 32bit, 1 64bit
      @param rd Destination register
      @param rn First operand register
      @param rm Second operand register

      https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADC--Add-with-Carry-

   */
  static uint32_t adc(uint8_t sf, uint8_t rd, uint8_t rn, uint8_t rm);

  /**
      @param setFlags 0 32bit, 1 64bit
      @param rd Destination register
      @param rn First operand register
      @param rm Second operand register
      differece between adc and adcs is that adcs sets status flags
      https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADCS--Add-with-Carry--setting-flags-
   */
  static uint32_t adcs(uint8_t sf, uint8_t rd, uint8_t rn, uint8_t rm);

  /**
      @param setFlags 0 32bit, 1 64bit
      @param rd Destination register
      @param rn First operand register
      @param rm Second operand register
      @param option 0b000  UXTB, 0b001 UXTH, 0b010 UXTW, 0b011 UXTX, 0b100 SXTB,
     0b101 SXTH, 0b110 SXTW, 0b111 SXTX
      @param imm3 0-7, amount to left shift on rm
      add extended register instruction
      https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADD--extended-register---Add--extended-register--
   */
  static uint32_t add_extended_register(uint8_t sf, uint8_t rd, uint8_t rn,
                                        uint8_t rm, uint8_t option,
                                        uint8_t imm3);

  /**
      @param sf 0 32bit, 1 64bit
      @param imm16 16bit immediate value
      @param rd Destination register
      @param rn First operand register
      @param shift 0 0, 1 12
      https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/MOVN--Move-Wide-Immediate--ARM-
      case sh of
      when '0' imm = ZeroExtend(imm12, datasize);
      when '1' imm = ZeroExtend(imm12 : Zeros(12), datasize);
   */
  static uint32_t add_immediate(uint8_t sf, uint8_t rd, uint8_t rn,
                                uint16_t imm12, uint8_t shift);

  /**
      @param sf 0 32bit, 1 64bit
      @param rd Destination register
      @param rn First operand register
      @param rm Second operand register (shift this register value)
      @param shift    00	LSL         Logical shift left
                      01	LSR         Logical shift right
                      10	ASR         Arithmetic shift right
                      11	RESERVED    not working!!
      @param imm6 6bit immediate value
      https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADD--shifted-register---Add--shifted-register--
   */
  static uint32_t add_shift_register(uint8_t sf, uint8_t rd, uint8_t rn,
                                     uint8_t rm, uint8_t shift, uint8_t imm6);

  /**
      @param rd Destination register
      @param rn First operand register
      @param imm4_tag_offset 4bit immediate value
      @param imm6_offset 6bit immediate value
      https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADDG--Add-with-Tag-
   */
  static uint32_t add_with_tag(uint8_t rd, uint8_t rn, uint8_t imm4_tag_offset,
                               uint8_t imm6_offset);

  /**
      @param sf 0 32bit, 1 64bit
      @param rd Destination register
      @param rn First operand register
      @param rm Second operand register
      @param option 0b000  UXTB, 0b001 UXTH, 0b010 UXTW, 0b011 UXTX, 0b100 SXTB,
     0b101 SXTH, 0b110 SXTW, 0b111 SXTX
      @param imm3 0-7, amount to left shift on rm
      add extended register instruction
      https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADDS--extended-register---Add--extended-register---setting-flags-
   */
  static uint32_t add_extended_register_set_flags(uint8_t sf, uint8_t rd,
                                                  uint8_t rn, uint8_t rm,
                                                  uint8_t option, uint8_t imm3);

  /**
      @param sf 0 32bit, 1 64bit
      @param rd Destination register
      @param rn First operand register
      @param imm12 12bit immediate value
      @param shift 0 0, 1 12
      https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADDS--immediate---Add--immediate---setting-flags-
   */
  static uint32_t add_immediate_set_flags(uint8_t sf, uint8_t rd, uint8_t rn,
                                          uint16_t imm12, uint8_t shift);

  /**
  @param sf 0 32bit, 1 64bit
  @param rd Destination register
  @param rn First operand register
  @param rm Second operand register (shift this register value)
  @param shift    00	LSL         Logical shift left
                  01	LSR         Logical shift right
                  10	ASR         Arithmetic shift right
                  11	RESERVED    not working!!
  @param imm6 6bit immediate value
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADDS--shifted-register---Add--shifted-register---setting-flags-
   */
  static uint32_t add_shifted_register_set_flags(uint8_t sf, uint8_t rd,
                                                 uint8_t rn, uint8_t rm,
                                                 uint8_t shift, uint8_t imm6);

  /**
    get pc address and add immediate value to destination register
    @param immlo 2bit immediate value
    @param immhi 19bit immediate value
    @param rd Destination register
    https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADRP--Add-PC-relative-
   */
  static uint32_t add_pc_and_imm(uint8_t immlo, uint32_t immhi, uint8_t rd);

  /**
    if page then
        imm = SignExtend(immhi:immlo:Zeros(12), 64);  LSL 12 bit
    else
        imm = SignExtend(immhi:immlo, 64);
    @param immlo 2bit immediate value
    @param immhi 19bit immediate value
    @param rd Destination register
   https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ADRP--Form-PC-relative-address-to-4KB-page-
   */
  static uint32_t add_pc_and_imm_page(uint8_t immlo, uint32_t immhi,
                                      uint8_t rd);

  /**
  Bitwise AND (immediate) performs a bitwise AND of a register value and an
  immediate value, and writes the result to the destination register.
    @param sf 0 32bit, 1 64bit
    @param rd Destination register
    @param rn First operand register
    @param n 0 32bit, 1 64bit
    @param immr 6bit immediate value
    @param imms 6bit immediate value
   */
  static uint32_t logic_and_immediate(uint8_t sf, uint8_t rd, uint8_t rn,
                                      uint8_t n, uint8_t immr, uint8_t imms);

  /**
  Bitwise AND (shifted register) performs a bitwise AND of a register value and
  a value shifted left by an immediate value, and writes the result to the
  destination register.
  @param sf 0 32bit, 1 64bit
  @param rd Destination register
  @param rn First operand register
  @param rm Second operand register
  @param shift    00	LSL         Logical shift left
                01	LSR         Logical shift right
                10	ASR         Arithmetic shift right
                11	RESERVED    not working!!
  @param imm6 6bit immediate value
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/AND--shifted-register---Bitwise-AND--shifted-register--
  */
  static uint32_t logic_and_shifted_register(uint8_t sf, uint8_t rd, uint8_t rn,
                                             uint8_t rm, uint8_t shift,
                                             uint8_t imm6);

  /**
  Bitwise AND (immediate), setting flags, performs a bitwise AND of a register
  value and an immediate value, and writes the result to the destination
  register. It updates the condition flags based on the result.
  @param sf 0 32bit, 1 64bit
  @param rd Destination register
  @param rn First operand register
  @param n 0 32bit, 1 64bit
  @param immr 6bit immediate value
  @param imms 6bit immediate value
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ANDS--immediate---Bitwise-AND--immediate---setting-flags-
   */
  static uint32_t logic_and_immediate_set_flags(uint8_t sf, uint8_t rd,
                                                uint8_t rn, uint8_t n,
                                                uint8_t immr, uint8_t imms);

  /**
  Bitwise AND (shifted register), setting flags, performs a bitwise AND of a
  register value and an optionally-shifted register value, and writes the result
  to the destination register. It updates the condition flags based on the
  result.
  @param sf 0 32bit, 1 64bit
  @param rd Destination register
  @param rn First operand register
  @param rm Second operand register
  @param shift    00	LSL         Logical shift left
                01	LSR         Logical shift right
                10	ASR         Arithmetic shift right
                11	RESERVED    not working!!
  @param imm6 6bit immediate value
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ANDS--shifted-register---Bitwise-AND--shifted-register---setting-flags-
   */
  static uint32_t logic_and_shifted_register_set_flags(uint8_t sf, uint8_t rd,
                                                       uint8_t rn, uint8_t rm,
                                                       uint8_t shift,
                                                       uint8_t imm6);

  /**
  Bitwise AND (shifted register), setting flags, performs a bitwise AND of a
  register value and a value shifted left by an immediate value, and writes the
  result to the destination register. It updates the condition flags based on
  the result.
  @param sf 0 32bit, 1 64bit
  @param rd Destination register
  @param rn First operand register
  @param n 0 32bit, 1 64bit
  @param immr 6bit immediate value
  @param x 0 32bit, 1 64bit
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ASR--immediate---Arithmetic-Shift-Right--immediate---an-alias-of-SBFM-
   */
  static uint32_t arithmetic_shift_right_immediate(uint8_t sf, uint8_t rd,
                                                   uint8_t rn, uint8_t n,
                                                   uint8_t immr, uint8_t x);
  /**
  Arithmetic Shift Right (register) shifts a register value right by a variable
  number of bits, shifting in copies of its sign bit, and writes the result to
  the destination register. The remainder obtained by dividing the second source
  register by the data size defines the number of bits by which the first source
  register is right-shifted.
  @param sf 0 32bit, 1 64bit
  @param rd Destination register
  @param rn First operand register
  @param rm Second operand register
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ASR--register---Arithmetic-Shift-Right--register---an-alias-of-ASRV-
   */
  static uint32_t arithmetic_shift_right_register(uint8_t sf, uint8_t rd,
                                                  uint8_t rn, uint8_t rm);
  /**
  Arithmetic Shift Right Variable shifts a register value right by a variable
  number of bits, shifting in copies of its sign bit, and writes the result to
  the destination register. The remainder obtained by dividing the second source
  register by the data size defines the number of bits by which the first source
  register is right-shifted.

  @param sf 0 32bit, 1 64bit
  @param rd Destination register
  @param rn First operand register
  @param rm Second operand register
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/ASRV--Arithmetic-Shift-Right-Variable-

   */
  static uint32_t arithmetic_shift_right_variable(uint8_t sf, uint8_t rd,
                                                  uint8_t rn, uint8_t rm);
  static uint32_t mov_wide_immediate(uint8_t hw, uint16_t imm16, uint8_t rd);
  static uint32_t ret_rn(uint8_t rn);
};