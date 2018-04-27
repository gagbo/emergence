add_library (${PROJECT_NAME}_ui mainwindow.cpp world_view.cpp )
target_link_libraries (${PROJECT_NAME}_ui ${PROJECT_NAME}_world)
target_link_libraries (${PROJECT_NAME}_ui Qt5::Widgets)

install (TARGETS ${PROJECT_NAME}_ui DESTINATION lib)
install (FILES mainwindow.h world_view.h DESTINATION include/ui)
