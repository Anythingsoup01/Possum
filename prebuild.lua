workspace "Ferret"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

external "Ferret"
external "Possum"
external "PossumApp"

external "vendor/glfw"
external "vendor/glad"
external "vendor/imgui"
external "vendor/stb"
external "vendor/prebuild"
external "vendor/ImGuiFileDialog"
