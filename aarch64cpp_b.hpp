#ifndef AARCH64CPP_B_HPP
#define AARCH64CPP_B_HPP
#include <cstdint>
#include <stdint.h>

/**
  Branch causes an unconditional branch to a label at a PC-relative offset,
  with a hint that this is not a subroutine call or return. to the value in
  the program counter.
  @param imm26 26bit immediate value,
  bits(64) offset = SignExtend(imm26:'00', 64);
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/B--Branch-
 */
static uint32_t branch_immediate(uint32_t imm26);

/**
  Branch conditionally to a label at a PC-relative offset, with a hint that this
  is not a subroutine call or return.
  @param imm19 19bit immediate value,
  bits(64) offset = SignExtend(imm19:'00', 64);
  @param cond 4bit condition code.
  boolean ConditionHolds(bits(4) cond)
    // Evaluate base condition.
    boolean result;
    case cond<3:1> of
        when '000' result = (PSTATE.Z == '1');                          // EQ or
  NE when '001' result = (PSTATE.C == '1');                          // CS or CC
        when '010' result = (PSTATE.N == '1');                          // MI or
  PL when '011' result = (PSTATE.V == '1');                          // VS or VC
        when '100' result = (PSTATE.C == '1' && PSTATE.Z == '0');       // HI or
  LS when '101' result = (PSTATE.N == PSTATE.V);                     // GE or LT
        when '110' result = (PSTATE.N == PSTATE.V && PSTATE.Z == '0');  // GT or
  LE when '111' result = TRUE;                                       // AL

    // Condition flag values in the set '111x' indicate always true
    // Otherwise, invert condition if necessary.
    if cond<0> == '1' && cond != '1111' then
        result = !result;

    return result;
    https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/B-cond--Branch-conditionally-
 */
static uint32_t branch_immediate_conditional(uint32_t imm19, uint32_t cond);

/**
  Branch Consistent conditionally to a label at a PC-relative offset, with a
  hint that this branch will behave very consistently and is very unlikely to
  change direction.
  @param imm19 19bit immediate value,
  bits(64) offset = SignExtend(imm19:'00', 64);
  @param cond 4bit condition code.
  在多处理器环境中，确保一致性的分支操作是为了保证多个处理器对共享资源的访问和操作的一致性。这对于避免竞争条件和数据不一致非常重要。以下是一个简单的例子来说明这一点：
  Branch Consistent conditionally 的作用：
  在实现锁机制时，可以使用条件分支来检查锁的状态。
  需要确保这个检查和锁的获取是原子的，并且在所有处理器间一致。
  例如，使用原子操作或内存屏障来确保一致性。
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/B-cond--Branch-conditionally-

 */
static uint32_t branch_immediate_consistent_conditional(uint32_t imm19,
                                                        uint32_t cond);

/**
  Bitfield Clear sets a bitfield of <width> bits at bit position <lsb> of the
  destination register to zero, leaving the other destination bits unchanged.
  @param sf 0 32bit, 1 64bit
  BFC (Bitfield Clear)
  指令用于将目标寄存器中从指定位置开始的若干位清零，而不改变其他位的值。
  例如，假设我们有一个32位的寄存器 R0，其初始值为
  0xFFFFFFFF（即所有位都是1）。我们希望将从第8位（lsb = 8）开始的4个位（width =
  4）清零。使用 BFC 指令后，寄存器 R0 的值将变为 0xFFFFF0FF。 具体步骤如下：
  初始值：R0 = 0xFFFFFFFF
  清零从第8位开始的4个位：R0 = 0xFFFFF0FF
  https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/BFC--Bitfield-Clear--an-alias-of-BFM-
 */
static uint32_t bitfield_clear(uint8_t sf, uint8_t N, uint8_t immr,
                               uint8_t imms, uint8_t rd);

