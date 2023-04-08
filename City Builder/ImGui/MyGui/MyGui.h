#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Utilities/Camera.h"
#include "Abstractions/FrameBuffer.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_glfw.h"
#include "../ImGui/imgui_impl_opengl3.h"

class MyGui
{
public:
	MyGui(Camera* camera);
	~MyGui() = default;

	void Pre_Render();
	void Post_Render();

	void Demo_Render();
	void Window1_Render();
	void Window2_Render();
	void Window3_Render();
	void Window4_Render();
	void Window5_Render();
	void ViewPort_Render(FrameBuffer* fbo);
	void DockSpace_Render();

	static void Init(GLFWwindow* window);
	static void Clean();

	bool hit;
	int mouse_x;
	int mouse_y;
	ImVec2 content_size;
protected:
	//Style
	static void Custom_Style();
	//Events
	void Build_MouseClickEvent();
	void Camera_MouseClickEvent();
	void Camera_KeyboardKeyEvent();
private:
	Camera* m_Camera = nullptr;
	int m_ViewPort_Width = 0;
	int m_ViewPort_Height = 0;
};

