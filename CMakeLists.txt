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
	VERSION 1.0.11
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

target_compile_features(MPML INTERFACE cxx_std_20)


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