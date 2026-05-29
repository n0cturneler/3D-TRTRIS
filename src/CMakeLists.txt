# CMakeList.txt : CMake project for CMAKE_THREE, include source and define
# project specific logic here.

# Add source to this project's executable.
add_executable (main  "main.cpp")
target_compile_options(main PRIVATE
    -Wall
    -Wextra
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -pedantic-errors
)

# Include headers from libs/lib
# target_include_directories (main PRIVATE
#	${CMAKE_SOURCE_DIR}/libs/include
# )

# Include libraries from libs/lib
# target_link_directories (main PRIVATE
#	${CMAKE_SOURCE_DIR}/libs/lib
# )




