#include <cerrno>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <sys/mman.h>
#include <thread>

#include "../aarch64cpp.hpp"

typedef int (*FuncPtr)();
typedef uint64_t (*RetU64FuncPtr)();

static FuncPtr createJit(const std::vector<uint8_t> &executable) {
  void *jitPtr = mmap(nullptr, 4096, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (jitPtr == MAP_FAILED) {
    std::cerr << "mmap failed: " << std::strerror(errno) << std::endl;
    return nullptr;
  }

  std::memcpy(jitPtr, executable.data(), executable.size());

  if (mprotect(jitPtr, 4096, PROT_READ | PROT_EXEC) == -1) {
    std::cerr << "mprotect failed: " << std::strerror(errno) << std::endl;
    munmap(jitPtr, 4096);
    return nullptr;
  }

  return (FuncPtr)jitPtr;
}

static RetU64FuncPtr createRetU64Jit(const std::vector<uint8_t> &executable) {
  void *jitPtr = mmap(nullptr, 4096, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (jitPtr == MAP_FAILED) {
    std::cerr << "mmap failed: " << std::strerror(errno) << std::endl;
    return nullptr;
  }

  std::memcpy(jitPtr, executable.data(), executable.size());

  if (mprotect(jitPtr, 4096, PROT_READ | PROT_EXEC) == -1) {
    std::cerr << "mprotect failed: " << std::strerror(errno) << std::endl;
    munmap(jitPtr, 4096);
    return nullptr;
  }

  return (RetU64FuncPtr)jitPtr;
}

static std::vector<uint8_t> littleEdian(uint32_t value) {
  std::vector<uint8_t> result;
  result.push_back(value & 0xff);
  result.push_back((value >> (sizeof(uint8_t) * 8)) & 0xff);
  result.push_back((value >> ((2 * sizeof(uint8_t)) * 8)) & 0xff);
  result.push_back((value >> ((3 * sizeof(uint8_t)) * 8)) & 0xff);
  return result;
}

static std::vector<uint8_t> storeX29X30() {

  uint32_t stp_x29_x30 = 0b101010011 << 23;
  stp_x29_x30 |= (0x2211 << 5);
  stp_x29_x30 |= (((-16 / 8) & 0b1111111) << 15);
  stp_x29_x30 |= (30 << 10);
  stp_x29_x30 |= (31 << 5);
  stp_x29_x30 |= (29);
  return littleEdian(stp_x29_x30);
}

static std::vector<uint8_t>
mov_register_register_from_to_sp(uint32_t register1, uint32_t register2) {
  uint32_t assembly = 0b1001000100000000000000 << 10;
  assembly |= register1;
  assembly |= (register2 << 5);
  return littleEdian(assembly);
}

static std::vector<uint8_t> loadX29X30() {

  uint32_t LDP_X29_X30 = 0b1010100011 << 22;
  LDP_X29_X30 |= (((16 / 8) & 0b1111111) << 15);
  LDP_X29_X30 |= (30 << 10);
  LDP_X29_X30 |= (31 << 5);
  LDP_X29_X30 |= (29);
  return littleEdian(LDP_X29_X30);
}

TEST(demo_test, always_change) {
  uint32_t result = Aarch64CPP::adc(1, 1, 1, 1);
  ASSERT_EQ(2583756833, result);
}

void prepare(std::vector<uint8_t> &executable) {
  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());
}

void teardown(std::vector<uint8_t> &executable) {
  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());
}

TEST(spec, test_adc) {
  std::vector<uint8_t> executable = {};
  prepare(executable);
  // mov X0, 21
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 21, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // mov X1, 21
  auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 21, 1);
  auto mov2 = littleEdian(movIns2);
  executable.insert(executable.end(), mov2.begin(), mov2.end());

  // adc X0, X0, X1
  auto adcIns = Aarch64CPP::adc(1, 0, 0, 1);
  auto adc = littleEdian(adcIns);
  executable.insert(executable.end(), adc.begin(), adc.end());
  teardown(executable);

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_TRUE(42 == result || 43 == result);
}

// TEST(spec, test_adc) {
//   std::vector<uint8_t> executable = {};

//   auto storex = storeX29X30();
//   executable.insert(executable.end(), storex.begin(), storex.end());
//   auto r29tor31 = mov_register_register_from_to_sp(29, 31);
//   executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

