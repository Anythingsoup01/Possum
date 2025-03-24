#pragma once

#include <vector>
#include <filesystem>
#include <unordered_map>

#include <imgui.h>

#include "Buffer.h"
#include "Possum/Core/Core.h"

namespace Possum
{


    struct FileData
    {
        std::string Title;
        std::string AltTitle;
        std::filesystem::path FilePath;

        bool IsUntitled = false;
        bool IsOpen = false;

        std::string Content;
        Buffer Buf = Buffer(s_MaxFileSize);

        ImGuiTabItemFlags Flag = ImGuiTabItemFlags_None;
    };

    class FileManager
    {
    public:
        FileManager() = default;
        ~FileManager() = default;

        void OpenFile(const std::filesystem::path filePath, const std::string data);

        void SaveFile(const std::filesystem::path& filePath, char* inData);

        void InsertFileToIndex(const std::string key, const FileData fileData);
        void RemoveFromFileIndex(const std::filesystem::path& key);

        FileData& GetFileDataAt(const std::filesystem::path& key);

        bool Exists(const std::string& key);

        std::unordered_map<std::string, FileData> GetAllFiles() const { return m_Files; }

    private:
        std::unordered_map<std::string, FileData> m_Files;
    };
}
