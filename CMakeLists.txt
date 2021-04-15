cmake_minimum_required(VERSION 3.17)
project(GinRummyBot)

set(CMAKE_CXX_STANDARD 14)

find_package (Python3 COMPONENTS Interpreter Development)

add_executable(GinRummyBot main.cpp deck.cpp deck.h game.cpp game.h player.cpp player.h mcts.cpp mcts.h cardProperties.h #[[node.cpp node.h]] ${PYTHON_FILES})
target_link_libraries(GinRummyBot ${Python3_LIBRARIES})
target_include_directories(GinRummyBot PUBLIC ${Python3_INCLUDE_DIRS})
