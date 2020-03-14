# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (tbe)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
# add_subdirectory (Hello)
# add_subdirectory (Demo)
# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_library(SOIL SOIL /usr/local/lib/libSOIL.a)
find_library(nlohmann_json /include)


include_directories($(GLEW_INCLUDE_DIRS) ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} .)


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
# target_include_directories (Hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES "*.cpp")

# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable(tbe ${SOURCES})

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries(tbe ${SOIL} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} ${SOIL_INCLUDE_DIRS})


