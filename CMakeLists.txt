cmake_minimum_required(VERSION 3.12...3.26)

project( playground LANGUAGES C CXX )
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT is_multi_config AND NOT (CMAKE_BUILD_TYPE OR DEFINED ENV{CMAKE_BUILD_TYPE}))
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Release default")
endif()

find_package(OpenMP COMPONENTS CXX)

if (MSVC)
    # warning level 4 (and all warnings as errors, /WX)
    add_compile_options(/W4)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Clone Ultimaille
include(FetchContent)
FetchContent_Declare(
  ultimaille
  GIT_REPOSITORY https://github.com/ssloy/ultimaille
  GIT_TAG        30c245d
)
FetchContent_MakeAvailable(ultimaille)
include_directories(${ultimaille_SOURCE_DIR})

# Download Graphite
file(DOWNLOAD https://github.com/BrunoLevy/GraphiteThree/releases/download/v3-1.8.4/graphite3-1.8.5-rc-win64.zip ${CMAKE_SOURCE_DIR}/graphite.zip)
# Unzip Graphite
execute_process(
    COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_SOURCE_DIR}/graphite.zip
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_subdirectory(examples)

