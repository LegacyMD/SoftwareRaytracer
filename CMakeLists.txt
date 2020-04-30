# Cmake vars
cmake_minimum_required (VERSION 3.8)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_SUPPRESS_REGENERATION true)

# Own vars
set (SOLUTION_NAME "RayTracer")
set (PROJECT_NAME ${SOLUTION_NAME})

# Add all source files
SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET  (SOURCES
	${SRC_DIR}/external/TinyPngOut.cpp
	${SRC_DIR}/external/TinyPngOut.hpp
	
	${SRC_DIR}/object/Object.h
	${SRC_DIR}/object/Sphere.cpp
	${SRC_DIR}/object/Sphere.h
	${SRC_DIR}/object/Plane.cpp
	${SRC_DIR}/object/Plane.h
	
	${SRC_DIR}/raytracer/RayTracer.cpp
	${SRC_DIR}/raytracer/RayTracer.h
	${SRC_DIR}/raytracer/Camera.cpp
	${SRC_DIR}/raytracer/Camera.h
	${SRC_DIR}/raytracer/Light.h
	
	${SRC_DIR}/util/Vector.h
	${SRC_DIR}/util/Color.h
	${SRC_DIR}/util/Ray.h
	
	${CMAKE_CURRENT_SOURCE_DIR}/src/Source.cpp
)


# Project setup
project (${SOLUTION_NAME})
source_group (TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
add_executable (${PROJECT_NAME} ${SOURCES})
include_directories("src" "src/external")
