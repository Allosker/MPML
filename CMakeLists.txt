# CMakeList.txt : CMake project for MPML, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif() 
 
project ( 
	MPML
	VERSION 1.0.12
	LANGUAGES CXX
)

# Make library

add_library(MPML INTERFACE)

add_library(MPML::MPML ALIAS MPML)

 

target_include_directories(MPML
	INTERFACE

		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		
		$<INSTALL_INTERFACE:include>
)


	# set(SRC_DIR "${PROJECT_SOURCE_DIR}/include/") 
	# set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/") 

	# file(GLOB_RECURSE CPP_FILES CMAKE_CONFIGURE_DEPENDS 
	# 	"${SRC_DIR}/*.cpp"
	# 	"${SRC_DIR}/*.c"  
	# ) 
	
	# file(GLOB_RECURSE HPP_FILES CMAKE_CONFIGURE_DEPENDS  
	# 	"${INCLUDE_DIR}/*.hpp"
	# 	"${INCLUDE_DIR}/*.h"
	# ) 


	# add_executable( MPML
	# 	"${PROJECT_SOURCE_DIR}/include/mpml/test.cpp"
	# 	"${CPP_FILES}"
	# 	"${HPP_FILES}"  
	# ) 

	# target_include_directories(MPML PUBLIC ${INCLUDE_DIR})

	# target_compile_features(MPML PRIVATE cxx_std_23)

target_compile_features(MPML INTERFACE cxx_std_23)

# Dowloading Rules

include(GNUInstallDirs)

 
install(
	TARGETS MPML
	EXPORT MPMLTargets
)

install(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
	EXPORT MPMLTargets
	NAMESPACE MPML::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MPML
)