//   // main logic instructions
//   {
//     // mov X0, 21
//     auto movIns = Aarch64CPP::mov_wide_immediate(0, 21, 0);
//     auto mov = littleEdian(movIns);
//     executable.insert(executable.end(), mov.begin(), mov.end());

//     // mov X1, 21
//     auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 21, 1);
//     auto mov2 = littleEdian(movIns2);
//     executable.insert(executable.end(), mov2.begin(), mov2.end());

//     // adc X0, X0, X1
//     auto adcIns = Aarch64CPP::adc(1, 0, 0, 1);
//     auto adc = littleEdian(adcIns);
//     executable.insert(executable.end(), adc.begin(), adc.end());
//   }

//   auto r31tor29 = mov_register_register_from_to_sp(31, 29);
//   executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
//   auto loadx = loadX29X30();
//   executable.insert(executable.end(), loadx.begin(), loadx.end());
//   auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
//   auto ret = littleEdian(retIns);
//   executable.insert(executable.end(), ret.begin(), ret.end());

//   FuncPtr func = createJit(executable);
//   int result = func();
//   ASSERT_TRUE(42 == result || 43 == result);
// }

TEST(spec, test_adcs) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // mov X0, 21
    auto movIns = Aarch64CPP::mov_wide_immediate(0, 21, 0);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());

    // mov X1, 21
    auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 21, 1);
    auto mov2 = littleEdian(movIns2);
    executable.insert(executable.end(), mov2.begin(), mov2.end());

    // adcs X0, X0, X1
    auto adcsIns = Aarch64CPP::adcs(1, 0, 0, 1);
    auto adcs = littleEdian(adcsIns);
    executable.insert(executable.end(), adcs.begin(), adcs.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_TRUE(42 == result || 43 == result);
}

TEST(spec, add_extended_register_set_flags) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // mov X0, 21
    auto movIns = Aarch64CPP::mov_wide_immediate(0, 21, 0);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());

    // mov X1, 21
    auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 21, 1);
    auto mov2 = littleEdian(movIns2);
    executable.insert(executable.end(), mov2.begin(), mov2.end());

    // adds X0, X0, X1
    auto add_extended_register_set_flags =
        Aarch64CPP::add_extended_register_set_flags(1, 0, 0, 1, 0b011, 0);
    auto adds = littleEdian(add_extended_register_set_flags);
    executable.insert(executable.end(), adds.begin(), adds.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(42, result);
}

TEST(spec, test_add_extended_register) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // mov X0, 0x0
    auto movIns = Aarch64CPP::mov_wide_immediate(0, 0x1, 0);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());

    // mov X1, 0xffff
    auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 0xffff, 1);
    auto mov2 = littleEdian(movIns2);
    executable.insert(executable.end(), mov2.begin(), mov2.end());

    // add_extended_register X0, X0, X1
    auto addExtendedRegisterIns =
        Aarch64CPP::add_extended_register(1, 0, 0, 1, 0b000, 1);
    // 1 + (0xff << 1)
    auto adds = littleEdian(addExtendedRegisterIns);
    executable.insert(executable.end(), adds.begin(), adds.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0x1ff, result);
}

TEST(spec, test_add_immediate) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // mov X0, 0
    auto movIns = Aarch64CPP::mov_wide_immediate(0, 0xff, 0);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());

    // add_immediate X0, X0, 0x1 shift 12
    auto addImmediateIns = Aarch64CPP::add_immediate(1, 0, 0, 0x1, 1);
    // 0xff + (0x1 << 12)
    auto addI = littleEdian(addImmediateIns);
    executable.insert(executable.end(), addI.begin(), addI.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(4351, result);
}

TEST(spec, test_add_shifted_register) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // mov X0, 0xff
    auto movIns = Aarch64CPP::mov_wide_immediate(0, 0xff, 0);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());

    // mov X0, 0x1
    auto mov1Ins = Aarch64CPP::mov_wide_immediate(0, 0x1, 1);
    auto mov1 = littleEdian(mov1Ins);
    executable.insert(executable.end(), mov1.begin(), mov1.end());

    // add_shift x0, x0, x1, 0, 8
    auto addShiftRegister = Aarch64CPP::add_shift_register(1, 0, 0, 1, 0, 8);
    // 0xff + (0x1 << 8)
    auto addI = littleEdian(addShiftRegister);
    executable.insert(executable.end(), addI.begin(), addI.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0x1ff, result);
}

