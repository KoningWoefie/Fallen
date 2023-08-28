# CMake entry point
cmake_minimum_required (VERSION 3.1)
project (Fallen)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
	message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

# Compile external dependencies
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2")

	# For leak-checking and profiling, add '-pg' to CXX flags
	# set(CMAKE_CXX_FLAGS "-Wall -pg -std=c++11 -O2")
	# valgrind --leak-check=full ./pokemans
	# ./pokemans # creates cmon.out
	# gprof pokemans gmon.out > analysis.txt
endif(UNIX)

if(WIN32)
	# Create a group for Visual Studio
	SOURCE_GROUP(src REGULAR_EXPRESSION ".*/src/.*" )
	# suppress pedantic warnings
	#add_definitions( "/W1 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" )
endif(WIN32)

add_definitions( # g++ -Dxxx
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Compile external dependencies
add_subdirectory (external)

include_directories( # g++ -Ipath/to/headerfiles
	external/glfw-3.3/include/
	external/glm-0.9.9.2/
	external/glew-1.9.0/include/
	.
)

link_directories( # g++ -Lpath/to/library

)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_190
)

# src (fallenlib.a)
add_library(src # ar rcs fallenlib.a
	src/camera.cpp
	src/camera.h
	src/config.h
	src/dynamic.cpp
	src/dynamic.h
	src/game.cpp
	src/game.h
	src/mesh.cpp
	src/mesh.h
	src/renderer.cpp
	src/renderer.h
	src/resourcemanager.cpp
	src/resourcemanager.h
	src/scene.cpp
	src/scene.h
	src/sprite.cpp
	src/sprite.h
	src/spritesheet.cpp
	src/spritesheet.h
	src/texture.cpp
	src/texture.h
	src/timer.cpp
	src/timer.h
)

add_executable(examples # g++ examples/main.cpp -o examples
	examples/main.cpp
	examples/exampleScene00.cpp
	examples/exampleScene00.h
	examples/SheetTest.cpp
	examples/SheetTest.h
)

target_link_libraries(examples #g++ -lsrc
	src
	${ALL_GRAPHICS_LIBS}
)
# Copy assets and shaders to the build directory
# (In Visual Studio, copy these directories to either 'Release' or 'Build')
file(
	COPY examples/assets
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY src/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY src/fonts
	DESTINATION ${CMAKE_BINARY_DIR}
)
