cmake_minimum_required(VERSION 3.12..4.3)

project(
  Rx
  LANGUAGES C
  VERSION 0.1.0
  HOMEPAGE_URL "https://github.com/sarkar-segfault/Rx"
  DESCRIPTION "A rendering library for simpletons and wizards alike"
)

option(Rx_Testing "Whether to build tests and enable CTest integration" OFF)
add_library(Rx Sources/Engine.c Sources/Device/Core.c Sources/Device/Extra.c)

if(BUILD_SHARED_LIBS)
  target_compile_definitions(Rx PRIVATE Rx__Shared)
endif()

target_compile_definitions(Rx PRIVATE Rx__Build)

target_compile_definitions(
  Rx PUBLIC
  Rx_Version="${PROJECT_VERSION}"
  Rx_VersionMajor="${PROJECT_VERSION_MAJOR}"
  Rx_VersionMinor="${PROJECT_VERSION_MINOR}"
  Rx_VersionMicro="${PROJECT_VERSION_PATCH}"
)

target_include_directories(Rx PUBLIC Headers)

target_compile_features(Rx PUBLIC c_std_99)

find_package(Vulkan REQUIRED)

target_link_libraries(Rx PRIVATE Vulkan::Vulkan)

if(Rx_Testing)
  include(FetchContent)

  FetchContent_Declare(
    Vx
    GIT_REPOSITORY https://github.com/sarkar-segfault/Vx.git
    GIT_TAG main
  )

  FetchContent_MakeAvailable(Vx)

  function(Rx_Test name)
      add_executable(${name} Tests/${name}.c)
      target_link_libraries(${name} PRIVATE Vx Rx)
      add_test(NAME ${name} COMMAND ${name})
  endfunction()

  Rx_Test(Basic)
  enable_testing()
endif()
