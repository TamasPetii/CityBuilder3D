#include "Meteor.h"

std::unordered_set<MeteorLayout*> Meteor::meteors;
std::vector<MeteorLayout*> Meteor::to_delete;
std::vector<std::pair<int, int>> Meteor::fields;
float Meteor::last_time;
float Meteor::current_time;
bool Meteor::Init = true;

void Meteor::FullClear()
{
	meteors.clear();
	to_delete.clear();
	fields.clear();
}

void Meteor::Clear()
{
	for (int i = 0; i < to_delete.size(); i++)
	{
		meteors.erase(to_delete[i]);
		delete to_delete[i];
	}

	to_delete.clear();
	fields.clear();
}

void Meteor::AdjustTime()
{
	last_time = glfwGetTime();
}

void Meteor::Update()
{
	current_time = glfwGetTime();

	for (MeteorLayout* layout : meteors)
	{
		layout->current_position += layout->speed * glm::normalize(layout->end_positon - layout->start_position) * static_cast<float>(current_time - last_time);
	
		if (layout->current_position.y <= 0)
		{
			to_delete.push_back(layout);
			fields.push_back({ (int)layout->end_positon.z / 2, (int)layout->end_positon.x / 2 });
		}
	}

	last_time = current_time;
}

bool Meteor::IsActive()
{
	return meteors.size() != 0;
}

std::vector<std::pair<int, int>> Meteor::Get_Fields()
{
	return fields;
}

std::vector<glm::mat4> Meteor::Get_Transforms()
{
	std::vector<glm::mat4> transforms;

	for (MeteorLayout* layout : meteors)
	{
		transforms.push_back(glm::translate(layout->current_position) * glm::scale(glm::vec3(layout->radius)));
	}

	return transforms;
}

void Meteor::Add(int x, int y)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist_angle(0.f, 1.f);

	MeteorLayout* layout = new MeteorLayout();
	layout->radius = 1;
	layout->speed = rand() % 25 + 25;
	layout->start_position = glm::vec3(cosf(dist_angle(gen) * 2 * M_PI) * ((rand() % 200) + 250), rand() % 200 + 150, sinf(dist_angle(gen) * 2 * M_PI) * ((rand() % 200) + 250));
	layout->end_positon = glm::vec3(2 * y + 1, 0, 2 * x + 1);
	layout->current_position = layout->start_position;

	meteors.insert(layout);
}
