## Cmake fetch_content examples

```cmake
include(FetchContent)
 
FetchContent_Declare(
	MPML
	GIT_REPOSITORY	https://github.com/allosker/MPML.git
)


FetchContent_MakeAvailable(MPML)
 
target_link_libraries(Tests PRIVATE MPML::MPML)```
