#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Utilities/Camera.h"
#include "Abstractions/FrameBuffer.h"
#include "Abstractions/Texture.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"
#include "MyGuiLayout.h"

#include "../ImGui/ImGuiFileBrowser.h"

class MyGui
{
public:
	MyGui(Camera* camera);
	~MyGui() = default;

	static void Init(GLFWwindow* window);
	static void Clean();

	void Pre_Render();
	void Post_Render();

	void CityDetials_Window();
	void DockSpace();
	void Demo_Window();
	void GameDetails_Window();
	void GameOptions_Window();
	void FieldDetails_Window();
	void Log_Window();
	void RenderOptions_Window();
	void Build_Window(Texture* texture);
	void ViewPort_Render(FrameBuffer* fbo);
	void GameIdk();

	void Game_Window();
	void Render_Window();

	int pos;

	inline NewGameLayout& Get_NewGameLayout() { return m_NewGameLayout; }
	inline LoadGameLayout& Get_LoadGameLayout() { return m_LoadGameLayout; }
	inline SaveGameLayout& Get_SaveGameLayout() { return m_SaveGameLayout; }
	inline TaxLayout& Get_TaxLayout() { return m_TaxLayout; }
	inline BuildLayout Get_BuildLayout() { return m_BuildLayout; }
	inline LightsLayout& Get_LightsLayout() { return m_LightsLayout; }
	inline FieldDetailsLayout& Get_FieldDetailsLayout() { return m_FieldDetailsLayout; }
	inline LogLayout& Get_LogLayout() { return m_LogLayout; }
	inline CatastropheLayout& Get_CatastropheLayout() { return m_MeteorLayout; }
	inline CityLayout& Get_CityLayout() { return m_CityLayout; }
	inline DimensionLayout& Get_DimensionLayout() { return m_DimensionLayout; }

	inline RenderWindowLayout& Get_RenderWindowLayout() { return m_RenderWindowLayout; }
	inline GameWindowLayout& Get_GameWindowLayout() { return m_GameWindowLayout; }

	bool BuildHover = false;
	int r = 0;
	bool hit;
	int mouse_x;
	int mouse_y;
	ImVec2 content_size;
protected:
	static void Custom_Style();

	void Build_MouseClickEvent();
	void Build_KeyboardKeyEvent();
	void Camera_MouseClickEvent();
	void Camera_KeyboardKeyEvent();

	void NewGame_Window();
	void LoadGame_Window();
	void SaveGame_Window();
	void DockSpace_MenuBar();

	void Dimension_2D_AND_HALF_Popup();
	void Dimension_3D_Popup();

	void Table_Game_General();
	void Table_Game_Time();
	void Table_Game_Tax();

	void Table_Render_Lights();
	void Table_Render_Objects();
	void Table_Render_Camera();
	void Table_Render_Frame();
private:
	Camera* m_Camera = nullptr;
	int m_ViewPort_Width = 0;
	int m_ViewPort_Height = 0;


	NewGameLayout m_NewGameLayout;
	LoadGameLayout m_LoadGameLayout;
	SaveGameLayout m_SaveGameLayout;
	BuildLayout m_BuildLayout;
	TaxLayout m_TaxLayout;
	FieldDetailsLayout m_FieldDetailsLayout;
	LogLayout m_LogLayout;
	CityLayout m_CityLayout;
	LightsLayout m_LightsLayout;
	CatastropheLayout m_MeteorLayout;
	DimensionLayout m_DimensionLayout;

	GameWindowLayout m_GameWindowLayout;
	RenderWindowLayout m_RenderWindowLayout;
	imgui_addons::ImGuiFileBrowser file_dialog;



	ImVec2 Get_UV(int index, int type);
};

