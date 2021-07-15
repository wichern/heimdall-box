include(ExternalProject)

set(TINYXML2_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/tinyxml2-install")
message(STATUS "${TINYXML2_INSTALL_DIR}")
file(MAKE_DIRECTORY "${TINYXML2_INSTALL_DIR}")

#  tinyxml2
ExternalProject_Add(tinyxml2_Ext
	#PREFIX tinyxml2
	GIT_REPOSITORY "https://github.com/leethomason/tinyxml2.git"
	GIT_TAG "9.0.0"
    INSTALL_DIR "${TINYXML2_INSTALL_DIR}"
	CMAKE_ARGS 
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
			-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

add_library(tinyxml2 UNKNOWN IMPORTED)
set_property(TARGET tinyxml2 PROPERTY IMPORTED_LOCATION "${TINYXML2_INSTALL_DIR}/lib/libtinyxml2.a")
target_include_directories(tinyxml2 INTERFACE "${TINYXML2_INSTALL_DIR}/include")
add_dependencies(tinyxml2 tinyxml2_Ext)
