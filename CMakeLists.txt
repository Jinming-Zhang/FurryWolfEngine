cmake_minimum_required(VERSION 3.15)
project(FurrywolfEngine VERSION 0.0.3)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("./includes")

file(GLOB_RECURSE SRS_FILES CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/*.c"
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})

# add_executable(FurrywolfEngine ${SRS_FILES})
add_subdirectory(editor/bindings/pybind11)
pybind11_add_module(FurrywolfEngine ${SRS_FILES} editor/bindings/EngineBindings.cpp)

if(WIN32)
  add_definitions(-DWINDOWS)
  find_library(GLFW NAMES glfw3.lib PATHS "${PROJECT_SOURCE_DIR}/lib/windows/")

  if(NOT GLFW)
    message(FATAL_ERROR "GLFW not found on Windows")
  endif()

  find_library(ASSIMP NAMES assimp-vc143-mtd.lib PATHS "${PROJECT_SOURCE_DIR}/lib/windows/")

  if(NOT ASSIMP)
    message(FATAL_ERROR "Assimp not found on Windows")
  endif()

  find_library(ZLib NAMES zlibstaticd.lib PATHS "${PROJECT_SOURCE_DIR}/lib/windows/")

  if(NOT ZLib)
    message(FATAL_ERROR "zlibstaticd not found on Windows")
  endif()

  target_link_libraries(FurrywolfEngine PRIVATE opengl32.lib ${GLFW} ${ZLib} ${ASSIMP} kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib)
else()
  find_library(GLFW NAMES glfw3 PATHS "${PROJECT_SOURCE_DIR}/lib/linux/")

  if(NOT GLFW)
    message(FATAL_ERROR "GLFW not found")
  endif()

  find_library(ASSIMP NAMES assimp PATHS "${PROJECT_SOURCE_DIR}/lib/linux/")

  if(NOT ASSIMP)
    message(FATAL_ERROR "GLFW not found")
  endif()

  target_link_libraries(FurrywolfEngine ${GLFW} dl m GL X11 ${ASSIMP} z)
endif()
