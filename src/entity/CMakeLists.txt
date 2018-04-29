add_library (${PROJECT_NAME}_entity entity.cpp inert_entity.cpp living_entity.cpp)

add_subdirectory (factory)

add_subdirectory (velocity_strategy)

add_subdirectory (ant)
add_subdirectory (food)

target_link_libraries (${PROJECT_NAME}_entity Qt5::Widgets)
target_link_libraries (${PROJECT_NAME}_entity ${PROJECT_NAME}_food ${PROJECT_NAME}_ant)
target_link_libraries (${PROJECT_NAME}_entity ${PROJECT_NAME}_world)

install (TARGETS ${PROJECT_NAME}_entity DESTINATION lib)
install (FILES entity.h DESTINATION include/entity)
install (FILES inert_entity.h DESTINATION include/entity)
