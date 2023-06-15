#pragma once
#include <string>

/**
 * A struct representing the layout of a viewport.
 *
 * @param ViewPort_Effect A boolean indicating whether the viewport is active or not.
 * @param ViewPort_TextureID The ID of the texture associated with the viewport.
 * @param ViewPort_Width The width of the viewport.
 * @param ViewPort_Height The height of the viewport.
 */
struct ViewPortLayout 
{
	bool ViewPort_Effect = false;
	int ViewPort_TextureID;
	int ViewPort_Width = 0;
	int ViewPort_Height = 0;
};

/**
 * Defines the layout of the menu bar for a game.
 *
 * The MenuBarLayout struct contains boolean flags and variables that define the layout of the menu bar for a game. 
 * It includes options for new game, load game, save game, ImGui demo, and info. 
 * 
 * @param NewGame_Effect A boolean flag indicating whether the new game effect is enabled.
 * @param NewGame_Show A boolean flag indicating whether the new game option is shown.
 * @param City_Name A character array containing the name of the city.
 * @param City_Size An integer representing the size of the city.
 * @param City_Time A float representing the time of the city.
 * @param LoadGame_Effect A boolean
 */
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

/**
 * Defines the layout of the game window.
 *
 * The GameWindowLayout struct contains information about the state of the game window, including the city's money and satisfaction levels, time-related effects, catastrophe effects, and tax levels for different types of buildings.
 *
 * @param City_Money The amount of money the city has.
 * @param City_Satisfaction The satisfaction level of the city.
 * @param Time_Effect A boolean indicating whether time-related effects are enabled.
 * @param Time_Tick The time interval for the game.
 * @param Time_Game The current game time.
 * @param Time_Real The current real time.
 * @param PauseTime A boolean indicating whether the game is paused.
 * @param Catastrophe_Effect
 */
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
	bool PauseTime = false;

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

/**
 * A struct that defines the layout of a render window.
 *
 * @param Frame_Fps The frames per second of the render window.
 * @param Frame_Time The time of each frame in the render window.
 * @param Frame_Lock A boolean indicating whether the frame is locked or not.
 * @param Camera_Effect A boolean indicating whether the camera effect is enabled or not.
 * @param Camera_Show A boolean indicating whether the camera is shown or not.
 * @param Camera_Show2D A boolean indicating whether the camera is shown in 2D or not.
 * @param Camera_Show3D A boolean indicating whether the camera is shown in 3D or not.
 * @param Camera_Ask A boolean indicating whether the
 */
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

/**
 * A struct representing the layout of a log window, containing the file paths for the citizen log, build log, and money log.
 */
struct LogWindowLayout
{
	std::string citizen_log;
	std::string build_log;
	std::string money_log;
};

/**
 * A struct representing the layout of a building window.
 *
 * @param Build_Id The ID of the building.
 * @param TextureID The ID of the texture for the building.
 * @param RoadCost The cost of building a road.
 * @param ForestCost The cost of building in a forested area.
 * @param ResidenceCost The cost of building a residence.
 * @param IndustryCost The cost of building an industry.
 * @param ServiceCost The cost of building a service building.
 * @param FireStationCost The cost of building a fire station.
 * @param PoliceStationCost The cost of building a police station.
 * @param StadionCost The cost of building a stadium.
 * @param HighSchoolCost
 */
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

/**
 * A struct that defines the layout of the details window for a game.
 *
 * @param Details_X The x-coordinate of the details window.
 * @param Details_Y The y-coordinate of the details window.
 * @param Details The details to be displayed in the window.
 * @param Field_X The x-coordinate of the field in the window.
 * @param Field_Y The y-coordinate of the field in the window.
 * @param Field_Type The type of field to be displayed.
 * @param Network_details The details of the network to be displayed.
 * @param Upgrade_Effect A boolean indicating whether an upgrade effect is present.
 * @param Upgrade_Show A boolean indicating whether the upgrade is to be displayed.
 * @param Upgrade_C
 */
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

	//End Game
	bool End = false;
	bool End_Show = false;

};

/**
 * Defines the layout of an event, including mouse and content coordinates, and rotation.
 */
struct EventLayout
{
	bool Hit;
	int Mouse_X;
	int Mouse_Y;
	int Content_X;
	int Content_Y;
	int Rotate = 0;
};