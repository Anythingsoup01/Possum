#pragma once

#include <ImGuiFileDialog.h>

#include "Ferret/Event/Event.h"
#include "Ferret/Event/KeyEvent.h"
#include "Ferret/Layer/Layer.h"

#include "Possum/Core/FileManager.h"

using namespace Possum;

namespace Ferret
{
    class PossumLayer : public Layer
    {
    public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;

        virtual void OnUpdate(float ts) override;
        virtual void OnUIRender() override;
        virtual void OnEvent(Event& event) override;

        void RenderWorkspace();
        void RenderFileTree();

        void RenderOpenFileDialog(bool& opened);
        void RenderSaveFileDialog(bool& opened);

        bool OnKeyPressedEvent(KeyPressedEvent& e);

        void NewFile();
        void OpenFile();

        void OpenFolder();

        void SaveFile();
        void SaveFileAs();

        static PossumLayer& Get() { return *s_Instance; }

    private:
        static PossumLayer* s_Instance;
        FileManager m_FileManager;
        std::string m_OpenedFileKey;

        bool m_IsOpenFile = false;
        bool m_IsSaveFile = false;

        ImGuiFileDialog m_OpenFileDialog;
        ImGuiFileDialog m_SaveFileDialog;

        std::unordered_map<std::string, char*> m_OpenedFiles;
    };
}
