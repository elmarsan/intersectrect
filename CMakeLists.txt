cmake_minimum_required (VERSION 3.8)
project ("rectintersect")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(lib/include)
 
add_executable (rectintersect "main.cpp")
target_include_directories(rectintersect PRIVATE "lib/include")
target_link_directories(rectintersect PRIVATE "lib/lib")
target_link_libraries(rectintersect PRIVATE SDL2 SDL2main)

message("Building ${CMAKE_BUILD_TYPE}")
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")      
    file(GLOB dll_files "${CMAKE_CURRENT_SOURCE_DIR}/lib/lib/*.dll")
    file(COPY ${dll_files} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()