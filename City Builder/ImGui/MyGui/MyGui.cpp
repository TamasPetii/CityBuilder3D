#include "MyGui.h"

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
    style.GrabRounding = style.FrameRounding = 2.f;
    style.FramePadding = ImVec2(2, 2);
    
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        style.WindowMinSize = ImVec2(50, 50);
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
    ViewPortWindow();
    GameWindow();
    RenderWindow();
    LogWindow();
    BuildWindow();
    DetailsWindow();
    Upgrade_Popup();

    ImGui::End();
}

//|MENU-BAR|---------------------------------------------------------------------------------------------------------------------//
//|MENU-BAR|---------------------------------------------------------------------------------------------------------------------//
//|MENU-BAR|---------------------------------------------------------------------------------------------------------------------//

void MyGui::DockSpace_MenuBar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Game"))
            {
                m_MenuBarLayout.NewGame_Show = true;
            }
            if (ImGui::MenuItem("Load Game"))
            {
                m_MenuBarLayout.LoadGame_Show = true;
            }
            if (ImGui::MenuItem("Save Game"))
            {
                m_MenuBarLayout.SaveGame_Show = true;
            }
            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Demo"))
        {
            m_MenuBarLayout.ImGuiDemo_Show = true;
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Info"))
        {
            
            m_MenuBarLayout.Info_Show = true;
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    NewGame_Popup();
    LoadGame_Popup();
    SaveGame_Popup();
    InfoGame_Popup();
    //ImGui::ShowDemoWindow(&m_MenuBarLayout.ImGuiDemo_Show);
}

void MyGui::NewGame_Popup()
{
    if (m_MenuBarLayout.NewGame_Show)
    {
        ImGui::OpenPopup("New Game");
    }

    if (ImGui::BeginPopupModal("New Game", nullptr, ImGuiWindowFlags_NoResize))
    {
        ImGui::SetWindowSize(ImVec2(300, 127));

        //[New Game] : City Name Text Input
        ImGui::Text("City Name: ");
        ImGui::SameLine();
        ImGui::InputText("##city_name", m_MenuBarLayout.City_Name, 64);

        //[New Game] : City Size Slider 
        ImGui::Text("City Size: ");
        ImGui::SameLine();
        ImGui::SliderInt("##city_size", &m_MenuBarLayout.City_Size, 25, 50);

        //[New Game] : City Time Slider 
        ImGui::Text("City Time: ");
        ImGui::SameLine();
        ImGui::SliderFloat("##city_time", &m_MenuBarLayout.City_Time, 0.05, 2);

        ImGui::Separator();

        //[New Game] : Okay Button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.75, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0.7, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.65, 0, 1));
        if (ImGui::Button("Okay", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); m_MenuBarLayout.NewGame_Show = false; m_MenuBarLayout.NewGame_Effect = true; }
        ImGui::SetItemDefaultFocus();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        //[New Game] : Cancel Button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8, 0, 0, 1));
        ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - 120);
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); m_MenuBarLayout.NewGame_Show = false; }
        ImGui::PopStyleColor(3);

        ImGui::EndPopup();
    }
}

void MyGui::LoadGame_Popup()
{
    if (m_MenuBarLayout.LoadGame_Show)
    {
        ImGui::OpenPopup("Load Game");
    }

    if (file_dialog.showFileDialog("Load Game", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), m_MenuBarLayout.LoadFile_Extension))
    {
        m_MenuBarLayout.LoadFile_Name = file_dialog.selected_fn;
        m_MenuBarLayout.LoadFile_Path = file_dialog.selected_path;
        m_MenuBarLayout.LoadGame_Effect = true;
    }

    if (file_dialog.close) 
    {
        m_MenuBarLayout.LoadGame_Show = false;
        file_dialog.close = false;
    }

}

