add_library (${PROJECT_NAME}_ant ant.cpp role/role_ant.cpp role/role_ant_explorer.cpp role/role_ant_worker.cpp)

target_link_libraries (${PROJECT_NAME}_ant Qt5::Widgets)
target_link_libraries (${PROJECT_NAME}_ant ${PROJECT_NAME}_entity)

install (FILES ant.h DESTINATION include/entity/ant)
install (FILES role/role_ant.h role/role_ant_explorer.h role/role_ant_worker.h DESTINATION include/entity/ant)