TEST(spec, test_add_immediate_set_flags) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // mov X0, #21
    auto movIns = Aarch64CPP::mov_wide_immediate(0, 21, 0);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());

    // add_shift x0, x0, x1, 0, 8
    auto addInstruction = Aarch64CPP::add_immediate_set_flags(1, 0, 0, 21, 0);
    // 0xff + (0x1 << 8)
    auto addI = littleEdian(addInstruction);
    executable.insert(executable.end(), addI.begin(), addI.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(42, result);
}

TEST(spec, test_add_shifted_register_set_flags) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // mov X0, #0xff
    auto movIns = Aarch64CPP::mov_wide_immediate(0, 0xff, 0);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());

    // mov X1, #0x1
    auto movIns1 = Aarch64CPP::mov_wide_immediate(0, 0x1, 1);
    auto mov1 = littleEdian(movIns1);
    executable.insert(executable.end(), mov1.begin(), mov1.end());

    // add_shift x0, x0, x1, 0, 8
    auto addInstruction =
        Aarch64CPP::add_shifted_register_set_flags(1, 0, 0, 1, 0, 8); // LSL 8
    // 0xff + (0x1 << 8)
    auto addI = littleEdian(addInstruction);
    executable.insert(executable.end(), addI.begin(), addI.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0x1ff, result);
}

TEST(spec, test_add_pc_and_imm) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // adr x0, 0x4
    auto addInstruction = Aarch64CPP::add_pc_and_imm(0x0, 0x1, 0); // 0b100
    auto addI = littleEdian(addInstruction);
    executable.insert(executable.end(), addI.begin(), addI.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  std::cout
      << "adr pc instruction result: " << std::hex << result
      << std::endl; // only print the value, PC address is runtime determined
}

TEST(spec, test_add_pc_and_imm_page) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  {
    // adr x0, 0x4
    auto addInstruction = Aarch64CPP::add_pc_and_imm_page(0x0, 0x1, 0); // 0b100
    auto addI = littleEdian(addInstruction);
    executable.insert(executable.end(), addI.begin(), addI.end());
  }

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  std::cout
      << "adr pc instruction with page result: " << std::hex << result
      << std::endl; // only print the value, PC address is runtime determined
}

TEST(spec, test_logic_and_immediate) {
  std::vector<uint8_t> executable = {};
  prepare(executable);

  // mov 0b1111 to x0
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0b1111, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // logic and x0 with 0b11
  auto logicAndIns = Aarch64CPP::logic_and_immediate(0, 0, 0, 0, 0, 0b111001);
  auto logicAnd = littleEdian(logicAndIns);
  executable.insert(executable.end(), logicAnd.begin(), logicAnd.end());

  teardown(executable);
  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0b11, result);
}

TEST(spec, test_logic_and_shifted_register) {
  std::vector<uint8_t> executable = {};
  prepare(executable);

  // mov 0b1111 to x0
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0b1111, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // mov 0b1100 to x1
  auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 0b1100, 1);
  auto mov2 = littleEdian(movIns2);
  executable.insert(executable.end(), mov2.begin(), mov2.end());

  // logic and x0 x1 to x0
  auto logicAndIns = Aarch64CPP::logic_and_shifted_register(0, 0, 0, 1, 0, 0);
  auto logicAnd = littleEdian(logicAndIns);
  executable.insert(executable.end(), logicAnd.begin(), logicAnd.end());

  teardown(executable);
  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0b1100, result);
}

TEST(spec, test_logic_and_immediate_set_flags) {
  std::vector<uint8_t> executable = {};
  prepare(executable);

  // mov 0b1111 to x0
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0b1111, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // logic and x0 with 0b11
  auto logicAndIns =
      Aarch64CPP::logic_and_immediate_set_flags(0, 0, 0, 0, 0, 0b111001);
  auto logicAnd = littleEdian(logicAndIns);
  executable.insert(executable.end(), logicAnd.begin(), logicAnd.end());

  teardown(executable);
  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0b11, result);
}

