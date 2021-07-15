include(ExternalProject)

#  nlohmann / json
ExternalProject_Add(nlohmannJson_Ext
	PREFIX nlohmannJson
	GIT_REPOSITORY "https://github.com/nlohmann/json.git"
	GIT_TAG "v3.9.1"
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
)

add_library(nlohmannJson INTERFACE IMPORTED)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/nlohmannJson/src/nlohmannJson_Ext/include")
set_target_properties(nlohmannJson PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_BINARY_DIR}/nlohmannJson/src/nlohmannJson_Ext/include")
add_dependencies(nlohmannJson nlohmannJson_Ext)
