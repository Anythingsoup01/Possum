#include "Ferret/Core/Application.h"
#include "Ferret/Core/Entrypoint.h"
#include "PossumLayer.h"
#include "imgui.h"

Ferret::PossumLayer* possumLayer = new Ferret::PossumLayer;

Ferret::Application* Ferret::CreateApplication(int argc, char** argv)
{
    Ferret::ApplicationSpecifications spec;
    spec.Title = "Ferret Example";

    Ferret::Application* app = new Ferret::Application(spec);

    app->PushLayer(possumLayer);
    app->SetMenubarCallback([app]()
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New File", "Ctrl+N"))
            {
                possumLayer->Get().NewFile();
            }
            if (ImGui::MenuItem("Open File", "Ctrl+O"))
            {
                possumLayer->Get().OpenFile();
            }
            if (ImGui::MenuItem("Open Folder", "Ctrl+Shift+O"))
            {
                possumLayer->Get().OpenFile();
            }
            if (ImGui::MenuItem("Save File", "Ctrl+S"))
            {
                possumLayer->Get().SaveFile();
            }
            if (ImGui::MenuItem("Save File As...", "Ctrl+Shift+S"))
            {
                possumLayer->Get().SaveFileAs();
            }
            if (ImGui::MenuItem("Exit"))
            {
                app->Close();
            }

            ImGui::EndMenu();
        }
    });

    return app;
}
