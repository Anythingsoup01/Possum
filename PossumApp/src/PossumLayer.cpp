#include "PossumLayer.h"
#include "Ferret.h"
#include "Ferret/Core/KeyCodes.h"
#include "imgui.h"

#include "Possum/Core/Utils.h"

#define MegaByte 1000000

static size_t s_MaxFileSize = (sizeof(char) * MegaByte) * 10;

namespace Ferret
{
    PossumLayer* PossumLayer::s_Instance = nullptr;

    void PossumLayer::OnAttach()
    {
        s_Instance = this;
    }

    void PossumLayer::OnDetach()
    {
        s_Instance = nullptr;
    }

    void PossumLayer::OnUpdate(float ts)
    {

    }


    void PossumLayer::OnUIRender()
    {
        RenderWorkspace();
        RenderFileTree();
        RenderOpenFileDialog(m_IsOpenFile);
        RenderSaveFileDialog(m_IsSaveFile);
    }

    void PossumLayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(PossumLayer::OnKeyPressedEvent));
    }

    void PossumLayer::RenderWorkspace()
    {
        ImGui::Begin("##Workspace");
        {
            ImGuiTabBarFlags tabBarFlags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll;
            if (ImGui::BeginTabBar("##TabBar", tabBarFlags))
            {
                ImVec2 size = ImGui::GetContentRegionAvail();
                for (auto& [key, fileData] : m_FileManager.GetAllFiles())
                {
                    std::string label = fileData.Title;
                    if (fileData.Buf[0] == 0)
                        fileData.Buf.Copy(fileData.Content.c_str());

                    if (ImGui::BeginTabItem(label.c_str(), &fileData.IsOpen, fileData.Flag))
                    {
                        m_OpenedFileKey = key;
                        if (ImGui::InputTextMultiline("##", fileData.Buf.GetData(), s_MaxFileSize, size, ImGuiInputTextFlags_AllowTabInput))
                        {
                            m_OpenedFiles.at(key) = fileData.Buf.GetData();
                        }
                        ImGui::EndTabItem();
                    }
                    else
                    {
                        fileData.Flag = ImGuiTabItemFlags_None;
                    }

                    if (!fileData.IsOpen)
                    {

                        FileData data = fileData;
                        Ferret::Application::Get().SubmitToMainThread([this, data]()
                        {
                            m_FileManager.RemoveFromFileIndex(data.FilePath);
                            m_OpenedFiles.erase(data.FilePath);
                        });
                    }
                }
                ImGui::EndTabBar();
            }
            ImGui::End();
        }
    }

    void PossumLayer::RenderFileTree()
    {
        ImGui::Begin("Files");
        {

            ImVec2 size = {ImGui::GetContentRegionAvail().x, 20 };
            for (auto& [key , data] : m_FileManager.GetAllFiles())
            {

                if(ImGui::Button(data.Title.c_str(), size))
                {
                    if (!m_OpenedFileKey.empty() && m_FileManager.Exists(m_OpenedFileKey))
                        m_FileManager.GetFileDataAt(m_OpenedFileKey).Flag = ImGuiTabItemFlags_None;
                    m_FileManager.GetFileDataAt(key).Flag = ImGuiTabItemFlags_SetSelected;
                }

            }

            ImGui::End();
        }
    }

    void PossumLayer::RenderOpenFileDialog(bool& opened)
    {
        if (opened)
        {
            if (ImGui::Begin("##OpenDialogCommand"))
            {
                std::stringstream ss;
                ss << "/home/";
                IGFD::FileDialogConfig config;config.path = ss.str();
                m_OpenFileDialog.OpenDialog("ChooseFileDlgKey", "Choose File", ".*", config);
            }
            ImGui::End();
            // display
            if (m_OpenFileDialog.Display("ChooseFileDlgKey", ImGuiWindowFlags_NoCollapse))
            { // => will show a dialog
                if (m_OpenFileDialog.IsOk())
                { // action if OK
                    std::string filePathName = m_OpenFileDialog.GetFilePathName();
                    // action
                    std::string data = Utils::GetFileData(filePathName);

                    if (!m_OpenedFileKey.empty() && m_FileManager.Exists(m_OpenedFileKey))
                        m_FileManager.GetFileDataAt(m_OpenedFileKey).Flag = ImGuiTabItemFlags_None;

                    m_FileManager.OpenFile(filePathName, data);
                    m_OpenedFiles.emplace(std::pair<std::string, char*>{filePathName, data.data()});
                }
                // close
                m_OpenFileDialog.Close();
                opened = false;
            }
        }
    }

    void PossumLayer::RenderSaveFileDialog(bool& opened)
    {
        if (opened)
        {
            if (ImGui::Begin("##SaveFileDialog"))
            {
                std::stringstream ss;
                ss << "/home/";
                IGFD::FileDialogConfig config;config.path = ss.str();
                m_SaveFileDialog.OpenDialog("SaveFileDlgKey", "Save File As...", nullptr, config);
                ImGui::End();
            }

            if(m_SaveFileDialog.Display("SaveFileDlgKey", ImGuiWindowFlags_NoCollapse))
            {
                if(m_SaveFileDialog.IsOk())
                {
                    std::string filePathName = m_SaveFileDialog.GetCurrentPath();
                }
                m_SaveFileDialog.Close();
                m_IsSaveFile = false;
            }
        }
    }

    bool PossumLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        bool ctrl = Input::IsKeyPressed(KeyCode::RightControl) || Input::IsKeyPressed(KeyCode::LeftControl);

        bool shift = Input::IsKeyPressed(KeyCode::RightShift) || Input::IsKeyPressed(KeyCode::LeftShift);

        bool alt = Input::IsKeyPressed(KeyCode::RightAlt) || Input::IsKeyPressed(KeyCode::LeftAlt);

        switch (e.GetKeyCode())
        {
            case KeyCode::N:
            {
                if (ctrl)
                    NewFile();
                break;
            }
            case KeyCode::O:
            {
                if (ctrl)
                {
                    if (shift)
                        OpenFolder();
                    else
                        OpenFile();
                    break;
                }
            }
            case KeyCode::S:
            {
                if (ctrl)
                {
                    if (shift)
                        SaveFileAs();
                    else
                        SaveFile();
                    break;
                }
            }
            default:
                break;
        }
        return false;
    }

    void PossumLayer::NewFile()
    {
        //m_FileManager.NewFile("Untitled");
        //m_OpenedFiles.emplace(std::pair<std::string, char*>("null", nullptr));
    }

    void PossumLayer::OpenFile()
    {
        m_IsOpenFile = true;
    }

    void PossumLayer::OpenFolder()
    {

    }

    void PossumLayer::SaveFile()
    {
        if (!m_OpenedFileKey.empty() && m_FileManager.Exists(m_OpenedFileKey))
            m_FileManager.SaveFile(m_OpenedFileKey, m_OpenedFiles.at(m_OpenedFileKey));
        else
           SaveFileAs();
    }

    void PossumLayer::SaveFileAs()
    {
         m_IsSaveFile = true;
    }


}
