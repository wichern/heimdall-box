cmake_minimum_required(VERSION 3.9)

project("heimdall-box")

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(httplib)
include(json)
include(tinyxml2)
include(threads)

add_executable(heimdall-box 
    "src/main.cpp"
    "src/md5.cpp")
target_include_directories(heimdall-box PUBLIC "include")
target_link_libraries(heimdall-box PUBLIC
    HttpLib
    nlohmannJson
    tinyxml2
    Threads::Threads)

#add_dependencies(heimdall-box tinyxml2)
#if(NOT ${tinyxml2_FOUND})
#    message(FATAL "tinyxml2 not found")
#else()
#    message(STATUS ${tinyxml2_LIBRARY})
    #target_link_libraries(heimdall-box PUBLIC tinyxml2)
#    message(STATUS ${tinyxml2_INCLUDE_DIRS})
    #target_include_directories(heimdall-box PUBLIC ${INSTALL_DIR})
#endif()