cmake_minimum_required (VERSION 3.14.4)
project (tmpnam)

add_definitions("-fno-omit-frame-pointer -g")

add_executable(${PROJECT_NAME}-test ${PROJECT_NAME}-test.c ${PROJECT_NAME}.c)

# do an AFL or LibFuzzer build

if("${CMAKE_C_COMPILER}" MATCHES ".*/afl-.*")
  set(ENV{AFL_USE_ASAN} 1)
  set(ENV{AFL_HARDEN} 1)
  add_executable(${PROJECT_NAME}-afl ${PROJECT_NAME}-afl.c ${PROJECT_NAME}.c)
elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  add_executable(${PROJECT_NAME}-libfuzzer ${PROJECT_NAME}.c ${PROJECT_NAME}-libfuzzer.c)
  target_compile_options(${PROJECT_NAME}-libfuzzer PRIVATE "-fsanitize=fuzzer,address")
  target_link_options(${PROJECT_NAME}-libfuzzer PRIVATE "-fsanitize=fuzzer,address")
endif()
