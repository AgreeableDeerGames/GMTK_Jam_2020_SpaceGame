# CMakeLists for ProjectTemplate library

cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SELBA_WARD_SOURCES "src/*")

add_library(SelbaWard STATIC ${SELBA_WARD_SOURCES})
set_target_properties(SelbaWard PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
find_package(SFML 2 COMPONENTS network audio graphics window system)
target_link_libraries(SelbaWard PUBLIC sfml-graphics sfml-network sfml-audio sfml-window sfml-system)
