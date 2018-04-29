# Include the classic directory
include_directories ("${PROJECT_SOURCE_DIR}/src")

# Test case for Food
add_executable(test_food test_food.cpp)
target_link_libraries(test_food ${PROJECT_NAME}_food)
target_link_libraries(test_food Qt5::Widgets Qt5::Test)

add_test(Food test_food)

# Test case for Ant
add_executable(test_ant test_ant.cpp)
target_link_libraries(test_ant ${PROJECT_NAME}_ant)
target_link_libraries(test_ant Qt5::Widgets Qt5::Test)

add_test(Ant test_ant)

# Test case for World
add_executable(test_world test_world.cpp)
target_link_libraries(test_world ${PROJECT_NAME}_world)
target_link_libraries(test_world Qt5::Widgets Qt5::Test)

add_test(World test_world)

# Install location
install (TARGETS test_food DESTINATION bin)
install (TARGETS test_world DESTINATION bin)
