set(SRCS
    src/PossumLayer.cpp
    src/FerretApp.cpp
    src/PossumLayer.h
)
add_executable(PossumApp ${SRCS})
set_property(TARGET PossumApp PROPERTY CXX_STANDARD 17)

target_include_directories(PossumApp PRIVATE
    ${CMAKE_SOURCE_DIR}/Ferret/src
    ${CMAKE_SOURCE_DIR}/Possum/src
    ${CMAKE_SOURCE_DIR}/vendor/glfw/include
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/vendor/glm
    ${CMAKE_SOURCE_DIR}/vendor/imgui
    ${CMAKE_SOURCE_DIR}/vendor/ImGuiFileDialog
)

target_link_libraries(PossumApp
    Ferret
    Possum
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
target_compile_definitions(PossumApp
PUBLIC
    FE_DEBUG
)
endif(CMAKE_BUILD_TYPE STREQUAL Debug)
if(CMAKE_BUILD_TYPE STREQUAL Release)
target_compile_definitions(PossumApp
PUBLIC
    FE_RELEASE
)
endif(CMAKE_BUILD_TYPE STREQUAL Release)