void MyGui::SaveGame_Popup()
{
    if (m_MenuBarLayout.SaveGame_Show)
    {
        ImGui::OpenPopup("Save Game");
    }

    if (file_dialog.showFileDialog("Save Game", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), m_MenuBarLayout.SaveFile_Extension))
    {
        m_MenuBarLayout.SaveFile_Name = file_dialog.selected_fn;
        m_MenuBarLayout.SaveFile_Path = file_dialog.selected_path;
        m_MenuBarLayout.SaveGame_Effect = true;
    }

    if (file_dialog.close)
    {
        m_MenuBarLayout.SaveGame_Show = false;
        file_dialog.close = false;
    }
}

void MyGui::InfoGame_Popup()
{

}

//|GAME-WINDOW|---------------------------------------------------------------------------------------------------------------------//
//|GAME-WINDOW|---------------------------------------------------------------------------------------------------------------------//
//|GAME-WINDOW|---------------------------------------------------------------------------------------------------------------------//

void MyGui::GameWindow()
{
    ImGui::Begin("Game >> (Options/Details)");
    GameWindow_General();
    GameWindow_Time();
    GameWindow_Catastrophe();
    GameWindow_Tax();
    ImGui::End();
}

void MyGui::GameWindow_General()
{
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
    if (ImGui::CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("General-Table", 2, table_flags))
        {
            //1 RAW: MONEY
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Money:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::Text("%d", m_GameWindowLayout.City_Money);

            //2 RAW: SATISFACTION
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Satifaction:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::Text("%d", m_GameWindowLayout.City_Satisfaction);

            ImGui::EndTable();
        }

    }
}
void MyGui::GameWindow_Time()
{
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
    if (ImGui::CollapsingHeader("Time", ImGuiTreeNodeFlags_DefaultOpen))
    {

        if (ImGui::BeginTable("Time-Table", 2, table_flags))
        {
            //1 RAW: TICK TIME
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Tick (sec):");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if(ImGui::SliderFloat("##city-tick", &m_GameWindowLayout.Time_Tick, 0.05, 2)) m_GameWindowLayout.Time_Effect = true;

            //2 RAW: GAME TIME
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Time (game):");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::Text(m_GameWindowLayout.Time_Game.c_str());

            //3 RAW: REAL TIME
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Time (real):");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::Text("%f", m_GameWindowLayout.Time_Real);

            ImGui::EndTable();
        }
    }
}

void MyGui::GameWindow_Catastrophe()
{
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
    if (ImGui::CollapsingHeader("Catastrophe", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("Meteor-Table", 2, table_flags))
        {
            //1 RAW: Meteor Count
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Meteor:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::SliderInt("##meteor-count", &m_GameWindowLayout.Catastrophe_Count, 0, 2500);

            //2 RAW: Meteor Count
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Shoot:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if(ImGui::Button("Start")) m_GameWindowLayout.Catastrophe_Effect = true;

            ImGui::EndTable();
        }
    }
}

