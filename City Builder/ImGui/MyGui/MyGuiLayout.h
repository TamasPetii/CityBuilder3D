#pragma once
#include <string>

struct ViewPortLayout 
{
	bool ViewPort_Effect = false;
	int ViewPort_TextureID;
	int ViewPort_Width = 0;
	int ViewPort_Height = 0;
};

struct MenuBarLayout 
{
	//New Game Layout
	bool  NewGame_Effect = false;
	bool  NewGame_Show = false;
	char  City_Name[64];
	int   City_Size = 50;
	float City_Time = 0.1f;

	//Load Game Layout
	bool LoadGame_Effect = false;
	bool LoadGame_Show = false;
	std::string LoadFile_Path;
	std::string LoadFile_Name;
	std::string LoadFile_Extension = ".txt";

	//Save Game Layout
	bool SaveGame_Effect = false;
	bool SaveGame_Show = false;
	std::string SaveFile_Path;
	std::string SaveFile_Name;
	std::string SaveFile_Extension = ".txt";

	//Demo Layout
	bool ImGuiDemo_Show = false;

	//Info Layout
	bool Info_Show = false;
};

struct GameWindowLayout
{
	//General
	int City_Money;
	int City_Satisfaction;

	//Time 
	bool Time_Effect = false;
	float Time_Tick = 0.1f;
	std::string Time_Game;
	float Time_Real;

	//Catastrophe
	bool Catastrophe_Effect;
	int Catastrophe_Count = 0;

	//Tax
	bool Tax_Effect = false;
	float ResidenceTaxLvl1 = 40;
	float ResidenceTaxLvl2 = 40;
	float ResidenceTaxLvl3 = 40;
	float IndustrialTaxLvl1 = 40;
	float IndustrialTaxLvl2 = 40;
	float IndustrialTaxLvl3 = 40;
	float ServiceTaxLvl1 = 40;
	float ServiceTaxLvl2 = 40;
	float ServiceTaxLvl3 = 40;
};

struct RenderWindowLayout
{
	//Frame
	int   Frame_Fps;
	float Frame_Time;
	bool  Frame_Lock = false;

	//Camera
	bool Camera_Effect = false;
	bool Camera_Show = false;
	bool Camera_Show2D = true;
	bool Camera_Show3D = true;
	bool Camera_Ask = true;
	int Camera_Mode = 2;
	const char* Camera_Modes[3] = { "2D", "2.5D", "3D" };
	float Camera_Speed = 5.f;
	glm::vec3 Camera_Position;

	//Objects


	//Lights
	bool Lights_Effect = false;
	bool Lights_Reset = false;
	glm::vec3 Lights_Direction = glm::vec3(1, -1, 1);
	int Lights_SpecularPow = 64;
	glm::vec3 La = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 Ld = glm::vec3(1, 1, 0.85);
	glm::vec3 Ls = glm::vec3(1, 1, 1);
	glm::vec3 Ka = glm::vec3(0.8, 0.8, 0.8);
	glm::vec3 Kd = glm::vec3(1, 1, 1);
	glm::vec3 Ks = glm::vec3(0.7, 0.6, 0.6);
};

struct LogWindowLayout
{
	std::string citizen_log;
	std::string build_log;
	std::string money_log;
};

struct BuildWindowLayout
{
	int  Build_Id = 0;
	int  TextureID;

	int RoadCost;
	int ForestCost;
	int ResidenceCost;
	int IndustryCost;
	int ServiceCost;
	int FireStationCost;
	int PoliceStationCost;
	int StadionCost;
	int HighSchoolCost;
	int UniversityCost;
	int PowerStationCost;
};

struct DetailsWindowLayout
{
	int Details_X = 0;
	int Details_Y = 0;
	std::string Details;

	int Field_X = 0;
	int Field_Y = 0;
	int Field_Type = 0;

	//NetWork Details
	std::string Network_details;

	//Upgrade details
	bool Upgrade_Effect = false;
	bool Upgrade_Show = false;
	int Upgrade_Cost = 0;
	int level = 0;
};

struct EventLayout
{
	bool Hit;
	int Mouse_X;
	int Mouse_Y;
	int Content_X;
	int Content_Y;
	int Rotate = 0;
};