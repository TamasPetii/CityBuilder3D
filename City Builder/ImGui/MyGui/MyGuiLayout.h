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