void MyGui::GameWindow_Tax()
{
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
    if (ImGui::CollapsingHeader("Tax", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::SeparatorText("Residence");
        if (ImGui::BeginTable("Tax-Table-Residence", 2, table_flags))
        {
            //1 RAW: Residence LvL1
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 1:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##residence_lvl1", &m_GameWindowLayout.ResidenceTaxLvl1, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            //2 RAW: Residence LvL2
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 2:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##residence_lvl2", &m_GameWindowLayout.ResidenceTaxLvl2, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            //3 RAW: Residence LvL3
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 3:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ResidenceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##residence_lvl3", &m_GameWindowLayout.ResidenceTaxLvl3, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            ImGui::EndTable();
        }

        ImGui::SeparatorText("Service");
        if (ImGui::BeginTable("Tax-Table-Service", 2, table_flags))
        {
            //1 RAW: Industry LvL1
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 1:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##service_lvl1", &m_GameWindowLayout.ServiceTaxLvl1, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            //2 RAW: Industry LvL2
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 2:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##service_lvl2", &m_GameWindowLayout.ServiceTaxLvl2, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            //3 RAW: Industry LvL3
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 3:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.ServiceTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##service_lvl3", &m_GameWindowLayout.ServiceTaxLvl3, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            ImGui::EndTable();
        }

        ImGui::SeparatorText("Industry");
        if (ImGui::BeginTable("Tax-Table-Industry", 2, table_flags))
        {
            //1 RAW: Industry LvL1
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 1:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl1 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##industry_lvl1", &m_GameWindowLayout.IndustrialTaxLvl1, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            //2 RAW: Industry LvL2
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 2:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl2 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##industry_lvl2", &m_GameWindowLayout.IndustrialTaxLvl2, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            //3 RAW: Industry LvL3
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("LvL - 3:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, 0.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4((0 + (m_GameWindowLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, (255 - (m_GameWindowLayout.IndustrialTaxLvl3 * 2.55)) / 255.0f, 0.0f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
            if (ImGui::SliderFloat("##industry_lvl3", &m_GameWindowLayout.IndustrialTaxLvl3, 0, 100)) m_GameWindowLayout.Tax_Effect = true;
            ImGui::PopStyleColor(5);

            ImGui::EndTable();
        }
    }
}

//|RENDER-WINDOW|---------------------------------------------------------------------------------------------------------------------//
//|RENDER-WINDOW|---------------------------------------------------------------------------------------------------------------------//
//|RENDER-WINDOW|---------------------------------------------------------------------------------------------------------------------//

void MyGui::RenderWindow()
{
    ImGui::Begin("Render >> (Options/Details)");

    RenderWindow_Frame();
    RenderWindow_Camera();
    RenderWindow_Objects();
    RenderWindow_Lights();

    if (m_RenderWindowLayout.Camera_Mode == 2 && m_RenderWindowLayout.Camera_Show3D) RenderWindow_CameraPopup3D();
    if (m_RenderWindowLayout.Camera_Mode != 2 && m_RenderWindowLayout.Camera_Show2D) RenderWindow_CameraPopup2D();

    ImGui::End();
}

void MyGui::RenderWindow_Frame()
{
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
    if (ImGui::CollapsingHeader("Frame", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("Frame Table", 2, table_flags))
        {
            //1 RAW: FPS LOCK
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Frame Lock:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::Checkbox("##frame-lock", &m_RenderWindowLayout.Frame_Lock))
            {
                glfwSwapInterval(m_RenderWindowLayout.Frame_Lock);
            }

            //2 RAW: FPS
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Frame:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::Text("%d", m_RenderWindowLayout.Frame_Fps);

            //3 RAW: Time
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Time (ms):");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::Text("%f", m_RenderWindowLayout.Frame_Time);

            ImGui::EndTable();
        }
    }
}
void MyGui::RenderWindow_Camera()
{
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
    if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("Camera Table", 2, table_flags))
        {
            //1 RAW: CAMERA DIMENSION MODE
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Mode:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::Combo("##dimension:", &m_RenderWindowLayout.Camera_Mode, m_RenderWindowLayout.Camera_Modes, IM_ARRAYSIZE(m_RenderWindowLayout.Camera_Modes)))
            {
                m_RenderWindowLayout.Camera_Effect = true;
                m_RenderWindowLayout.Camera_Show = true;
            }

            //2 RAW: CAMERA SPEED
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Speed:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if(ImGui::SliderFloat("##camera-speed", &m_RenderWindowLayout.Camera_Speed, 5, 20)) m_RenderWindowLayout.Camera_Effect = true;

            //3 RAW: CAMERA POSITON
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Position:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            ImGui::Text("(%.1f,%.1f,%.1f)", m_RenderWindowLayout.Camera_Position.x, m_RenderWindowLayout.Camera_Position.y, m_RenderWindowLayout.Camera_Position.z);

            ImGui::EndTable();
        }
    }
}

