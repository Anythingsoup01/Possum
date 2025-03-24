cmake_minimum_required(VERSION 3.30.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(Ferret LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_C_FLAGS_DEBUG "-O0")

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_C_FLAGS_RELEASE "-O2")

add_subdirectory(vendor/ImGuiFileDialog)
add_subdirectory(vendor/prebuild)
add_subdirectory(vendor/stb)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glad)
add_subdirectory(PossumApp)
add_subdirectory(Possum)
add_subdirectory(Ferret)
add_subdirectory(vendor/glfw)
