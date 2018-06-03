add_library (${PROJECT_NAME}_entity_prototypes entity_prototypes_manager.cpp)

target_link_libraries (${PROJECT_NAME}_entity_prototypes ${PROJECT_NAME}_entity)

install (FILES entity_prototypes_manager.h DESTINATION include/entity/prototype_mgmt)