void MyGui::RenderWindow_CameraPopup2D()
{
    if (m_RenderWindowLayout.Camera_Show)
    {
        ImGui::OpenPopup("Game Dimension 2D / 2.5D");
    }

    if (ImGui::BeginPopupModal("Game Dimension 2D / 2.5D", nullptr, ImGuiWindowFlags_NoResize))
    {
        ImGui::SetWindowSize(ImVec2(300, 270));

        //[New Game] : City Name Text Input
        ImGui::SeparatorText("Keyboard events");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "W >> Moving FRONT");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "S >> Moving BACK");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "A >> Moving LEFT");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "D >> Moving RIGHT");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "L_SHIFT >> Moving DOWN");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "L_CTRL >> Moving UP");

        ImGui::SeparatorText("Mouse events");
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "LEFT CLICK >> DEACTIVATED");
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "RIGHT CLICK >> BUILD");

        ImGui::Separator();
        ImGui::Checkbox("Ask me next time", &m_RenderWindowLayout.Camera_Ask);
        ImGui::Separator();

        //[New Game] : Okay Button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.75, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0.7, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.65, 0, 1));
        if (ImGui::Button("Okay", ImVec2(282, 0)))
        {
            ImGui::CloseCurrentPopup();
            m_RenderWindowLayout.Camera_Show = false;
            m_RenderWindowLayout.Camera_Show2D = m_RenderWindowLayout.Camera_Ask;
            m_RenderWindowLayout.Camera_Ask = true;
        }
        ImGui::SetItemDefaultFocus();
        ImGui::PopStyleColor(3);

        ImGui::EndPopup();
    }
}

void MyGui::RenderWindow_CameraPopup3D()
{
    if (m_RenderWindowLayout.Camera_Show)
    {
        ImGui::OpenPopup("Game Dimension 3D");
    }

    if (ImGui::BeginPopupModal("Game Dimension 3D", nullptr, ImGuiWindowFlags_NoResize))
    {
        ImGui::SetWindowSize(ImVec2(300, 235));

        //[New Game] : City Name Text Input
        ImGui::SeparatorText("Keyboard events");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "W >> Moving FRONT");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "S >> Moving BACK");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "A >> Moving LEFT");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "D >> Moving RIGHT");

        ImGui::SeparatorText("Mouse events");
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "LEFT CLICK >> ROTATE");
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "RIGHT CLICK >> BUILD");

        ImGui::Separator();
        ImGui::Checkbox("Ask me next time", &m_RenderWindowLayout.Camera_Ask);
        ImGui::Separator();

        //[New Game] : Okay Button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.75, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0.7, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.65, 0, 1));
        if (ImGui::Button("Okay", ImVec2(282, 0)))
        {
            ImGui::CloseCurrentPopup();
            m_RenderWindowLayout.Camera_Show = false;
            m_RenderWindowLayout.Camera_Show3D = m_RenderWindowLayout.Camera_Ask;
            m_RenderWindowLayout.Camera_Ask = true;
        }
        ImGui::SetItemDefaultFocus();
        ImGui::PopStyleColor(3);

        ImGui::EndPopup();
    }
}

void MyGui::RenderWindow_Objects()
{
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
    if (ImGui::CollapsingHeader("Objects", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("Objects Table", 2, table_flags))
        {
            for (int i = 0; i < 5; i++)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Tree:");
                ImGui::TableNextColumn();
                ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
                ImGui::Text("%d", 5);
            }

            ImGui::EndTable();
        }
    }
}

