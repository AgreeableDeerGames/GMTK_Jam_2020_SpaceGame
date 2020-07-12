
set(PROJECT_TEMPLATE_INSTALL_TARGETS ProjectTemplate ProjectTemplateExe)

# install GameBackbone lib
install(
    TARGETS ${PROJECT_TEMPLATE_INSTALL_TARGETS}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

set(PROJECT_TEMPLATE_DEPENDENT_DLLS_DIR "" CACHE PATH "Directory containing all Dlls to install")

file(GLOB DEPENDENT_DLL_FILES ${PROJECT_TEMPLATE_DEPENDENT_DLLS_DIR}/*.dll)

install (
    FILES
        ${DEPENDENT_DLL_FILES}
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin
)

set(PROJECT_RESOURCE_TEXTUERS_DIR "" CACHE PATH "Directory resource")
file(GLOB RESOURCE_TEXTURE_FILES ${CMAKE_SOURCE_DIR}/Resources/Textures/*.png)
install(
    FILES
        ${RESOURCE_TEXTURE_FILES}
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin/Textures
)

file(GLOB RESOURCE_WIDGET_FILES_PNG ${CMAKE_CURRENT_SOURCE_DIR}/Resources/TGUI_Widgets/*.png)
file(GLOB RESOURCE_WIDGET_FILES_TXT ${CMAKE_CURRENT_SOURCE_DIR}/Resources/TGUI_Widgets/*.txt)
install(
    FILES
        ${RESOURCE_WIDGET_FILES_PNG}
        ${RESOURCE_WIDGET_FILES_TXT}
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/bin/TGUI_Widgets
)

set (CPACK_PACKAGE_NAME "Project Template")
set (CPACK_PACKAGE_VENDOR "AgreeableDeerGames")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Game from GMTK 2020 Game Jam")
set (CPACK_PACKAGE_VERSION "0.1.0")
set (CPACK_PACKAGE_INSTALL_DIRECTORY "GMTK2020")

# Define NSIS installation types
set(CPACK_ALL_INSTALL_TYPES Full)
set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)
include(CPack)