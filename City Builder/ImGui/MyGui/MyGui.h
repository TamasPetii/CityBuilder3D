#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Utilities/Camera.h"
#include "Abstractions/FrameBuffer.h"
#include "Abstractions/Texture.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"
#include "../ImGui/ImGuiFileBrowser.h"


#include "MyGuiLayout.h"
class MyGui
{
public:
	MyGui(Camera* camera);
	~MyGui() = default;

	static void Init(GLFWwindow* window);
	static void Clean();

	void Pre_Render();
	void Post_Render();
	void DockSpace();

	inline ViewPortLayout& Get_ViewPortLayout() { return m_ViewPortLayout; }
	inline MenuBarLayout& Get_MenuBarLayout() { return m_MenuBarLayout; }
	inline GameWindowLayout& Get_GameWindowLayout() { return m_GameWindowLayout; }
	inline RenderWindowLayout& Get_RenderWindowLayout() { return m_RenderWindowLayout; }
	inline LogWindowLayout& Get_LogWindowLayout() { return m_LogWindowLayout; }
	inline BuildWindowLayout& Get_BuildWindowLayout() { return m_BuildWindowLayout; }
	inline DetailsWindowLayout& Get_DetailsWindowLayout() { return m_DetailsWindowLayout; }
	inline EventLayout& Get_EventLayout() { return m_EventLayout; }
	bool BuildHover = false;
protected:
	static void Custom_Style();
	void Build_MouseClickEvent();
	void Build_KeyboardKeyEvent();
	void Camera_MouseClickEvent();
	void Camera_KeyboardKeyEvent();

	void DockSpace_MenuBar();
	void NewGame_Popup();
	void LoadGame_Popup();
	void SaveGame_Popup();
	void InfoGame_Popup();
	void ViewPortWindow();
	void GameWindow();
	void GameWindow_General();
	void GameWindow_Time();
	void GameWindow_Tax();
	void GameWindow_Catastrophe();
	void RenderWindow();
	void RenderWindow_Frame();
	void RenderWindow_Camera();
	void RenderWindow_CameraPopup2D();
	void RenderWindow_CameraPopup3D();
	void RenderWindow_Objects();
	void RenderWindow_Lights();
	void LogWindow();
	void BuildWindow();
	void DetailsWindow();

	ImVec2 Get_UV(int index, int type);
private:
	Camera* m_Camera = nullptr;

	ViewPortLayout m_ViewPortLayout;
	MenuBarLayout m_MenuBarLayout;
	GameWindowLayout m_GameWindowLayout;
	RenderWindowLayout m_RenderWindowLayout;
	LogWindowLayout m_LogWindowLayout;
	BuildWindowLayout m_BuildWindowLayout;
	DetailsWindowLayout m_DetailsWindowLayout;
	EventLayout m_EventLayout;

	imgui_addons::ImGuiFileBrowser file_dialog;
};

