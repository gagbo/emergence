# TODO Factories will depend on concrete entity libraries
add_library (${PROJECT_NAME}_food food.cpp )
target_link_libraries (${PROJECT_NAME}_food Qt5::Widgets)
target_link_libraries (${PROJECT_NAME}_food ${PROJECT_NAME}_entity)

install (TARGETS ${PROJECT_NAME}_food DESTINATION bin)
install (FILES food.h DESTINATION include/entity/food)
