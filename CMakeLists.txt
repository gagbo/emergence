cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 14)
project (emergence)

find_package (Qt5 5.10 COMPONENTS Widgets Test REQUIRED QUIET)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

set (BUILD_SHARED_LIBS OFF)

set (CMAKE_CXX_FLAGS "-pipe \
-Wall -Wextra -fexceptions")
set (CMAKE_CXX_FLAGS_RELEASE "-O3 -D_FORTIFY_SOURCE=3 -DNDEBUG")
set (CMAKE_CXX_FLAGS_MINSIZEREL "-Os -D_FORTIFY_SOURCE=2 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -D_FORTIFY_SOURCE=2 -g -DNDEBUG")
set (CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address -fno-omit-frame-pointer")
set (CMAKE_CXX_FLAGS_COVERAGE "-O0 -g -fprofile-arcs -ftest-coverage")
set (CMAKE_CXX_LINKER_FLAGS_DEBUG "-lasan")
set (CMAKE_CXX_LINKER_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage")

enable_testing ()

add_subdirectory (src)
add_subdirectory (test)
