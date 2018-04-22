add_library (${PROJECT_NAME}_ui mainwindow.cpp )
target_link_libraries (${PROJECT_NAME}_ui Qt5::Widgets)

install (TARGETS ${PROJECT_NAME}_ui DESTINATION bin)
install (FILES mainwindow.h DESTINATION include/ui)
