project (engine)

add_library(${PROJECT_NAME} 
	"src/IndexBuffer.cpp"
	"src/Shader.cpp"
	"src/ShaderBuilder.cpp"
	"include/engine/VertexArray.ipp"
	"src/VertexBuffer.cpp"
 "src/utils/GlCall.cpp")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_include_directories(${PROJECT_NAME} PRIVATE
	${PROJECT_SOURCE_DIR}/include/engine
)

target_include_directories (${PROJECT_NAME} PUBLIC
	${PROJECT_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/external/glfw/include
	${CMAKE_SOURCE_DIR}/external/glew/include
	${CMAKE_SOURCE_DIR}/external/glm/include
)

target_link_libraries(${PROJECT_NAME} 
	glfw 
	libglew_static
	glm
)
