cmake_minimum_required(VERSION 2.8)

project (cardserver)

set (SOURCES
	GameController.cpp
	NetworkController.cpp
	PlayerObject.cpp
	RestfulObject.cpp
	TableObject.cpp
	main.cpp)

add_executable(cardserver ${SOURCES})

# should remove this include-depending, when correct libsimplecard cmake
include_directories(/usr/local/include/libsimplecards)


target_link_libraries(cardserver microhttpd simplecards)

install (TARGETS cardserver DESTINATION /usr/local/bin)

