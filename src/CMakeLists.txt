set (emergence_VERSION_MAJOR 0)
set (emergence_VERSION_MINOR 1)
set (Install_data_dir "\"${CMAKE_INSTALL_PREFIX}/data/\"")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/src/emegenceConfig.h.in"
    "${PROJECT_SOURCE_DIR}/src/emegenceConfig.h"
    )

# add the binary tree to the search path for include files
# so that we will find FlockingConfig.h
include_directories ("${PROJECT_BINARY_DIR}/src")

add_executable (emergence main.cpp)
# Maybe linking SDL2 is not necessary since it should be ui
target_link_libraries (emergence Qt5::Widgets)

install (TARGETS emergence DESTINATION bin)
install (FILES "${PROJECT_SOURCE_DIR}/src/emergenceConfig.h"
             DESTINATION include)
