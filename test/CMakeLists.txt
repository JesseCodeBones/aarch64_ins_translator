find_package(GTest REQUIRED)
file(GLOB test_sources CONFIGURE_DEPENDS ./*.cpp)
add_executable(
  aarch64_cpp_test
  ${test_sources}
)

target_link_libraries(
  aarch64_cpp_test
  GTest::gtest_main
)

file(GLOB sources CONFIGURE_DEPENDS ../*.cpp )
target_sources(aarch64_cpp_test PUBLIC ${sources})
include(GoogleTest)
gtest_discover_tests(aarch64_cpp_test)
