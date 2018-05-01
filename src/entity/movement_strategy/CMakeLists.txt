add_library (${PROJECT_NAME}_movement_strategy movement_strategy_base.cpp movement_strategy_alignment.cpp movement_strategy_cohesion.cpp movement_strategy_separation.cpp movement_strategy.cpp movement_strategy_decorator.cpp movement_strategy_all_align.cpp)
target_link_libraries (${PROJECT_NAME}_movement_strategy Qt5::Widgets)

install (TARGETS ${PROJECT_NAME}_movement_strategy DESTINATION bin)
install (FILES movement_strategy_base.h DESTINATION include/entity/movement_strategy)
install (FILES movement_strategy_alignment.h movement_strategy_all_align.h movement_strategy_cohesion.h movement_strategy_separation.h movement_strategy.h movement_strategy_decorator.h DESTINATION include/entity/movement_strategy)
