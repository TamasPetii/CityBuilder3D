#pragma once
#include <string>

struct NewGameLayout 
{
	bool effect = false;
	bool show = false;
	char name[64];
	int size = 25;
	int time = 0;
};

struct LoadGameLayout
{
	bool effect = false;
	bool show = false;
	std::string path;
	std::string name;
	std::string extension = ".txt";
};

struct SaveGameLayout
{
	bool effect = false;
	bool show = false;
	std::string path;
	std::string name;
	std::string extension = ".txt";
};

struct BuildLayout
{
	bool effect = false;
	int building = 0;
};

struct TaxLayout
{
	bool effect = false;

	float ResidenceTaxLvl1 = 20;
	float ResidenceTaxLvl2 = 20;
	float ResidenceTaxLvl3 = 20;

	float IndustrialTaxLvl1 = 20;
	float IndustrialTaxLvl2 = 20;
	float IndustrialTaxLvl3 = 20;

	float ServiceTaxLvl1 = 20;
	float ServiceTaxLvl2 = 20;
	float ServiceTaxLvl3 = 20;
};

struct LightsLayout
{
	bool effect = false;
	bool reset = false;

	glm::vec3 lightDir = glm::vec3(1, -1, 1);
	int specularPow = 64;
	glm::vec3 La = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 Ld = glm::vec3(1, 1, 0.85);
	glm::vec3 Ls = glm::vec3(1, 1, 1);
	glm::vec3 Ka = glm::vec3(0.8, 0.8, 0.8);
	glm::vec3 Kd = glm::vec3(1, 1, 1);
	glm::vec3 Ks = glm::vec3(0.7, 0.6, 0.6);
};

struct FieldDetailsLayout
{
	bool isZone;
	int x;
	int y;
	int level;
	int contain;
	int capacity;
	float satisfaction;
	std::string citizens_details;
};

struct LogLayout 
{
	std::string citizen_log;
	std::string build_log;
	std::string money_log;
};

struct CityLayout
{
	int money;
	std::string time;
};

struct CatastropheLayout
{
	bool effect;
	int count;
};

struct DimensionLayout
{
	bool show = false;
	bool effect = false;
	int dimension = 2;
	const char* items[3] = { "2D", "2.5D", "3D" };

	bool Ask = false;
	bool DontAskMeNextTime_2D_AND_HALF = false;
	bool DontAskMeNextTime_3D = false;
};

struct GameWindowLayout
{
	int money;


	float tick;
	std::string gameTime;
	std::string realTime;
};

struct RenderWindowLayout
{
	int fps;
	float time;
	bool fps_lock;

	bool show = false;
	bool Ask = false;
	bool DontAskMeNextTime_2D_AND_HALF = false;
	bool DontAskMeNextTime_3D = false;
	const char* items[3] = { "2D", "2.5D", "3D" };
};