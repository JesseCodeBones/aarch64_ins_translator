#ifndef AARCH64CPP_HPP
#define AARCH64CPP_HPP
#include <cstdint>
#include <stdint.h>

class Aarch64CPP {
public:
#include "./aarch64cpp_a.hpp"
#include "./aarch64cpp_b.hpp"
#include "./aarch64cpp_c.hpp"
#include "./aarch64cpp_d.hpp"
#include "./aarch64cpp_e.hpp"
#include "./aarch64cpp_g_to_i.hpp"
#include "./aarch64cpp_l.hpp"
  /**
    Move wide with keep moves an optionally-shifted 16-bit immediate value into
    a register, keeping other bits unchanged.
    @param sf 0 32bit, 1 64bit
    @param hw shift the immediate left, either 0 (the default), 16, 32 or 48,
    encoded in the "hw" field as <shift>/16.
    @param imm16 16bit immediate value
    @param rd Destination register
    https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/MOVZ--Move-wide-with-zero-
     */
  static uint32_t move_imm16_zero(uint8_t sf, uint8_t hw, uint16_t imm16,
                                  uint8_t rd);
  /**
  Move wide with keep moves an optionally-shifted 16-bit immediate value into a
  register, keeping other bits unchanged.
  @param sf 0 32bit, 1 64bit
  @param hw shift the immediate left, either 0 (the default), 16, 32 or 48,
  encoded in the "hw" field as <shift>/16.
  @param imm16 16bit immediate value
  @param rd Destination register
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/MOVK--Move-wide-with-keep-
   */
  static uint32_t move_imm16_keep(uint8_t sf, uint8_t hw, uint16_t imm16,
                                  uint8_t rd);
  static uint32_t mov_wide_immediate(uint8_t hw, uint16_t imm16, uint8_t rd);
  static uint32_t ret_rn(uint8_t rn);
};

#endif // AARCH64CPP_HPP