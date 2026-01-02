# CMakeList.txt : CMake project for MPML, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ( 
	MPML
	VERSION 1.0.1
	LANGUAGES CXX
)

# Create paths to file folders
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")

# Seek all files (recursively)
file(GLOB_RECURSE INCLUDE_FILES CMAKE_CONFIGURE_DEPENDS
	"${INCLUDE_DIR}/*.hpp"
	"${INCLUDE_DIR}/*.h"
)


# Add source and include to this project's executable.

add_library(MPML INTERFACE)

target_include_directories(MPML
	INTERFACE
		
		${INCLUDE_FILES}	

		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MPML PROPERTY CXX_STANDARD 20)
endif()

# define the library

target_compile_features(MPML INTERFACE cxx_std_20)