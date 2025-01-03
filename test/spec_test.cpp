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

TEST(spec, test_adc) {
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

    // adc X0, X0, X1
    auto adcIns = Aarch64CPP::adc(1, 0, 0, 1);
    auto adc = littleEdian(adcIns);
    executable.insert(executable.end(), adc.begin(), adc.end());
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
