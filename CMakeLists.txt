﻿cmake_minimum_required (VERSION 3.15)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# external dependencies
add_subdirectory (external/glfw)
add_subdirectory (external/glew)
add_subdirectory (external/glm)
add_subdirectory (external/stb_image)

# Add engine project
add_subdirectory (engine)

# Add the Duck executable
add_subdirectory (app)