TEST(spec, test_logic_and_shifted_register_set_flags) {
  std::vector<uint8_t> executable = {};
  prepare(executable);

  // mov 0b1111 to x0
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0b1111, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // mov 0b1100 to x1
  auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 0b1100, 1);
  auto mov2 = littleEdian(movIns2);
  executable.insert(executable.end(), mov2.begin(), mov2.end());

  // logic and x0 x1 to x0
  auto logicAndIns =
      Aarch64CPP::logic_and_shifted_register_set_flags(0, 0, 0, 1, 0, 0);
  auto logicAnd = littleEdian(logicAndIns);
  executable.insert(executable.end(), logicAnd.begin(), logicAnd.end());

  teardown(executable);
  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0b1100, result);
}

TEST(spec, test_arithmetic_shift_right_immediate) {
  std::vector<uint8_t> executable = {};
  prepare(executable);

  // mov 0b1111 to x0
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0b1111, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // asr x0, x0, 2
  auto arithmeticShiftRightIns =
      Aarch64CPP::arithmetic_shift_right_immediate(0, 0, 0, 0, 2, 0);
  auto arithmeticShiftRight = littleEdian(arithmeticShiftRightIns);
  executable.insert(executable.end(), arithmeticShiftRight.begin(),
                    arithmeticShiftRight.end());

  teardown(executable);
  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0b11, result);
}

TEST(spec, test_arithmetic_shift_right_register) {
  std::vector<uint8_t> executable = {};
  prepare(executable);

  // mov 0b1111 to x0
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0b1111, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // mov 0b10 to x1
  auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 0b10, 1);
  auto mov2 = littleEdian(movIns2);
  executable.insert(executable.end(), mov2.begin(), mov2.end());

  // asr x0, x0, x1
  // rm shift amount is x1
  auto arithmeticShiftRightIns =
      Aarch64CPP::arithmetic_shift_right_register(0, 0, 0, 1);
  auto arithmeticShiftRight = littleEdian(arithmeticShiftRightIns);
  executable.insert(executable.end(), arithmeticShiftRight.begin(),
                    arithmeticShiftRight.end());

  teardown(executable);
  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0b11, result);
}

TEST(spec, test_arithmetic_shift_right_variable) {
  std::vector<uint8_t> executable = {};
  prepare(executable);

  // mov 0b1111 to x0
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0b1111, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // mov 0b10 to x1
  auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 0b10, 1);
  auto mov2 = littleEdian(movIns2);
  executable.insert(executable.end(), mov2.begin(), mov2.end());

  // asrv x0, x0, x1
  // rm shift amount is x1
  auto arithmeticShiftRightIns =
      Aarch64CPP::arithmetic_shift_right_variable(0, 0, 0, 1);
  auto arithmeticShiftRight = littleEdian(arithmeticShiftRightIns);
  executable.insert(executable.end(), arithmeticShiftRight.begin(),
                    arithmeticShiftRight.end());

  teardown(executable);
  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(0b11, result);
}

void embedMov64ToRegister(uint64_t value, uint32_t rd,
                          std::vector<uint8_t> &executable) {
  uint16_t lowest = value & 0xffff;
  auto movzIns = Aarch64CPP::move_imm16_zero(1, 0, lowest, rd);
  auto movz = littleEdian(movzIns);
  executable.insert(executable.end(), movz.begin(), movz.end());

  uint16_t low = (value >> 16) & 0xffff;
  auto movkIns = Aarch64CPP::move_imm16_keep(1, 1, low, rd);
  auto movk = littleEdian(movkIns);
  executable.insert(executable.end(), movk.begin(), movk.end());

  uint16_t high = (value >> 32) & 0xffff;
  auto movkIns2 = Aarch64CPP::move_imm16_keep(1, 2, high, rd);
  auto movk2 = littleEdian(movkIns2);
  executable.insert(executable.end(), movk2.begin(), movk2.end());

  uint16_t highest = (value >> 48) & 0xffff;
  auto movkIns3 = Aarch64CPP::move_imm16_keep(1, 3, highest, rd);
  auto movk3 = littleEdian(movkIns3);
  executable.insert(executable.end(), movk3.begin(), movk3.end());
}

TEST(spec, test_address_translate) {
  // address translate require the MMU knowledge, TODO handle it in future
  //   需要在特权级别（通常是 EL1 或更高）下使用。
  // 不会直接修改内存内容或指针值。
  std::vector<uint8_t> executable = {};
  prepare(executable);
  void *addr = malloc(sizeof(int32_t));
  embedMov64ToRegister((uint64_t)addr, 0, executable);
  auto addressTranslateIns = Aarch64CPP::address_translate(0b100, 0, 0b111, 0);
  auto addressTranslate = littleEdian(addressTranslateIns);
  executable.insert(executable.end(), addressTranslate.begin(),
                    addressTranslate.end());
  teardown(executable);
  free(addr);
}

