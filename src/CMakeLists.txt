set (emergence_VERSION_MAJOR 0)
set (emergence_VERSION_MINOR 1)
set (Install_data_dir "\"${CMAKE_INSTALL_PREFIX}/data/\"")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/src/emergenceConfig.h.in"
    "${PROJECT_SOURCE_DIR}/src/emergenceConfig.h"
    )

include_directories ("${PROJECT_SOURCE_DIR}/src")

add_subdirectory (ui)
add_subdirectory (world)
add_subdirectory (entity)

add_executable (emergence main.cpp)
target_link_libraries (emergence ${PROJECT_NAME}_ui)
target_link_libraries (emergence ${PROJECT_NAME}_food ${PROJECT_NAME}_ant)
target_link_libraries (emergence Qt5::Widgets)

install (TARGETS emergence DESTINATION bin)
install (FILES "${PROJECT_SOURCE_DIR}/src/emergenceConfig.h"
             DESTINATION include)
