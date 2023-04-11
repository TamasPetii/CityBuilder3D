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