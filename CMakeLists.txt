cmake_minimum_required(VERSION 2.8)

project (cardserver)

set(CMAKE_CXX_FLAGS "-std=c++0x")

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
include_directories(/home/alexey/Work/libsimplecards)


target_link_libraries(cardserver microhttpd uriparser json)
target_link_libraries(cardserver /home/alexey/Work/libsimplecards/libsimplecards.so)

install (TARGETS cardserver DESTINATION /usr/local/bin)