/**
    Bitfield Insert inserts a bitfield of <width> bits from a second register
   into a second register, at bit position <lsb> of the destination register,
   leaving the other destination bits unchanged.
    @param sf 0 32bit, 1 64bit
    @param N
    @param immr
    @param imms 这三个参数定义了imm
    @param rd 目标寄存器
    BFI (Bitfield Insert)
   指令用于将第二个寄存器中的一个位域插入到第一个寄存器中的指定位置，而不改变其他位的值。
    例如，假设我们有两个32位的寄存器 R0 和 R1，其初始值分别为 0xFFFFFFFF 和
   0x0000000F。我们希望将 R1 中的低4位（width = 4）插入到 R0 的第8位（lsb =
   8）开始的4个位中。使用 BFI 指令后，寄存器 R0 的值将变为 0xFFFFF0FF。
    具体步骤如下：
    初始值：R0 = 0xFFFFFFFF，R1 = 0x0000000F
    将 R1 中的低4位插入到 R0 的第8位开始的4个位中：R0 = 0xFFFFF0FF
    https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/BFI--Bitfield-Insert--an-alias-of-BFM-
 */
static uint32_t bitfield_insert(uint8_t sf, uint8_t N, uint8_t immr,
                                uint8_t imms, uint8_t rd, uint8_t rn);

/**
    BFM
Bitfield Move is usually accessed via one of its aliases, which are always
preferred for disassembly.

If <imms> is greater than or equal to <immr>, this copies a bitfield of
(<imms>-<immr>+1) bits starting from bit position <immr> in the source register
to the least significant bits of the destination register.

If <imms> is less than <immr>, this copies a bitfield of (<imms>+1) bits from
the least significant bits of the source register to bit position
(regsize-<immr>) of the destination register, where regsize is the destination
register size of 32 or 64 bits.

In both cases the other bits of the destination register remain unchanged.

https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/BFM--Bitfield-Move-
 */
static uint32_t bitfield_move(uint8_t sf, uint8_t N, uint8_t immr, uint8_t imms,
                              uint8_t rd, uint8_t rn);

/**
BFXIL
Bitfield Extract and Insert Low copies a bitfield of <width> bits starting from
bit position <lsb> in the source register to the least significant bits of the
destination register, leaving the other destination bits unchanged.

https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/BFXIL--Bitfield-extract-and-insert-at-low-end--an-alias-of-BFM-
 */

static uint32_t bitfield_extract_insert_low(uint8_t sf, uint8_t N, uint8_t immr,
                                            uint8_t imms, uint8_t rd,
                                            uint8_t rn);

/**

BIC BICS(opc == '11')

Bitwise Bit Clear (shifted register) performs a bitwise AND of a register value
and the complement of an optionally-shifted register value, and writes the
result to the destination register. integer d = UInt(Rd); integer n = UInt(Rn);
    integer m = UInt(Rm);
    integer datasize = if sf == '1' then 64 else 32;
    boolean setflags;
    LogicalOp op;
    case opc of
        when '00' op = LogicalOp_AND; setflags = FALSE;
        when '01' op = LogicalOp_ORR; setflags = FALSE;
        when '10' op = LogicalOp_EOR; setflags = FALSE;
        when '11' op = LogicalOp_AND; setflags = TRUE;

    if sf == '0' && imm6<5> == '1' then UNDEFINED;

    ShiftType shift_type = DecodeShift(shift);
    integer shift_amount = UInt(imm6);
    boolean invert = (N == '1');


    移动操作
    ShiftType DecodeShift(bits(2) op)
    case op of
        when '00'  return ShiftType_LSL;
        when '01'  return ShiftType_LSR;
        when '10'  return ShiftType_ASR;
        when '11'  return ShiftType_ROR;
 */
static uint32_t bitwise_bit_clear(uint8_t sf, uint8_t opc, uint8_t shift,
                                  uint8_t rd, uint8_t rn, uint8_t rm,
                                  uint8_t imm6);
#endif