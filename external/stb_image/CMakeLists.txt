project(stb_image)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_SOURCE_DIR}/external/stb_image)