include(ExternalProject)

#  yhirose / cpp-httplib
ExternalProject_Add(HttpLib_Ext
	PREFIX HttpLib
	GIT_REPOSITORY "https://github.com/yhirose/cpp-httplib.git"
	GIT_TAG "v0.8.9"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
)

add_library(HttpLib INTERFACE IMPORTED)
set_target_properties(HttpLib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/HttpLib/src/HttpLib_Ext")
add_dependencies(HttpLib HttpLib_Ext)
