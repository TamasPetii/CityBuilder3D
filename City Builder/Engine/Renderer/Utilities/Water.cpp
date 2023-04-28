#include "Water.h"

WaterGroup::WaterGroup(int startX, int startY, int endX, int endY)
{
	curve = new ProjectileMotion(glm::vec3(startX, 0, startY), glm::vec3(endX, 0, endY));
}

void WaterGroup::Init()
{
	last_time = glfwGetTime();
}

void WaterGroup::Clear()
{
	for (auto it = m_Waters.begin(); it != m_Waters.end(); ++it)
	{
		delete* it;
	}

	m_Waters.clear();
	m_ToDelete.clear();
}

void WaterGroup::Update()
{
	Delete();

	if (time >= 0.05)
	{
		Add();
		time = 0;
		std::cout << m_Waters.size() << std::endl;
	}

	current_time = glfwGetTime();
	delta_time = current_time - last_time;
	time += delta_time;
	last_time = current_time;

	for (auto* water : m_Waters)
	{
		water->Update(delta_time * 0.4, curve);

		if (water->Delete())
		{
			m_ToDelete.push_back(water);
		}
	}
}

void WaterGroup::Recalculate(int endX, int endY)
{

	if (curve != nullptr) delete curve;
	curve = new ProjectileMotion(glm::vec3(0, 0, 0), glm::vec3(endX, 0, endY));
}

void WaterGroup::Delete()
{
	for (int i = 0; i < m_ToDelete.size(); i++)
	{
		m_Waters.erase(m_ToDelete[i]);
		delete m_ToDelete[i];
	}

	m_ToDelete.clear();
}

void WaterGroup::Add()
{
	m_Waters.insert(new Water());
}

std::vector<glm::mat4> WaterGroup::Get_Transforms()
{
	std::vector<glm::mat4> transforms;

	for (auto water : m_Waters)
	{
		transforms.push_back(water->Get_Transform());
	}

	return transforms;
}

//------------------------------------------------------------------------------------------------------------------------

Water::Water()
{

}

void Water::Update(float t, ProjectileMotion* curve)
{
	this->t += t;
	position = curve->Get_PositionOnCurve(this->t);
}

bool Water::Delete()
{
	return t >= 1;
}

//------------------------------------------------------------------------------------------------------------------------

ProjectileMotion::ProjectileMotion(glm::vec3 start, glm::vec3 end) :
	m_MotionStartPosition(start),
	m_MotionEndPosition(end)
{
	distanceX = m_MotionEndPosition.x - m_MotionStartPosition.x;
	distanceZ = m_MotionEndPosition.z - m_MotionStartPosition.z;
	distanceY = m_MotionEndPosition.y - m_MotionStartPosition.y;
	distance = sqrtf(powf(distanceX, 2) + powf(distanceZ, 2));
	angle = fmin(55 + (distance > 6.2 ? 0 : abs(distance - 5.2 - 2) * 5), 85) * (M_PI / 180.f);
	speed = sqrtf((-1 * m_Gravity * powf(distance, 2)) / (2 * powf(cosf(angle), 2) * (distanceY - distance * tanf(angle))));
}

glm::vec3 ProjectileMotion::Get_PositionOnCurve(float t)
{
	float MotionD = t * distance;
	float MotionX = t * distanceX;
	float MotionZ = t * distanceZ;
	float MotionY = MotionD * tan(angle) - ((m_Gravity * powf(MotionD, 2)) / (2 * powf(speed, 2) * powf(cos(angle), 2)));

	return glm::vec3(m_MotionStartPosition.x + MotionX, m_MotionStartPosition.y + MotionY, m_MotionStartPosition.z + MotionZ);
}