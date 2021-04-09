cmake_minimum_required(VERSION 3.17)
project(GinRummyBot)

set(CMAKE_CXX_STANDARD 14)

add_executable(GinRummyBot main.cpp card.cpp card.h deck.cpp deck.h game.cpp game.h player.cpp player.h mcts.cpp mcts.h cardProperties.h)
