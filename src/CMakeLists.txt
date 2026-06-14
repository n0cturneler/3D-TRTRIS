# CMakeList.txt : CMake project for CMAKE_THREE, include source and define
# project specific logic here.

# Add source to this project's executable.
add_executable (main  "main.cpp" "Pieces.cpp" "Background.cpp" "UI.cpp" "Grid.cpp")
target_compile_options(main PRIVATE
    -Wall
    -Wextra
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -pedantic-errors
)

# Include Raylib
find_package(raylib CONFIG REQUIRED)
target_link_libraries(main PRIVATE raylib)

# Include the header folder
target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR}/headers)

# Include headers from libs/lib
target_include_directories (main PRIVATE
	${CMAKE_SOURCE_DIR}/libs/include
)

# Include libraries from libs/lib
# target_link_directories (main PRIVATE
#	${CMAKE_SOURCE_DIR}/libs/lib
# )




