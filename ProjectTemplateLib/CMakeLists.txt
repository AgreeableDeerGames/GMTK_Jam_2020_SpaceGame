# CMakeLists for ProjectTemplate library

cmake_minimum_required (VERSION 3.8)
add_library(ProjectTemplate SHARED
  "include/ProjectTemplate.h"
  "include/ProjectTemplate/Core/EventController.h"
  "include/ProjectTemplate/Core/InputRecorder.h"
  "include/ProjectTemplate/Core/Ship.h"
  "include/ProjectTemplate/Core/TemplateRegion.h"
  "include/ProjectTemplate/Core/Terminal.h" 
  "include/ProjectTemplate/Core/TerminalOne.h" 
  "include/ProjectTemplate/Core/TerminalRegion.h" 
  "include/ProjectTemplate/Utils/DisplayText.h"
  "include/ProjectTemplate/Utils/DllUtils.h"
  "include/ProjectTemplate/Utils/GestureBindUtils.h"
  
  "source/Core/EventController.cpp"
  "source/Core/InputRecorder.cpp"
  "source/Core/Ship.cpp"
  "source/ProjectTemplate.cpp"
  "source/Core/Terminal.cpp"
  "source/Core/TerminalOne.cpp"
  "source/Core/TerminalRegion.cpp"
)
set_target_properties(ProjectTemplate PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

# GameBackbone has SFML as a public target. This means that it is automatically
# added to the target_link_libraries for ProjectTemplate
# ProjectTemplate still needs to find SFML for GB to link against though.
find_package(SFML 2 COMPONENTS network audio graphics window system)

find_package(GameBackbone 0.4.1 REQUIRED)
target_link_libraries(ProjectTemplate PUBLIC GameBackbone) 
target_link_libraries(ProjectTemplate PUBLIC SelbaWard) 

message("current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(ProjectTemplate PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")