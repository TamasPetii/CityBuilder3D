﻿#include "MyGui.h"
#include "../../Game/RoadNetwork.h";


void MyGui::Init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    Custom_Style();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void MyGui::Custom_Style()
{
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    style.GrabRounding = style.FrameRounding = 2.3f;

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        style.WindowMinSize = ImVec2(100, 100);
    }
}

void MyGui::Clean()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//------------------------------------------------------------|Non-static|------------------------------------------------------------//

MyGui::MyGui(Camera* camera) : m_Camera(camera) {}



void MyGui::Pre_Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void MyGui::Post_Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void MyGui::DockSpace()
{
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpace Demo", nullptr, window_flags);
  
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    DockSpace_MenuBar();

    ImGui::End();
}

void MyGui::DockSpace_MenuBar()
{
    if (ImGui::BeginMenuBar())
    {

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Game"))
            {
                m_NewGameLayout.show = true;
            }
            if (ImGui::MenuItem("Load Game"))
            {
                m_LoadGameLayout.show = true;
            }
            if (ImGui::MenuItem("Save Game"))
            {
                m_SaveGameLayout.show = true;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Options"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    NewGame_Window();
    LoadGame_Window();
    SaveGame_Window();

}

void MyGui::NewGame_Window()
{
    if (m_NewGameLayout.show)
    {
        ImGui::OpenPopup("New Game");
    }

    if (ImGui::BeginPopupModal("New Game", nullptr, ImGuiWindowFlags_NoResize))
    {
        ImGui::SetWindowSize(ImVec2(300, 127));

        //[New Game] : City Name Text Input
        ImGui::Text("City Name: ");
        ImGui::SameLine();
        ImGui::InputText("##city_name", m_NewGameLayout.name, 64);

        //[New Game] : City Size Slider 
        ImGui::Text("City Size: ");
        ImGui::SameLine();
        ImGui::SliderInt("##city_size", &m_NewGameLayout.size, 25, 50);

        //[New Game] : City Time Slider 
        ImGui::Text("City Time: ");
        ImGui::SameLine();
        ImGui::SliderInt("##city_time", &m_NewGameLayout.time, 0, 2);

        ImGui::Separator();

        //[New Game] : Okay Button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.75, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0.7, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.65, 0, 1));
        if (ImGui::Button("Okay", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); m_NewGameLayout.show = false; m_NewGameLayout.effect = true; }
        ImGui::SetItemDefaultFocus();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        //[New Game] : Cancel Button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8, 0, 0, 1));
        ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - 120);
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); m_NewGameLayout.show = false; }
        ImGui::PopStyleColor(3);

        ImGui::EndPopup();
    }
}

void MyGui::LoadGame_Window()
{
    if (m_LoadGameLayout.show)
    {
        ImGui::OpenPopup("Load Game");
    }

    if (file_dialog.showFileDialog("Load Game", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), m_LoadGameLayout.extension))
    {
        m_LoadGameLayout.name = file_dialog.selected_fn;
        m_LoadGameLayout.path = file_dialog.selected_path;
        m_LoadGameLayout.effect = true;
    }

    if (file_dialog.close) 
    {
        m_LoadGameLayout.show = false;
        file_dialog.close = false;
    }

}

void MyGui::SaveGame_Window()
{
    if (m_SaveGameLayout.show)
    {
        ImGui::OpenPopup("Save Game");
    }

    if (file_dialog.showFileDialog("Save Game", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), m_SaveGameLayout.extension))
    {
        m_SaveGameLayout.name = file_dialog.selected_fn;
        m_SaveGameLayout.path = file_dialog.selected_path;
        m_SaveGameLayout.effect = true;
    }

    if (file_dialog.close)
    {
        m_SaveGameLayout.show = false;
        file_dialog.close = false;
    }
}

void MyGui::ViewPort_Render(FrameBuffer* fbo)
{
    ImGui::Begin("ViewPort", nullptr, ImGuiWindowFlags_NoCollapse);

    Camera_MouseClickEvent();
    Camera_KeyboardKeyEvent();
    Build_MouseClickEvent();
    Build_KeyboardKeyEvent();

    ImVec2 size = ImGui::GetContentRegionAvail();

    ImGui::Image((void*)fbo->Get_TextureId(), size, ImVec2(0, 1), ImVec2(1, 0));

    if (size.x != m_ViewPort_Width || size.y != m_ViewPort_Height)
    {
        fbo->Resize((int)size.x, (int)size.y);
    }

    m_ViewPort_Width = (int)size.x;
    m_ViewPort_Height = (int)size.y;

    ImGui::End();
}

void MyGui::Demo_Window()
{
    ImGui::ShowDemoWindow();
}

