project(Duck)

add_executable (${PROJECT_NAME} "src/main.cpp" "src/App.h" "src/App.cpp" "src/Camera.cpp" "src/Camera.h" "src/Square.h" "src/Cube.h")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# setup imgui
set(imgui_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/imgui")
add_library(imgui)

target_include_directories(
	imgui PUBLIC
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
)

target_sources(
	imgui PRIVATE
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
 )

target_link_libraries(imgui PUBLIC glfw libglew_static)

# TODO: Add tests and install targets if needed.
target_link_libraries (${PROJECT_NAME} 
	engine 
	imgui
	stb_image
)
