project "PossumApp"
    language "C++"
    dialect "17"
    kind "ConsoleApp"

    files
    {
        "src/*.cpp",
        "src/*.h",
    }

    includedirs
    {
        "$(WORKSPACEDIR)/Ferret/src",
        "$(WORKSPACEDIR)/Possum/src",
        "$(WORKSPACEDIR)/vendor/glfw/include",
        "$(WORKSPACEDIR)/vendor/glad/include",
        "$(WORKSPACEDIR)/vendor/spdlog/include",
        "$(WORKSPACEDIR)/vendor/glm",
        "$(WORKSPACEDIR)/vendor/imgui",
        "$(WORKSPACEDIR)/vendor/ImGuiFileDialog",
    }

    links
    {
        "Ferret",
        "Possum",
    }

    filter "configurations:Debug"
        defines "FE_DEBUG"

    filter "configurations:Release"
        defines "FE_RELEASE"

