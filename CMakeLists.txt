cmake_minimum_required(VERSION 3.20)

project(MyProject C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_USE_RESPONSE_FILE_FOR_INCLUDES OFF)
set(CMAKE_C_USE_RESPONSE_FILE_FOR_OBJECTS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

add_executable(MyProject main.c MyProject.rc)

target_include_directories(MyProject PRIVATE
        ${GTK4_INCLUDE_DIRS}
)

target_link_directories(MyProject PRIVATE
        ${GTK4_LIBRARY_DIRS}
)

target_link_libraries(MyProject PRIVATE
        ${GTK4_LIBRARIES}
)

target_compile_options(MyProject PRIVATE
        ${GTK4_CFLAGS_OTHER}
)

# -----------------------------
# Windows GTK deployment
# -----------------------------
add_custom_target(dist
        COMMAND ${CMAKE_COMMAND} -E rm -rf
        "${CMAKE_BINARY_DIR}/dist"

        COMMAND ${CMAKE_COMMAND} -E make_directory
        "${CMAKE_BINARY_DIR}/dist"

        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:MyProject>"
        "${CMAKE_BINARY_DIR}/dist/MyProject.exe"

        COMMAND "C:/msys64/usr/bin/bash.exe"
        "${CMAKE_SOURCE_DIR}/make_dist.sh"
        "$<TARGET_FILE:MyProject>"
        "${CMAKE_BINARY_DIR}/dist"

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/msys64/ucrt64/share/glib-2.0"
        "${CMAKE_BINARY_DIR}/dist/share/glib-2.0"

        COMMENT "Creating portable MyProject distribution..."
)