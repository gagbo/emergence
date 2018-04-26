add_library (${PROJECT_NAME}_entity_factory entity_factory.cpp)

target_link_libraries (${PROJECT_NAME}_entity_factory ${PROJECT_NAME}_entity)

install (TARGETS ${PROJECT_NAME}_entity_factory DESTINATION lib)
install (FILES entity_factory.h DESTINATION include/entity/factory)