void MyGui::GameDetails_Window()
{
    ImGui::Begin("Game Details");
    std::string str = RoadNetwork::NetworksToString();
    const char* cstr = str.c_str();
    ImGui::Text("%s", cstr);
    ImGui::End();
}

void MyGui::GameOptions_Window()
{
    ImGui::Begin("Game options");

    ImGui::SeparatorText("Residence Tax");

    ImGui::Text("LVL1: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##residence_lvl1", &m_TaxLayout.ResidenceTaxLvl1, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::Text("LVL2: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##residence_lvl2", &m_TaxLayout.ResidenceTaxLvl2, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::Text("LVL3: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##residence_lvl3", &m_TaxLayout.ResidenceTaxLvl3, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::SeparatorText("Service Tax");

    ImGui::Text("LVL1: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##service_lvl1", &m_TaxLayout.ServiceTaxLvl1, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::Text("LVL2: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##service_lvl2", &m_TaxLayout.ServiceTaxLvl2, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::Text("LVL3: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##service_lvl3", &m_TaxLayout.ServiceTaxLvl3, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::SeparatorText("Industrial Tax");

    ImGui::Text("LVL1: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##industrial_lvl1", &m_TaxLayout.IndustrialTaxLvl1, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::Text("LVL2: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##industrial_lvl2", &m_TaxLayout.IndustrialTaxLvl2, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::Text("LVL3: ");
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, 0.0f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_TaxLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, (255 - (m_TaxLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));

    if (ImGui::SliderFloat("##industrial_lvl3", &m_TaxLayout.IndustrialTaxLvl3, 0, 100))
        m_TaxLayout.effect = true;

    ImGui::PopStyleColor(5);

    ImGui::End();
}

void MyGui::RenderOptions_Window()
{
    ImGui::Begin("Render options");

    ImGui::SeparatorText("Light properties");

    ImGui::Text("Direction: ");
    ImGui::SameLine();

    if (ImGui::SliderFloat3("##light_direction", &m_LightsLayout.lightDir.x, -1, 1, "%.3f", 0))
        m_LightsLayout.effect = true;

    ImGui::Text("Shininess: ");
    ImGui::SameLine();

    //if (ImGui::SliderInt("##shininess", &m_LightsLayout.specularPow, 0, 100, "%d", 0))
    //    m_LightsLayout.effect = true;

    if (ImGui::InputInt("##shininess", &m_LightsLayout.specularPow, 1, 100, 0))
        m_LightsLayout.effect = true;

    ImGui::Text("La: ");
    ImGui::SameLine();

    if (ImGui::SliderFloat3("##la", &m_LightsLayout.La.x, 0, 1, "%.3f", 0))
        m_LightsLayout.effect = true;

    ImGui::Text("Ld: ");
    ImGui::SameLine();

    if (ImGui::SliderFloat3("##ld", &m_LightsLayout.Ld.x, 0, 1, "%.3f", 0))
        m_LightsLayout.effect = true;

    ImGui::Text("Ls: ");
    ImGui::SameLine();

    if (ImGui::SliderFloat3("##ls", &m_LightsLayout.Ls.x, 0, 1, "%.3f", 0))
        m_LightsLayout.effect = true;

    ImGui::Text("Ka: ");
    ImGui::SameLine();

    if (ImGui::SliderFloat3("##ka", &m_LightsLayout.Ka.x, 0, 1, "%.3f", 0))
        m_LightsLayout.effect = true;

    ImGui::Text("Kd: ");
    ImGui::SameLine();

    if (ImGui::SliderFloat3("##kd", &m_LightsLayout.Kd.x, 0, 1, "%.3f", 0))
        m_LightsLayout.effect = true;

    ImGui::Text("Ks: ");
    ImGui::SameLine();

    if (ImGui::SliderFloat3("##ks", &m_LightsLayout.Ks.x, 0, 1, "%.3f", 0))
        m_LightsLayout.effect = true;

    if (ImGui::Button("Reset"))
    {
        m_LightsLayout.reset = true;
    }


    ImGui::End();
}

//---------------------------------------------------------|EVENTS|---------------------------------------------------------//
//---------------------------------------------------------|EVENTS|---------------------------------------------------------//
//---------------------------------------------------------|EVENTS|---------------------------------------------------------//

void MyGui::Build_MouseClickEvent()
{

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        BuildHover = true;
        hit = false;
    }

    if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
    {
        hit = true;
        BuildHover = false;
    }

    if (ImGui::IsWindowHovered() && BuildHover)
    {
        int RelativWindowCursor_X = (int)(ImGui::GetMousePos().x - ImGui::GetWindowPos().x);
        int RelativWindowCursor_Y = (int)(ImGui::GetMousePos().y - ImGui::GetWindowPos().y);

        ImVec2 CurrentContent_MIN = ImGui::GetWindowContentRegionMin();
        ImVec2 CurrentContent_MAX = ImGui::GetWindowContentRegionMax();

        bool CursorInContentAreaMin_X = RelativWindowCursor_X >= CurrentContent_MIN.x && RelativWindowCursor_Y >= CurrentContent_MIN.y;
        bool CursorInContentAreaMax_Y = RelativWindowCursor_X <= CurrentContent_MAX.x && RelativWindowCursor_Y <= CurrentContent_MAX.y;

        if (CursorInContentAreaMin_X && CursorInContentAreaMax_Y)
        {
            mouse_x = RelativWindowCursor_X - (int)ImGui::GetWindowContentRegionMin().x;
            mouse_y = RelativWindowCursor_Y - (int)ImGui::GetWindowContentRegionMin().y;
            content_size.x = CurrentContent_MAX.x - CurrentContent_MIN.x;
            content_size.y = CurrentContent_MAX.y - CurrentContent_MIN.y;
            //std::cout << "Hitting content area: " << "{x = " << RelativWindowCursor_X - ImGui::GetWindowContentRegionMin().x << "} | {y = } " << RelativWindowCursor_Y - ImGui::GetWindowContentRegionMin().y << "}" << std::endl;
        }
    }
}

void MyGui::Build_Window()
{
    ImGui::Begin("Build");

    ImGui::SeparatorText("General");
    ImGui::RadioButton("Empty", &m_BuildLayout.building, 9);
    ImGui::RadioButton("Road", &m_BuildLayout.building, 10);
    ImGui::RadioButton("Forest", &m_BuildLayout.building, 11);
    ImGui::SeparatorText("Zone");
    ImGui::RadioButton("Residence_LVL1", &m_BuildLayout.building, 0);
    ImGui::RadioButton("Residence_LVL2", &m_BuildLayout.building, 1);
    ImGui::RadioButton("Residence_LVL3", &m_BuildLayout.building, 2);
    ImGui::RadioButton("Industry_LVL1", &m_BuildLayout.building, 3);
    ImGui::RadioButton("Industry_LVL2", &m_BuildLayout.building, 4);
    ImGui::RadioButton("Industry_LVL3", &m_BuildLayout.building, 5);
    ImGui::RadioButton("Service_LVL1", &m_BuildLayout.building, 6);
    ImGui::RadioButton("Service_LVL2", &m_BuildLayout.building, 7);
    ImGui::RadioButton("Service_LVL3", &m_BuildLayout.building, 8);
    ImGui::SeparatorText("Buildings");
    ImGui::RadioButton("FireStation", &m_BuildLayout.building, 13);
    ImGui::RadioButton("PoliceStation", &m_BuildLayout.building, 12);
    ImGui::RadioButton("Stadion", &m_BuildLayout.building, 16);
    ImGui::RadioButton("HighSchool", &m_BuildLayout.building, 14);
    ImGui::RadioButton("University", &m_BuildLayout.building, 15);
    ImGui::RadioButton("PowerStation", &m_BuildLayout.building, 17);
    ImGui::RadioButton("PowerWire", &m_BuildLayout.building, 18);
    ImGui::End();
}

void MyGui::Build_KeyboardKeyEvent()
{
    if (ImGui::IsKeyPressed(ImGuiKey_R))
    {
        r++;
    }
}

void MyGui::Camera_MouseClickEvent()
{
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        m_Camera->Mouse_ClickEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    }
    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
    {
        m_Camera->Mouse_ClickEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
    }
    if (ImGui::IsWindowHovered())
    {
        m_Camera->Mouse_MoveEvent(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    }
}

void MyGui::Camera_KeyboardKeyEvent()
{
    //W
    if (ImGui::IsKeyPressed(ImGuiKey_W))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_W, 0, GLFW_PRESS, 0);
    }
    if (ImGui::IsKeyReleased(ImGuiKey_W))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_W, 0, GLFW_RELEASE, 0);
    }

    //S
    if (ImGui::IsKeyPressed(ImGuiKey_S))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_S, 0, GLFW_PRESS, 0);
    }
    if (ImGui::IsKeyReleased(ImGuiKey_S))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_S, 0, GLFW_RELEASE, 0);
    }

    //A
    if (ImGui::IsKeyPressed(ImGuiKey_A))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_A, 0, GLFW_PRESS, 0);
    }
    if (ImGui::IsKeyReleased(ImGuiKey_A))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_A, 0, GLFW_RELEASE, 0);
    }

    //D
    if (ImGui::IsKeyPressed(ImGuiKey_D))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_D, 0, GLFW_PRESS, 0);
    }
    if (ImGui::IsKeyReleased(ImGuiKey_D))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_D, 0, GLFW_RELEASE, 0);
    }
}