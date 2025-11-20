# CMakeList.txt : CMake project for MPML, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MPML")

# Create paths to file folders
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src/")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")

# Seek all files (recursively)
file(GLOB_RECURSE INCLUDE_FILES CMAKE_CONFIGURE_DEPENDS
	"${INCLUDE_DIR}/*.hpp"
	"${INCLUDE_DIR}/*.h"
)


# Add source and include to this project's executable.
add_executable ( MPML
	"${SRC_DIR}main.cpp"
	"${INCLUDE_FILES}"
)

target_include_directories(MPML PUBLIC ${INCLUDE_DIR})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MPML PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
