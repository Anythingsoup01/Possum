set(SRCS
    ImGuiFileDialog.cpp
    ImGuiFileDialog.h
    ImGuiFileDialogConfig.h
)
add_library(ImGuiFileDialog STATIC ${SRCS})
set_property(TARGET ImGuiFileDialog PROPERTY CXX_STANDARD 17)

target_include_directories(ImGuiFileDialog PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/imgui
    ${CMAKE_SOURCE_DIR}/vendor/stb
)