TEST(spec, test_branch_immediate) {
  std::vector<uint8_t> executable = {};
  prepare(executable);
  // mov  x0 #42
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 42, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());
  // b 2
  // pc 指向当前指令，所以跳转到下一条指令，所以跳过当前指令，需要+2
  // branch指令会补齐00在最后，所以需要右移两位
  auto branchIns = Aarch64CPP::branch_immediate(0x2);
  auto branch = littleEdian(branchIns);
  executable.insert(executable.end(), branch.begin(), branch.end());

  // mov 24 to x0
  auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 24, 0);
  auto mov2 = littleEdian(movIns2);
  executable.insert(executable.end(), mov2.begin(), mov2.end());
  teardown(executable);

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(42, result);
}

TEST(spec, test_branch_immediate_conditional) {
  std::vector<uint8_t> executable = {};
  prepare(executable);
  // mov  x0 #42
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 42, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());
  // b 2
  // pc 指向当前指令，所以跳转到下一条指令，所以跳过当前指令，需要+2
  // branch指令会补齐00在最后，所以需要右移两位
  auto branchIns = Aarch64CPP::branch_immediate_conditional(0x2, 0b1110);
  auto branch = littleEdian(branchIns);
  executable.insert(executable.end(), branch.begin(), branch.end());

  // mov 24 to x0
  auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 24, 0);
  auto mov2 = littleEdian(movIns2);
  executable.insert(executable.end(), mov2.begin(), mov2.end());
  teardown(executable);

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(42, result);
}

TEST(spec, test_branch_immediate_consistent_conditional) {
  GTEST_SKIP() << "Skipping this test temporarily.";
  std::vector<uint8_t> executable = {};
  prepare(executable);
  // mov  x0 #42
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 42, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());
  // b 2
  // pc 指向当前指令，所以跳转到下一条指令，所以跳过当前指令，需要+2
  // branch指令会补齐00在最后，所以需要右移两位
  auto branchIns =
      Aarch64CPP::branch_immediate_consistent_conditional(0x2, 0b0111);
  auto branch = littleEdian(branchIns);
  executable.insert(executable.end(), branch.begin(), branch.end());

  // mov 24 to x0
  auto movIns2 = Aarch64CPP::mov_wide_immediate(0, 24, 0);
  auto mov2 = littleEdian(movIns2);
  executable.insert(executable.end(), mov2.begin(), mov2.end());
  teardown(executable);

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(42, result);
}

TEST(spec, test_bitfield_clear) {
  // GTEST_SKIP() << "bitfield clear enabled in ARMv8.2-A, skip the test for
  // some "
  //                 "platform!!";
  std::vector<uint8_t> executable = {};
  prepare(executable);
  // mov  x0 #0xfffffff'fffffffff
  embedMov64ToRegister(0xfffffff'fffffffff, 0, executable);
  auto bitfieldIns = Aarch64CPP::bitfield_clear(1, 1, 1, 0b111001, 0);
  auto bitfield = littleEdian(bitfieldIns);
  executable.insert(executable.end(), bitfield.begin(), bitfield.end());
  teardown(executable);
  RetU64FuncPtr func = createRetU64Jit(executable);
  uint64_t result = func();
  ASSERT_EQ(0xfe00000000000000, result);
}

TEST(demo_test, return_42) {
  std::vector<uint8_t> executable = {};

  auto storex = storeX29X30();
  executable.insert(executable.end(), storex.begin(), storex.end());
  auto r29tor31 = mov_register_register_from_to_sp(29, 31);
  executable.insert(executable.end(), r29tor31.begin(), r29tor31.end());

  // main logic instructions
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 42, 0);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  auto r31tor29 = mov_register_register_from_to_sp(31, 29);
  executable.insert(executable.end(), r31tor29.begin(), r31tor29.end());
  auto loadx = loadX29X30();
  executable.insert(executable.end(), loadx.begin(), loadx.end());
  auto retIns = Aarch64CPP::ret_rn(30); // use x30 as return register
  auto ret = littleEdian(retIns);
  executable.insert(executable.end(), ret.begin(), ret.end());

  FuncPtr func = createJit(executable);
  int result = func();
  ASSERT_EQ(42, result);
}

