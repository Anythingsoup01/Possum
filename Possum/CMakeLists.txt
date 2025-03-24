set(SRCS
    src/Possum/Core/FileManager.cpp
    src/Possum/Core/Utils.cpp
    src/Possum/Core/Buffer.h
    src/Possum/Core/Utils.h
    src/Possum/Core/FileManager.h
)
add_library(Possum STATIC ${SRCS})
set_property(TARGET Possum PROPERTY CXX_STANDARD 17)

target_include_directories(Possum PRIVATE
    src
    ${CMAKE_SOURCE_DIR}/Ferret/src
    ${CMAKE_SOURCE_DIR}/vendor/imgui
    ${CMAKE_SOURCE_DIR}/vendor/spdlog/include
)

target_link_libraries(Possum
    Ferret
)

