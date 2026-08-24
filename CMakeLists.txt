cmake_minimum_required(VERSION 3.15)
project(CPP_GAME)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB_RECURSE SOURCES "source/*.cpp")
  
file(GLOB_RECURSE HEADERS "include/*.h")

file(GLOB_RECURSE DESIGN_FILES "design/*")

add_executable(CPP_GAME ${SOURCES})

target_sources(CPP_GAME PRIVATE ${HEADERS} ${DESIGN_FILES})

target_include_directories(CPP_GAME PRIVATE include)

target_link_libraries(CPP_GAME
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)

# Set source groups for better organization in Xcode
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/source PREFIX "Source Files" FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/design PREFIX "Design" FILES ${DESIGN_FILES})

