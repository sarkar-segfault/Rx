cmake_minimum_required(VERSION 3.12..4.3)

project(
  Rx
  LANGUAGES C
  VERSION 0.1.0
  HOMEPAGE_URL "https://github.com/sarkar-segfault/Rx"
  DESCRIPTION "A rendering library for simpletons and wizards alike"
)

add_library(Rx Sources/Engine.c)

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

