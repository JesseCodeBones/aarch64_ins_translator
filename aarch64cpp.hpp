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

  /**

    this instruction require EL1 or higher privilege level

    AT <at_op>, <Xt>
    is equivalent to
    SYS #<op1>, C7, <Cm>, #<op2>, <Xt>

    示例
    假设我们有以下情况：

    AT S1E1R, X0
    S1E1R: 这是访问类型操作符，表示一级转换表的只读访问。
    X0: 这是寄存器，包含要访问的内存地址。

    结果存储：
    翻译结果会更新一些系统寄存器，如 PAR_EL1（Physical Address Register）。
    PAR_EL1 包含翻译后的物理地址和一些状态信息（如访问权限错误）。

    操作系统负责创建、管理和更新页表。
    操作系统会设置页表基址寄存器（如 TTBR0_EL1 和 TTBR1_EL1）以指向有效的页表。
    操作系统还负责处理页表中的权限和访问控制。

    op1	CRm<0>	op2	<at_op>	 Architectural Feature
    000	0	    000	         S1E1R	-
    000	0	    001	         S1E1W	-
    000	0	    010	         S1E0R	-
    000	0	    011	         S1E0W	-
    000	1	    000	         S1E1RP	FEAT_PAN2
    000	1	    001	         S1E1WP	FEAT_PAN2
    100	0	    000	         S1E2R	-
    100	0	    001	         S1E2W	-
    100	0	    100	         S12E1R	-
    100	0	    101	         S12E1W	-
    100	0	    110	         S12E0R	-
    100	0	    111	         S12E0W	-
    110	0	    000	         S1E3R	-
    110	0	    001	         S1E3W	-

   */
  static uint32_t address_translate(uint8_t op1, uint8_t x, uint8_t op2,
                                    uint8_t rt);

  /**
  Move wide with keep moves an optionally-shifted 16-bit immediate value into a
  register, keeping other bits unchanged.
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

  /**
  只能在特权模式下执行，所以不准备有test

  Authenticate Data address, using key A. This instruction authenticates a data
  address, using a modifier and key A. The address is in the general-purpose
  register that is specified by <Xd>.

  @param z if z == 0, AUTDA Xd Xn, if z == 1, AUTDA Xd
  @param rd Destination register
  @param rn First operand register
  */
  static uint32_t authenticate_data_address_A(uint8_t z, uint8_t rd,
                                              uint8_t rn);
  /**
    只能在特权模式下执行，所以不准备有test

    Authenticate Data address, using key B. This instruction authenticates a
data address, using a modifier and key B.

The address is in the general-purpose register that is specified by <Xd>.

    @param z if z == 0, AUTDB Xd Xn, if z == 1, AUTDB Xd
    @param rd Destination register
    @param rn First operand register
    */
  static uint32_t authenticate_data_address_B(uint8_t z, uint8_t rd,
                                              uint8_t rn);
  /**
  只能在特权模式下执行，所以不准备有test

  Authenticate Instruction address, using key A. This instruction
  authenticates an instruction address, using a modifier and key A.

  The address is:

  In the general-purpose register that is specified by <Xd> for AUTIA and
  AUTIZA. In X17, for AUTIA1716. In X30, for AUTIASP and AUTIAZ.

    */
  static uint32_t authenticate_instruction_address_A(uint8_t z, uint8_t rd,
                                                     uint8_t rn);
  /**
只能在特权模式下执行，所以不准备有test

Authenticate Instruction address, using key B. This instruction
authenticates an instruction address, using a modifier and key B.

The address is:

In the general-purpose register that is specified by <Xd> for AUTIA and
AUTIZA. In X17, for AUTIA1716. In X30, for AUTIASP and AUTIAZ.

*/
  static uint32_t authenticate_instruction_address_B(uint8_t z, uint8_t rd,
                                                     uint8_t rn);
  /**
    转换PSTATE寄存器里存储标志位的格式，有些软件需要这个格式
    该指令集没有输入，执行的时候，会转换PSTATE寄存器里存储标志位的格式
    bit n = '0';
    bit z = PSTATE.Z OR PSTATE.V;
    bit c = PSTATE.C AND NOT(PSTATE.V);
    bit v = '0';

    PSTATE.N = n;
    PSTATE.Z = z;
    PSTATE.C = c;
    PSTATE.V = v;
   */
  static uint32_t ax_flag();
  static uint32_t mov_wide_immediate(uint8_t hw, uint16_t imm16, uint8_t rd);
  static uint32_t ret_rn(uint8_t rn);
};