# Include the classic directory
include_directories ("${PROJECT_SOURCE_DIR}/src")

# Test case for Food
add_executable(test_food test_food.cpp)
target_link_libraries(test_food ${PROJECT_NAME}_food)
target_link_libraries(test_food Qt5::Widgets Qt5::Test)

add_test(test_food test_food)

# Install location
install (TARGETS test_food DESTINATION bin)
