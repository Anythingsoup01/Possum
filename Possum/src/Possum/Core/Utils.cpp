#include "Utils.h"
#include "Ferret/Core/Log.h"

#include <fstream>
#include <sstream>

#include <Ferret/Core/Core.h>

namespace Possum
{
    std::string Utils::GetFileData(const std::filesystem::path& filePath)
    {
        std::string out;
        std::ifstream in(filePath);
        if (!in.is_open())
        {
            FE_CLI_ERROR("Could not open file!");
        }
        std::stringstream ss;
        ss << in.rdbuf();
        out = ss.str();
        return out;
    }
}
