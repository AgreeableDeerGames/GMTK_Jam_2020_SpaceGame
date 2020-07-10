# CMakeLists for ProjectTemplate executable 

cmake_minimum_required (VERSION 3.8)

add_executable(ProjectTemplateExe 
  "source/main.cpp"
)

target_link_libraries(ProjectTemplateExe PRIVATE ProjectTemplate)

# Include own header files
target_include_directories(ProjectTemplateExe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)