project "Possum"
    kind "StaticLib"
    language "C++"
    dialect "17"

    files
    {
        "src/*.cpp",
        "src/*.h",
    }

    includedirs
    {
        "src",
        "$(WORKSPACEDIR)/Ferret/src",
        "$(WORKSPACEDIR)/vendor/imgui",
        "$(WORKSPACEDIR)/vendor/spdlog/include",
    }

    links
    {
        "Ferret",
    }
