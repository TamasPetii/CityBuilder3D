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

struct TaxLayout
{
	bool effect = false;

	float ResidenceTaxLvl1;
	float ResidenceTaxLvl2;
	float ResidenceTaxLvl3;

	float IndustrialTaxLvl1;
	float IndustrialTaxLvl2;
	float IndustrialTaxLvl3;

	float ServiceTaxLvl1;
	float ServiceTaxLvl2;
	float ServiceTaxLvl3;
};