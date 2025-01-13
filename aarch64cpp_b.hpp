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

/**
BL
Branch with Link branches to a PC-relative offset, setting the register X30 to PC+4. It provides a hint that this is a subroutine call.
bits(64) offset = SignExtend(imm26:'00', 64);
https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/BL--Branch-with-Link-
 */
static uint32_t branch_with_link_immediate(uint32_t imm26);
/**
BLR
Branch with Link to Register calls a subroutine at an address in a register, setting register X30 to PC+4.
https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/BLR--Branch-with-Link-to-Register-
 */
static uint32_t branch_with_link_register(uint8_t rn);

/**
Branch with Link to Register, with pointer authentication
  @param Z 0: zero modifier, 1: register modifier

  Key A, zero modifier (Z == 0 && M == 0 && Rm == 11111)
  Key A, register modifier (Z == 1 && M == 0)
  Key B, zero modifier (Z == 0 && M == 1 && Rm == 11111)
  Key B, register modifier (Z == 1 && M == 1)

  具体解释
  BLRAA X1, X0:

  跳转到 X0 指定的地址（例如 0x4000）。
  将返回地址（当前 PC + 4）存储在 X1 中。
  使用 PACIA 进行认证，确保返回地址的完整性。
  BLRAAZ X1, X0:

  跳转到 X0 指定的地址（例如 0x4000）。
  将返回地址（当前 PC + 4）存储在 X1 中。
  使用 PACIA 进行认证，并将认证码置零。
  BLRAB X1, X0:

  跳转到 X0 指定的地址（例如 0x4000）。
  将返回地址（当前 PC + 4）存储在 X1 中。
  使用 PACIB 进行认证，确保返回地址的完整性。
  BLRABZ X1, X0:

  跳转到 X0 指定的地址（例如 0x4000）。
  将返回地址（当前 PC + 4）存储在 X1 中。
  使用 PACIB 进行认证，并将认证码置零。
 */

static uint32_t branch_with_link_register_pointer_authentication(uint8_t Z, uint8_t M, uint8_t rn, uint8_t rm);


/**
BR
Branch to Register branches unconditionally to an address in a register, with a hint that this is not a subroutine return.

https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/BR--Branch-to-Register-
 */
static uint32_t branch_register(uint8_t rn);

/**
Branch to Register, with pointer authentication. 
Branch to Register, with pointer authentication. This instruction authenticates the address in the general-purpose register that is specified by <Xn>, using a modifier and the specified key, and branches to the authenticated address.
https://developer.arm.com/documentation/ddi0602/2022-06/Base-Instructions/BRAA--BRAAZ--BRAB--BRABZ--Branch-to-Register--with-pointer-authentication-
 */
static uint32_t branch_register_pointer_authentication(uint8_t Z, uint8_t M, uint8_t rn, uint8_t rm);

/**
BRB

This instruction need el1 or higher privilege level.

Branch Record Buffer. For more information, see op0==0b01, cache maintenance, TLB maintenance, and address translation instructions.

This is an alias of SYS. This means:

The encodings in this description are named to match the encodings of SYS.
The description of SYS gives the operational pseudocode for this instruction.

 */
static uint32_t branch_record_buffer(uint8_t op2, uint8_t rt);


/**
BRK

ESR_ELx 寄存器包含多个字段，其中包括异常类别（EC, Exception Class）和异常特定的状态（ISS, Instruction Specific Syndrome）

Breakpoint instruction. A BRK instruction generates a Breakpoint Instruction exception. 
The PE records the exception in ESR_ELx, using the EC value 0x3c, 
and captures the value of the immediate argument in ESR_ELx.ISS.
 */
static uint32_t break_point(uint16_t imm16);


/**
BTI

它通过在代码中插入 BTI 指令来标记合法的分支目标，从而防止攻击者利用分支目标注入漏洞。

BTI 指令的作用
防止未预期的分支目标：BTI 指令用于标记合法的分支目标，防止执行未预期的指令。
兼容性检查：在受保护的内存区域内，当 PSTATE.BTYPE 不等于 0b00 时，BTI 指令会检查当前的 PSTATE.BTYPE 值是否与 BTI 指令的操作数兼容。如果兼容，则允许执行后续指令，否则会生成分支目标异常。
NOP 行为：在未受保护的内存区域内，BTI 指令执行时相当于一个 NOP（No Operation）指令，不会产生任何效果。
PSTATE.BTYPE 是程序状态寄存器（PSTATE）中的一个字段，用于指示当前的分支类型。它的值可以是以下之一：

0b00：无分支类型检查。
0b01：直接分支。
0b10：间接分支。
0b11：保留。
.global _start

_start:
    // 标记合法的分支目标
    BTI c

    // 其他代码逻辑...

    // 退出程序
    MOV X8, #93          // syscall number for exit
    MOV X0, #0           // exit code
    SVC #0               // make syscall

    	
Is the type of indirection, encoded in op2<2:1>:

op2<2:1>	<targets>
00	(omitted)
01	c
10	j
11	jc


Branch Target Identification. A BTI instruction is used to guard against the execution of instructions which are not the intended target of a branch.
Outside of a guarded memory region, a BTI instruction executes as a NOP. Within a guarded memory region while PSTATE.BTYPE != 0b00, a BTI instruction compatible with the current value of PSTATE.BTYPE will not generate a Branch Target Exception and will allow execution of subsequent instructions within the memory region.
The operand <targets> passed to a BTI instruction determines the values of PSTATE.BTYPE which the BTI instruction is compatible with.

 */
static uint32_t branch_target_identifier(uint8_t op2);


#endif