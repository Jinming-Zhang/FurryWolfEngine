cmake_minimum_required(VERSION 3.15)
project(FurrywolfEngine VERSION 0.0.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("./includes")

file(GLOB_RECURSE SRS_FILES CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/*.c"
)

find_library(GLFW NAMES glfw3 PATHS "${PROJECT_SOURCE_DIR}/lib/linux/")

if(NOT GLFW)
  message(FATAL_ERROR "GLFW not found")
endif()

find_library(ASSIMP NAMES assimp PATHS "${PROJECT_SOURCE_DIR}/lib/linux/")

if(NOT ASSIMP)
  message(FATAL_ERROR "GLFW not found")
endif()

# add_library(dl SHARED)
# add_library(m SHARED)
# add_library(GL SHARED)
# add_library(X11 SHARED)
# add_library(z SHARED)
add_executable(FurrywolfEngine ${SRS_FILES})

target_link_libraries(FurrywolfEngine ${GLFW} dl m GL X11 ${ASSIMP} z)
