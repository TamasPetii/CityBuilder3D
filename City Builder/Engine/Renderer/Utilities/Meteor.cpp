#include "Meteor.h"

std::vector<Meteor*> MeteorGrp::m_ToDelete;
std::unordered_set<Meteor*> MeteorGrp::m_Meteors;
float MeteorGrp::last_time;
float MeteorGrp::current_time;
float MeteorGrp::delta_time;

void MeteorGrp::Init()
{
	last_time = glfwGetTime();
}

//This will callculate the delta time between 2 render cycle
//We will use this value to update every meteors positon
void MeteorGrp::Update()
{
	current_time = glfwGetTime();
	delta_time = current_time - last_time;
	last_time = current_time;

	for (Meteor* meteor : m_Meteors)
	{
		meteor->Update(delta_time);

		if (meteor->Delete())
		{
			m_ToDelete.push_back(meteor);
		}
	}
}

//This will tell the application if any of the meteors reached the end of its path
//Which means we need to destroy a gamefiled on the gametable
bool MeteorGrp::Effect()
{
	return m_ToDelete.size();
}

//Delete meteors that reached end of its path
void MeteorGrp::Delete()
{
	for (int i = 0; i < m_ToDelete.size(); i++)
	{
		m_Meteors.erase(m_ToDelete[i]);
		delete m_ToDelete[i];
	}

	m_ToDelete.clear();
}

//This will tell which gamefields should be destroyed
std::vector<std::pair<int, int>> MeteorGrp::Change()
{
	std::vector<std::pair<int, int>> fields;

	for (int i = 0; i < m_ToDelete.size(); i++)
	{
		fields.push_back(m_ToDelete[i]->Get_EndPos());
	}

	return fields;
}

void MeteorGrp::Add(int x, int y)
{
	float random_float = ((float)rand()) / (float)RAND_MAX; //Random number from 0.0 to 1.0 (float)

	float radius = 1;
	float speed = MAX_SPEED * random_float + MAX_SPEED / 2;
	float start_radius = rand() % 250 + 250; //Distance from the gametable
	float start_angle = ((float)rand()) / (float)RAND_MAX; //Random number from 0.0 to 1.0 (float)
	glm::vec3 start = glm::vec3(start_radius * cos(glm::radians(start_angle * 360)), start_radius, start_radius * sin(glm::radians(start_angle * 360)));
	glm::vec3 end = glm::vec3(2 * y + 1, 0, 2 * x + 1);

	m_Meteors.insert(new Meteor(radius, speed, start, end));
}

//This is a full clear, should be called when new game started
void MeteorGrp::Clear()
{
	for (auto it = m_Meteors.begin(); it != m_Meteors.end(); ++it)
	{
		delete* it;
	}
	m_Meteors.clear();
	m_ToDelete.clear();
}

std::vector<glm::mat4> MeteorGrp::Get_Transforms()
{
	std::vector<glm::mat4> transforms;

	for (Meteor* meteor : m_Meteors)
	{
		transforms.push_back(meteor->Get_Transform());
	}

	return transforms;
}

//------------------------------------------------|METEOR|------------------------------------------------//

Meteor::Meteor(float radius, float speed, glm::vec3 start, glm::vec3 end) :
	radius(radius),
	speed(speed),
	start_position(start),
	end_positon(end)
{
	t = 0;
	current_position = start_position;
}

void Meteor::Update(float t)
{
	this->t += t * (speed / (10 * MAX_SPEED));
	current_position = start_position + (end_positon - start_position) * this->t;
}

bool Meteor::Delete()
{
	return t >= 1;
}

glm::mat4 Meteor::Get_Transform()
{
	return glm::translate(current_position);
}

std::pair<int, int> Meteor::Get_EndPos()
{
	return { (int)end_positon.z / 2, (int)end_positon.x / 2 };
}