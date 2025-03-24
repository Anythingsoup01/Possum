#include "FileManager.h"

#include <fstream>

#include "Ferret/Core/Log.h"

#include "Utils.h"

namespace Possum
{
    void FileManager::OpenFile(const std::filesystem::path filePath, std::string data)
    {
        std::string fileName = filePath.filename().string();
        std::string filePathString = filePath.string();

        for (auto& [key, fileData] : m_Files)
        {
            if (key == filePathString)
            {
                FE_CLI_WARN("File is already open!");
                return;
            }
        }

        FileData fileData;
        fileData.Title = fileName;
        // TODO: Get the previous folder and append the file name to it;
        fileData.AltTitle = filePathString;
        fileData.FilePath = filePath;
        fileData.IsUntitled = false;
        fileData.Content = data;
        fileData.Buf.Copy(data.c_str());
        fileData.IsOpen = true;

        InsertFileToIndex(filePathString, fileData);
    }

    void FileManager::SaveFile(const std::filesystem::path& filePath, char* inData)
    {
        FileData& fileData = GetFileDataAt(filePath.string());

        std::string saveData(inData);
        std::ofstream out(filePath);
        if (!out.is_open())
        {
            FE_CLI_CRITICAL("Could not save file!");
            return;
        }
        out << saveData;
        out.close();
    }

    void FileManager::InsertFileToIndex(const std::string key, const FileData fileData)
    {
        m_Files.emplace(std::pair<std::string, FileData>(key, fileData));
    }

    void FileManager::RemoveFromFileIndex(const std::filesystem::path& key)
    {
        GetFileDataAt(key).Buf.FreeBuffer();
        m_Files.erase(key.string());
    }

    FileData& FileManager::GetFileDataAt(const std::filesystem::path& key)
    {
        return m_Files.at(key.string());
    }

    bool FileManager::Exists(const std::string& key)
    {
        for (auto& [storedKey, data] : m_Files)
        {
            if (key == storedKey)
                return true;
        }
        return false;
    }
}