TEST(spec, test_bitfield_insert) {
  std::vector<uint8_t> executable = {};
  prepare(executable);
  // mov  x0 #0xfffffff'fffffffff
  embedMov64ToRegister(0xfffffff'fffffffff, 0, executable);

  // mov x1 #0xff
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0xff, 1);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // bfi x0, x1, 0, 0b111001, 0
  auto bitfieldIns = Aarch64CPP::bitfield_insert(1, 1, 0, 0b111001, 0, 1);
  auto bitfield = littleEdian(bitfieldIns);
  executable.insert(executable.end(), bitfield.begin(), bitfield.end());
  teardown(executable);
  RetU64FuncPtr func = createRetU64Jit(executable);
  uint64_t result = func();
  ASSERT_EQ(0xfc000000000000ff, result);
}

TEST(spec, test_bitwise_bit_clear) {
  std::vector<uint8_t> executable = {};
  prepare(executable);
  // mov  x0 #0xfffffff'fffffffff
  embedMov64ToRegister(0xfffffff'fffffffff, 0, executable);

  // mov x1 #0xff
  auto movIns = Aarch64CPP::mov_wide_immediate(0, 0xff, 1);
  auto mov = littleEdian(movIns);
  executable.insert(executable.end(), mov.begin(), mov.end());

  // bfi x0, x1, 0, 0b111001, 0
  auto bitfieldIns = Aarch64CPP::bitwise_bit_clear(1, 0b10, 0, 0, 0, 1, 0);
  auto bitfield = littleEdian(bitfieldIns);
  executable.insert(executable.end(), bitfield.begin(), bitfield.end());
  teardown(executable);
  RetU64FuncPtr func = createRetU64Jit(executable);
  uint64_t result = func();
  ASSERT_EQ(0x00000000000000ff, result);
}

// TEST(spec, test_branch_with_link_immediate) {
//   std::vector<uint8_t> executable = {};
//   prepare(executable);

//   {
//     // mov x0 #42
//     auto movIns = Aarch64CPP::mov_wide_immediate(0, 42, 0);
//     auto mov = littleEdian(movIns);
//     executable.insert(executable.end(), mov.begin(), mov.end());

//   }
//   {
//     // bl 2
//     auto ins = Aarch64CPP::branch_with_link_immediate(2);
//     auto bytes = littleEdian(ins);
//     executable.insert(executable.end(), bytes.begin(), bytes.end());
//   }
//   {
//     // mov x0 #24
//     // this one will not take effect, because it has been jumped over
//     auto ins = Aarch64CPP::mov_wide_immediate(0, 24, 0);
//     auto bytes = littleEdian(ins);
//     executable.insert(executable.end(), bytes.begin(), bytes.end());
//   }
//   {
//     // ret
//     auto ins = Aarch64CPP::ret_rn(30);
//     auto bytes = littleEdian(ins);
//     executable.insert(executable.end(), bytes.begin(), bytes.end());
//   }

//   teardown(executable);
//   RetU64FuncPtr func = createRetU64Jit(executable);
//   uint64_t result = func();
//   ASSERT_EQ(42, result);
// }


// TEST(spec, test_break_point) {
//   std::vector<uint8_t> executable = {};
//   prepare(executable);

//   {
//     // mov x0 #42
//     auto movIns = Aarch64CPP::break_point(42);
//     auto mov = littleEdian(movIns);
//     executable.insert(executable.end(), mov.begin(), mov.end());

//   }

//   teardown(executable);
//   RetU64FuncPtr func = createRetU64Jit(executable);
//   uint64_t result = func();
//   ASSERT_EQ(42, result);
// }


TEST(spec, test_branch_target_identifier) {
  std::vector<uint8_t> executable = {};
  prepare(executable);

  {
    // bti c
    auto movIns = Aarch64CPP::branch_target_identifier(0b01);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());
  }

  {
    // mov x0 #42
    auto movIns = Aarch64CPP::mov_wide_immediate(0, 42, 0);
    auto mov = littleEdian(movIns);
    executable.insert(executable.end(), mov.begin(), mov.end());
  }

  teardown(executable);
  RetU64FuncPtr func = createRetU64Jit(executable);
  uint64_t result = func();
  ASSERT_EQ(42, result);
}
