project(Duck)

add_executable (${PROJECT_NAME} "src/main.cpp" "src/App.h" "src/App.cpp" "src/Camera.cpp" "src/Camera.h" "src/Square.h")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.
target_link_libraries (${PROJECT_NAME} 
	engine
)
