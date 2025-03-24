#include "Ferret/Core/Application.h"
#include "Ferret/Core/Entrypoint.h"
#include "FerretLayer.h"
#include "imgui.h"

Ferret::ExampleLayer* exampleLayer = new Ferret::ExampleLayer;

Ferret::Application* Ferret::CreateApplication(int argc, char** argv)
{
    Ferret::ApplicationSpecifications spec;
    spec.Title = "Ferret Example";

    Ferret::Application* app = new Ferret::Application(spec);

    app->PushLayer(exampleLayer);
    app->SetMenubarCallback([app]()
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Example"))
            {
                // Do static function here
                exampleLayer->LogExample();
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
