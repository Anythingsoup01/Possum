#pragma once

#include <filesystem>

namespace Possum
{
    class Utils
    {
    public:
        static std::string GetFileData(const std::filesystem::path& filePath);
    };
}
