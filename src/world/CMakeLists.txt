# World is not ready to be compiled yet
add_library (${PROJECT_NAME}_world world.cpp)
target_link_libraries (${PROJECT_NAME}_world ${PROJECT_NAME}_entity)
target_link_libraries (${PROJECT_NAME}_world ${PROJECT_NAME}_entity_prototypes)
target_link_libraries (${PROJECT_NAME}_world Qt5::Widgets)

install (TARGETS ${PROJECT_NAME}_world DESTINATION lib)
install (FILES world.h DESTINATION include/world)
