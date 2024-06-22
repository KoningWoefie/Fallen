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
if(WIN32)
    set(FREETYPE_INCLUDE_DIR_ft2build ${SOURCE_DIR}/external/freetype-2.13.2/include CACHE PATH "")
    set(FREETYPE_INCLUDE_DIR_freetype2 ${SOURCE_DIR}/external/freetype-2.13.2/include CACHE PATH "")
    set(FREETYPE_LIBRARY freetype-2.13.2 CACHE PATH "")
endif(WIN32)
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
add_subdirectory (external)

if(WIN32)
    include_directories( # g++ -Ipath/to/headerfiles
    	external/glfw-3.3/include/
    	external/glm-0.9.9.2/
    	external/glew-1.9.0/include/
    	external/freetype-2.13.2/include/
    	external
    	src
    	.
    )

	link_directories( # g++ -Lpath/to/library
		external/glfw-3.3/src
		external/glew-1.9.0
		external/freetype-2.13.2
		external
		src
	)
endif(WIN32)

if(UNIX)
    include_directories( # g++ -Ipath/to/headerfiles
	   external/glfw-3.3/include/
	   external/glm-0.9.9.2/
	   external/glew-1.9.0/include/
	   external/freetype-2.13.2/include/
	   .
    )

endif(UNIX)

set(ALL_GRAPHICS_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_190
)

# src (fallenlib.a)
add_library(src # ar rcs fallenlib.a
    src/UI/button.cpp
    src/UI/button.h
	src/Core/camera.cpp
	src/Core/camera.h
	src/UI/canvas.cpp
	src/UI/canvas.h
	src/Core/config.h
	src/Core/config.cpp
	src/Core/fontmanager.cpp
	src/Core/fontmanager.h
	src/Core/game.cpp
	src/Core/game.h
	src/Core/inputmanager.cpp
	src/Core/inputmanager.h
	src/Core/mesh.cpp
	src/Core/mesh.h
	src/Core/renderer.cpp
	src/Core/renderer.h
	src/Core/resourcemanager.cpp
	src/Core/resourcemanager.h
	src/Core/scene.cpp
	src/Core/scene.h
	src/Core/sprite.cpp
	src/Core/sprite.h
	src/Core/text.h
	src/Core/texture.cpp
	src/Core/texture.h
	src/Core/timer.cpp
	src/Core/timer.h
	src/Core/object.cpp
	src/Core/object.h
	src/Core/component.cpp
	src/Core/component.h
	src/Core/transform.cpp
	src/Core/transform.h
	src/UI/image.cpp
	src/UI/image.h
	src/UI/uielement.cpp
	src/UI/uielement.h
	src/Presets/button.cpp
	src/Presets/button.h
)

add_executable(examples # g++ examples/main.cpp -o examples
	examples/main.cpp
	examples/exampleScene00.cpp
	examples/exampleScene00.h
	examples/SheetTest.cpp
	examples/SheetTest.h
	examples/testobj.cpp
	examples/testobj.h
)

if(WIN32)
    target_link_libraries(examples #g++ -lsrc
    	src
    	external/freetype-2.13.2/freetype
    	${ALL_GRAPHICS_LIBS}
    )
	file(
		COPY external/freetype-2.13.2
		DESTINATION ${CMAKE_BINARY_DIR}/external
	)
endif(WIN32)

if(UNIX)
    target_link_libraries(examples #g++ -lsrc
	   src
	   ${FREETYPE_LIBRARIES}
	   ${ALL_GRAPHICS_LIBS}
    )
endif(UNIX)
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
if(WIN32)
file(
	COPY external/freetype-2.13.2/freetype.dll
	DESTINATION ${CMAKE_BINARY_DIR}
)
endif(WIN32)
