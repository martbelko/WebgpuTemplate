add_library(GLFW_LIB STATIC ${CMAKE_CURRENT_LIST_DIR}/src/Empty.cpp)

if(NOT EMSCRIPTEN)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(ext/glfw)
endif()

target_include_directories(GLFW_LIB PUBLIC "${CMAKE_CURRENT_LIST_DIR}/ext/glfw/include")
target_link_libraries(GLFW_LIB PUBLIC glfw)