void MyGui::RenderWindow_Lights()
{
    ImGuiTableFlags table_flags = ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersH;
    if (ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("Lights Table", 2, table_flags))
        {
            //1 RAW: Direction
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Direction:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::SliderFloat3("##light_direction", &m_RenderWindowLayout.Lights_Direction.x, -1, 1, "%.2f", 0))
                m_RenderWindowLayout.Lights_Effect = true;

            //2 RAW: Shininess
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Shininess:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::SliderInt("##shininess", &m_RenderWindowLayout.Lights_SpecularPow, 1, 100, "%d", 0))
                m_RenderWindowLayout.Lights_Effect = true;

            //3 RAW: LA
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("La:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::SliderFloat3("##la", &m_RenderWindowLayout.La.x, 0, 1, "%.1f", 0))
                m_RenderWindowLayout.Lights_Effect = true;

            //4 RAW: LD
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Ld:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::SliderFloat3("##ld", &m_RenderWindowLayout.Ld.x, 0, 1, "%.1f", 0))
                m_RenderWindowLayout.Lights_Effect = true;

            //4 RAW: Ls
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Ls:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::SliderFloat3("##ls", &m_RenderWindowLayout.Ls.x, 0, 1, "%.1f", 0))
                m_RenderWindowLayout.Lights_Effect = true;

            //5 RAW: Ka
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Ka:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::SliderFloat3("##ka", &m_RenderWindowLayout.Ka.x, 0, 1, "%.1f", 0))
                m_RenderWindowLayout.Lights_Effect = true;

            //6 RAW: Kd
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Kd:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::SliderFloat3("##kd", &m_RenderWindowLayout.Kd.x, 0, 1, "%.1f", 0))
                m_RenderWindowLayout.Lights_Effect = true;

            //7 RAW: Ks
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Ks:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::SliderFloat3("##ks", &m_RenderWindowLayout.Ks.x, 0, 1, "%.1f", 0))
                m_RenderWindowLayout.Lights_Effect = true;

            //8 RAW: RESET
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Reset:");
            ImGui::TableNextColumn();
            ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
            if (ImGui::Button("Reset", ImVec2(ImGui::GetColumnWidth(), 0)))
            {
                m_RenderWindowLayout.Lights_Effect = true;
                m_RenderWindowLayout.Lights_Reset = true;
            }

            ImGui::EndTable();
        }
    }
}

//|LOG-WINDOW|---------------------------------------------------------------------------------------------------------------------//
//|LOG-WINDOW|---------------------------------------------------------------------------------------------------------------------//
//|LOG-WINDOW|---------------------------------------------------------------------------------------------------------------------//

void MyGui::LogWindow()
{
    //TODO: TABLE FORMAT???
    ImGui::Begin("Build-Log");
    ImGui::TextUnformatted(m_LogWindowLayout.build_log.c_str());
    ImGui::End();

    ImGui::Begin("Citizen-Log");
    ImGui::TextUnformatted(m_LogWindowLayout.citizen_log.c_str());
    ImGui::End();

    ImGui::Begin("Money-Log");
    ImGui::TextUnformatted(m_LogWindowLayout.money_log.c_str());
    ImGui::End();
}

//|BUILD-WINDOW|---------------------------------------------------------------------------------------------------------------------//
//|BUILD-WINDOW|---------------------------------------------------------------------------------------------------------------------//
//|BUILD-WINDOW|---------------------------------------------------------------------------------------------------------------------//

ImVec2 MyGui::Get_UV(int index, int type)
{
    float pos_x = 0.1f * (index % 10);
    float pos_y = 0.1f * (index / 10);

    if (type == 0)
    {
        return ImVec2(pos_x, 1 - pos_y);
    }
    else
    {
        return ImVec2(pos_x + 0.1f, 1 - (pos_y + 0.1f));
    }
}

