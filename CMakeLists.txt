cmake_minimum_required(VERSION 3.26)
project(WakeUpTheSpeaker)

set(CMAKE_CXX_STANDARD 17)

add_executable(WakeUpTheSpeaker main.cpp)

if(MINGW)
    set_target_properties(WakeUpTheSpeaker PROPERTIES LINK_FLAGS "-mwindows")
endif()
