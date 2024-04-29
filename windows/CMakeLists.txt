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

set(SOURCE_DIR
	${CMAKE_SOURCE_DIR}/..
)

# Compile external dependencies
set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(OpenGL REQUIRED)
set(FREETYPE_INCLUDE_DIR_ft2build ${SOURCE_DIR}/external/freetype/include CACHE PATH "")
set(FREETYPE_INCLUDE_DIR_freetype2 ${SOURCE_DIR}/external/freetype/include CACHE PATH "")
set(FREETYPE_LIBRARY freetype CACHE PATH "")
find_package(Freetype REQUIRED)

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
	add_definitions( "/W1 /D_CRT_SECURE_NO_WARNINGS /wd4514 /nologo" )
endif(WIN32)

add_definitions( # g++ -Dxxx
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Compile external dependencies
add_subdirectory (${SOURCE_DIR}/external ${CMAKE_BINARY_DIR}/external)

include_directories( # g++ -Ipath/to/headerfiles
	${SOURCE_DIR}/external/glfw-3.3/include/
	${SOURCE_DIR}/external/glm-0.9.9.2/
	${SOURCE_DIR}/external/glew-1.9.0/include/
	${SOURCE_DIR}/external/freetype/include/
	${SOURCE_DIR}/external
	${SOURCE_DIR}/src
	${SOURCE_DIR}/.
)

link_directories( # g++ -Lpath/to/library
	${SOURCE_DIR}/external/glfw-3.3/src
	${SOURCE_DIR}/external/glew-1.9.0
	${SOURCE_DIR}/external/freetype
	${SOURCE_DIR}/external
	${SOURCE_DIR}/src
)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_190
)

# src (fallenlib.a)
add_library(src # ar rcs fallenlib.a
    ${SOURCE_DIR}/src/button.cpp
    ${SOURCE_DIR}/src/button.h
	${SOURCE_DIR}/src/camera.cpp
	${SOURCE_DIR}/src/camera.h
	${SOURCE_DIR}/src/canvas.cpp
	${SOURCE_DIR}/src/canvas.h
	${SOURCE_DIR}/src/config.h
	${SOURCE_DIR}/src/config.cpp
	${SOURCE_DIR}/src/fontmanager.cpp
	${SOURCE_DIR}/src/fontmanager.h
	${SOURCE_DIR}/src/game.cpp
	${SOURCE_DIR}/src/game.h
	${SOURCE_DIR}/src/inputmanager.cpp
	${SOURCE_DIR}/src/inputmanager.h
	${SOURCE_DIR}/src/mesh.cpp
	${SOURCE_DIR}/src/mesh.h
	${SOURCE_DIR}/src/renderer.cpp
	${SOURCE_DIR}/src/renderer.h
	${SOURCE_DIR}/src/resourcemanager.cpp
	${SOURCE_DIR}/src/resourcemanager.h
	${SOURCE_DIR}/src/scene.cpp
	${SOURCE_DIR}/src/scene.h
	${SOURCE_DIR}/src/sprite.cpp
	${SOURCE_DIR}/src/sprite.h
	${SOURCE_DIR}/src/text.h
	${SOURCE_DIR}/src/texture.cpp
	${SOURCE_DIR}/src/texture.h
	${SOURCE_DIR}/src/timer.cpp
	${SOURCE_DIR}/src/timer.h
	${SOURCE_DIR}/src/object.cpp
	${SOURCE_DIR}/src/object.h
	${SOURCE_DIR}/src/component.cpp
	${SOURCE_DIR}/src/component.h
	${SOURCE_DIR}/src/transform.cpp
	${SOURCE_DIR}/src/transform.h
	${SOURCE_DIR}/src/image.cpp
	${SOURCE_DIR}/src/image.h
	${SOURCE_DIR}/src/uielement.cpp
	${SOURCE_DIR}/src/uielement.h
)

add_executable(examples # g++ examples/main.cpp -o examples
	${SOURCE_DIR}/examples/main.cpp
	${SOURCE_DIR}/examples/exampleScene00.cpp
	${SOURCE_DIR}/examples/exampleScene00.h
	${SOURCE_DIR}/examples/SheetTest.cpp
	${SOURCE_DIR}/examples/SheetTest.h
	${SOURCE_DIR}/examples/testobj.cpp
	${SOURCE_DIR}/examples/testobj.h
)

target_link_libraries(examples #g++ -lsrc
	src
	${SOURCE_DIR}/external/freetype/objs/freetype.lib
	${ALL_GRAPHICS_LIBS}
)

# Copy assets and shaders to the build directory
# (In Visual Studio, copy these directories to either 'Release' or 'Build')
file(
	COPY ${SOURCE_DIR}/examples/assets
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY ${SOURCE_DIR}/src/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY ${SOURCE_DIR}/src/fonts
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY ${SOURCE_DIR}/external/freetype/freetype.dll
	DESTINATION ${CMAKE_BINARY_DIR}
)