void MyGui::BuildWindow()
{
    int id;
    int building = m_BuildWindowLayout.Build_Id;

    ImGui::Begin("Edit");

    //Delete
    id = 92;
    if (m_BuildWindowLayout.Build_Id == 17)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
    }
    if (ImGui::ImageButton("Delete-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(30, 30), Get_UV(id, 0), Get_UV(id, 1))) building = 17;
    if (m_BuildWindowLayout.Build_Id == 17) ImGui::PopStyleColor(2);
    ImGui::SameLine();

    id = 93;
    if (m_BuildWindowLayout.Build_Id == -1)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
    }
    if (ImGui::ImageButton("Check-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(30, 30), Get_UV(id, 0), Get_UV(id, 1))) building = -1;
    if (m_BuildWindowLayout.Build_Id == -1) ImGui::PopStyleColor(2);
    ImGui::SameLine();

    id = 90;
    if (m_BuildWindowLayout.Build_Id == -2)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
    }
    if (ImGui::ImageButton("Upgrade-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(30, 30), Get_UV(id, 0), Get_UV(id, 1))) building = -2;
    if (m_BuildWindowLayout.Build_Id == -2) ImGui::PopStyleColor(2);
    ImGui::SameLine();

    id = 91;
    if (m_BuildWindowLayout.Build_Id == -3)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
    }
    if (ImGui::ImageButton("Degrade-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(30, 30), Get_UV(id, 0), Get_UV(id, 1))) building = -3;
    if (m_BuildWindowLayout.Build_Id == -3) ImGui::PopStyleColor(2);

    ImGui::End();

    ImGui::Begin("Build");

    if (ImGui::CollapsingHeader("General Fields", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Separator();

        //ROAD
        id = 7;
        ImGui::Text("ROAD -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "150$");
        if (m_BuildWindowLayout.Build_Id == 18)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Road-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 18;
        if (m_BuildWindowLayout.Build_Id == 18) ImGui::PopStyleColor(2);

        ImGui::Separator();

        //FOREST
        id = 42;
        ImGui::Text("FOREST -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "750$");
        if (m_BuildWindowLayout.Build_Id == 9)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Forest-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 9;
        if (m_BuildWindowLayout.Build_Id == 9) ImGui::PopStyleColor(2);
    }

    if (ImGui::CollapsingHeader("Zone Fields", ImGuiTreeNodeFlags_DefaultOpen))
    {
        //RESIDENCE
        id = 16;
        ImGui::Text("RESIDENCE -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "6650$");
        if (m_BuildWindowLayout.Build_Id == 0)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Residence-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 0;
        if (m_BuildWindowLayout.Build_Id == 0) ImGui::PopStyleColor(2);
        ImGui::Separator();

        //INDUSTRY
        id = 30;
        ImGui::Text("INDUSTRY -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "16650$");
        if (m_BuildWindowLayout.Build_Id == 3)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Industry-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 3;
        if (m_BuildWindowLayout.Build_Id == 3) ImGui::PopStyleColor(2);
        ImGui::Separator();

        //SERVICE
        id = 20;
        ImGui::Text("SERVICE -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "13650$");
        if (m_BuildWindowLayout.Build_Id == 6)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Service-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 6;
        if (m_BuildWindowLayout.Build_Id == 6) ImGui::PopStyleColor(2);
    }

    if (ImGui::CollapsingHeader("Building Fields", ImGuiTreeNodeFlags_DefaultOpen))
    {
        //Firestation
        id = 50;
        ImGui::Text("FIRESTATION -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "6650$");
        if (m_BuildWindowLayout.Build_Id == 11)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Firestation-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 11;
        if (m_BuildWindowLayout.Build_Id == 11) ImGui::PopStyleColor(2);
        ImGui::Separator();

        //Firestation
        id = 52;
        ImGui::Text("POLICESTATION -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "6650$");
        if (m_BuildWindowLayout.Build_Id == 10)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Policestation-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 10;
        if (m_BuildWindowLayout.Build_Id == 10) ImGui::PopStyleColor(2);
        ImGui::Separator();

        //Stadion
        id = 45;
        ImGui::Text("STADION -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "6650$");
        if (m_BuildWindowLayout.Build_Id == 14)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Stadion-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 14;
        if (m_BuildWindowLayout.Build_Id == 14) ImGui::PopStyleColor(2);
        ImGui::Separator();

        //Highschool
        id = 55;
        ImGui::Text("HIGHSCHOOL -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "6650$");
        if (m_BuildWindowLayout.Build_Id == 12)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Highschool-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 12;
        if (m_BuildWindowLayout.Build_Id == 12) ImGui::PopStyleColor(2);
        ImGui::Separator();

        //University
        id = 57;
        ImGui::Text("UNIVERSITY -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "6650$");
        if (m_BuildWindowLayout.Build_Id == 13)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("University-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 13;
        if (m_BuildWindowLayout.Build_Id == 13) ImGui::PopStyleColor(2);
        ImGui::Separator();

        //Powerstation
        id = 47;
        ImGui::Text("POWERSTATION -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "6650$");
        if (m_BuildWindowLayout.Build_Id == 16)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Powerstation-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 16;
        if (m_BuildWindowLayout.Build_Id == 16) ImGui::PopStyleColor(2);
        ImGui::Separator();

        //Powerwire
        id = 63;
        ImGui::Text("POWERWIRE -> ");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "6650$");
        if (m_BuildWindowLayout.Build_Id == 15)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.f, 0.f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 1.f));
        }
        if (ImGui::ImageButton("Powerwire-image", (void*)m_BuildWindowLayout.TextureID, ImVec2(150, 150), Get_UV(id, 0), Get_UV(id, 1))) building = 15;
        if (m_BuildWindowLayout.Build_Id == 15) ImGui::PopStyleColor(2);
        ImGui::Separator();
    }

    ImGui::End();

    m_BuildWindowLayout.Build_Id = building;
}

void MyGui::Upgrade_Popup()
{
    if (m_DetailsWindowLayout.Upgrade_Show)
    {
        ImGui::OpenPopup("Upgrade zone");
    }

    if (ImGui::BeginPopupModal("Upgrade zone", nullptr, ImGuiWindowFlags_NoResize))
    {
        ImGui::SetWindowSize(ImVec2(300, 0));

        if (m_DetailsWindowLayout.level < 2)
        {
            ImGui::Text("The upgrade will cost:", m_DetailsWindowLayout.Upgrade_Cost);
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "%d", m_DetailsWindowLayout.Upgrade_Cost);
            ImGui::SameLine();
            ImGui::Text("$");

            ImGui::Text("Are you sure?");

            //Yes Button
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.75, 0, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0.7, 0, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.65, 0, 1));
            ImGui::SetCursorPosY(70.0f);
            if (ImGui::Button("Yes", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
                m_DetailsWindowLayout.Upgrade_Effect = true;
                m_DetailsWindowLayout.Upgrade_Show = false;
            }
            ImGui::SetItemDefaultFocus();
            ImGui::PopStyleColor(3);

            ImGui::SameLine();

            //Cancel Button
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 0, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9, 0, 0, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8, 0, 0, 1));
            ImGui::SetCursorPosX(ImGui::GetWindowContentRegionMax().x - 120);
            ImGui::SetCursorPosY(70.0f);
            if (ImGui::Button("Cancel", ImVec2(120, 0))) 
            { 
                ImGui::CloseCurrentPopup();
                m_DetailsWindowLayout.Upgrade_Show = false;
            }

            ImGui::PopStyleColor(3);
        }
        else
        {
            ImGui::Text("The zone is fully upgraded!");

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 1, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0.9, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0.8, 1));

            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 buttonSize(80.0f, 20.0f);
            ImVec2 buttonPos((windowSize.x - buttonSize.x) / 2.0f, 60.0f);
            ImGui::SetCursorPos(buttonPos);

            if (ImGui::Button("Ok", ImVec2(80, 20))) 
            { 
                ImGui::CloseCurrentPopup();
                m_DetailsWindowLayout.Upgrade_Show = false;      
            }
            ImGui::PopStyleColor(3);
        }
        ImGui::EndPopup();
    }
}

//|DETAILS-WINDOW|-------------------------------------------------------------------------------------------//
//|DETAILS-WINDOW|-------------------------------------------------------------------------------------------//
//|DETAILS-WINDOW|-------------------------------------------------------------------------------------------//

void MyGui::DetailsWindow()
{
    ImGui::Begin("Details");

    if (ImGui::CollapsingHeader("Field Details", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::TextUnformatted(m_DetailsWindowLayout.Details.c_str());
    }

    if (ImGui::CollapsingHeader("Field Details", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text(m_DetailsWindowLayout.Network_details.c_str());
    }

    ImGui::End();
}

//|VIEWPORT-WINDOW|-------------------------------------------------------------------------------------------//
//|VIEWPORT-WINDOW|-------------------------------------------------------------------------------------------//
//|VIEWPORT-WINDOW|-------------------------------------------------------------------------------------------//

void MyGui::ViewPortWindow()
{
    ImGui::Begin("ViewPort", nullptr, ImGuiWindowFlags_NoCollapse);

    Camera_MouseClickEvent();
    Camera_KeyboardKeyEvent();
    Build_MouseClickEvent();
    Build_KeyboardKeyEvent();

    ImVec2 size = ImGui::GetContentRegionAvail();

    ImGui::Image((void*)m_ViewPortLayout.ViewPort_TextureID, size, ImVec2(0, 1), ImVec2(1, 0));

    if (size.x != m_ViewPortLayout.ViewPort_Width || size.y != m_ViewPortLayout.ViewPort_Height)
    {
        m_ViewPortLayout.ViewPort_Effect = true;
    }

    m_ViewPortLayout.ViewPort_Width = (int)size.x;
    m_ViewPortLayout.ViewPort_Height = (int)size.y;

    ImGui::End();
}

//|EVENTS-INPUT|---------------------------------------------------------//
//|EVENTS-INPUT|---------------------------------------------------------//
//|EVENTS-INPUT|---------------------------------------------------------//

void MyGui::Build_MouseClickEvent()
{
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        BuildHover = true;
        m_EventLayout.Hit = false;
    }

    if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
    {
        m_EventLayout.Hit = true;
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
            m_EventLayout.Mouse_X = RelativWindowCursor_X - (int)ImGui::GetWindowContentRegionMin().x;
            m_EventLayout.Mouse_Y = RelativWindowCursor_Y - (int)ImGui::GetWindowContentRegionMin().y;
            m_EventLayout.Content_X = CurrentContent_MAX.x - CurrentContent_MIN.x;
            m_EventLayout.Content_Y = CurrentContent_MAX.y - CurrentContent_MIN.y;
        }
    }
}

void MyGui::Build_KeyboardKeyEvent()
{
    if (ImGui::IsKeyPressed(ImGuiKey_R))
    {
        m_EventLayout.Rotate++;
    }
}

void MyGui::Camera_MouseClickEvent()
{
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && m_RenderWindowLayout.Camera_Mode == 2)
    {
        m_Camera->Mouse_ClickEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);
    }
    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && m_RenderWindowLayout.Camera_Mode == 2)
    {
        m_Camera->Mouse_ClickEvent(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE, 0);
    }
    if (ImGui::IsWindowHovered() && m_RenderWindowLayout.Camera_Mode == 2)
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

    //CTRL
    if (ImGui::IsKeyPressed(ImGuiKey_LeftCtrl))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_LEFT_CONTROL, 0, GLFW_PRESS, 0);
    }
    if (ImGui::IsKeyReleased(ImGuiKey_LeftCtrl))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_LEFT_CONTROL, 0, GLFW_RELEASE, 0);
    }

    //SHIFT
    if (ImGui::IsKeyPressed(ImGuiKey_LeftShift))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_LEFT_SHIFT, 0, GLFW_PRESS, 0);
    }
    if (ImGui::IsKeyReleased(ImGuiKey_LeftShift))
    {
        m_Camera->Keyboard_ButtonEvent(GLFW_KEY_LEFT_SHIFT, 0, GLFW_RELEASE, 0);
    }
}