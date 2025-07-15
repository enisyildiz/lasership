# CMakeList.txt : CMake project for lasership, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("lasership")

include(FetchContent)

set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
raylib
URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(raylib)

# Add source to this project's executable.
add_executable (lasership "lasership.cpp" "lasership.h" "App/src/sprite.cpp" "App/src/sprite.h" "App/src/game.cpp" "App/src/game.h" "App/src/player.cpp" "App/src/player.h"   "App/src/laser.h" "App/src/laser.cpp" "App/src/meteor.cpp" "App/src/meteor.h" "App/src/timer.cpp" "App/src/timer.h")

target_include_directories(lasership PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/App/src)

target_link_libraries(${PROJECT_NAME} raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lasership PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
