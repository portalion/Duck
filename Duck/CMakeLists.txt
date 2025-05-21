# CMakeList.txt : CMake project for Duck, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Duck "main.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Duck PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries (Duck 
	glfw 
	libglew_static
)

target_include_directories (Duck PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories (Duck PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)
