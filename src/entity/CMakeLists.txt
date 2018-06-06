add_library (${PROJECT_NAME}_entity entity.cpp)
add_library (${PROJECT_NAME}_living_entity living_entity.cpp)
add_library (${PROJECT_NAME}_inert_entity inert_entity.cpp)

add_subdirectory (factory)
add_subdirectory (prototype_mgmt)

add_subdirectory (movement_strategy)

add_subdirectory (ant)
add_subdirectory (food)

target_link_libraries (${PROJECT_NAME}_entity Qt5::Widgets)
# target_link_libraries (${PROJECT_NAME}_entity ${PROJECT_NAME}_living_entity ${PROJECT_NAME}_inert_entity)
target_link_libraries (${PROJECT_NAME}_inert_entity ${PROJECT_NAME}_entity)
target_link_libraries (${PROJECT_NAME}_living_entity ${PROJECT_NAME}_entity)
target_link_libraries (${PROJECT_NAME}_entity ${PROJECT_NAME}_world)

install (TARGETS ${PROJECT_NAME}_entity DESTINATION lib)
install (FILES entity.h DESTINATION include/entity)
install (FILES inert_entity.h DESTINATION include/entity)
install (FILES living_entity.h DESTINATION include/entity)
