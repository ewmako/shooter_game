cmake_minimum_required(VERSION 2.6)
project(galaga)

include_directories(include)
add_executable(galaga main.cpp src/shuttle.cpp src/player.cpp src/enemy.cpp src/enemy_green.cpp src/enemy_red.cpp src/enemy_blue.cpp
               src/game.cpp src/meteoroid.cpp src/window.cpp src/keyboard.cpp
               src/weapon.cpp src/weapon_simple.cpp src/weapon_advanced.cpp src/bullet.cpp src/bullet_simple.cpp src/bullet_advanced_left.cpp src/bullet_advanced_right.cpp
               include/shuttle.h include/player.h include/enemy.h include/enemy_green.h include/enemy_red.h include/enemy_blue.h
               include/game.h include/meteoroid.h include/window.h include/keyboard.h
               include/weapon.h include/weapon_simple.h include/weapon_advanced.h include/bullet.h include/bullet_simple.h include/bullet_advanced_left.h include/bullet_advanced_right.h)
target_link_libraries(galaga ncurses pthread)
