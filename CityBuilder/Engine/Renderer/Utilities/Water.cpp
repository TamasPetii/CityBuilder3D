#include "Water.h"

/**
 * Constructs a WaterGroup object with the given start and end coordinates.
 *
 * @param startX The x-coordinate of the starting point of the water group.
 * @param startY The y-coordinate of the starting point of the water group.
 * @param endX The x-coordinate of the ending point of the water group.
 * @param endY The y-coordinate of the ending point of the water group.
 *
 * @returns None
 */
WaterGroup::WaterGroup(float startX, float startY, float endX, float endY)
{
	curve = new ProjectileMotion(glm::vec3(startX, 0, startY), glm::vec3(endX, 0, endY));

	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
}

/**
 * Initializes the WaterGroup object by setting the last_time variable to the current time.
 *
 * @returns None
 */
void WaterGroup::Init()
{
	last_time = (float)glfwGetTime();
}

/**
 * Resets the timer for the water group.
 *
 * @returns None
 */
void WaterGroup::ResetTimer()
{
	last_time = (float)glfwGetTime();
}

/**
 * Clears the WaterGroup by deleting all the Water objects it contains.
 *
 * @returns None
 */
void WaterGroup::Clear()
{
	for (auto it = m_Waters.begin(); it != m_Waters.end(); ++it)
	{
		delete* it;
	}

	m_Waters.clear();
	m_ToDelete.clear();
}

/**
 * Updates the water group by deleting any water objects that need to be deleted, adding new water objects if the time threshold has been reached, and updating the existing water objects.
 *
 * @returns None
 */
void WaterGroup::Update()
{
	Delete();

	if (time >= 0.01)
	{
		Add();
		time = 0;
	}

	current_time = (float)glfwGetTime();
	delta_time = current_time - last_time;
	time += delta_time;
	last_time = current_time;

	for (auto* water : m_Waters)
	{
		water->Update(delta_time * 0.4f, curve);

		if (water->Delete())
		{
			m_ToDelete.push_back(water);
		}
	}
}

/**
 * Recalculates the projectile motion of the water group.
 *
 * @param endX The x-coordinate of the end point of the water group.
 * @param endY The y-coordinate of the end point of the water group.
 *
 * @returns None
 */
void WaterGroup::Recalculate(int endX, int endY)
{

	if (curve != nullptr) delete curve;
	curve = new ProjectileMotion(glm::vec3(0, 0, 0), glm::vec3(endX, 0, endY));
}

/**
 * Deletes the water molecules in the `m_ToDelete` vector from the `m_Waters` set and frees the memory.
 *
 * @returns None
 */
void WaterGroup::Delete()
{
	for (int i = 0; i < m_ToDelete.size(); i++)
	{
		m_Waters.erase(m_ToDelete[i]);
		delete m_ToDelete[i];
	}

	m_ToDelete.clear();
}

/**
 * Adds a new water molecule to the water group.
 *
 * @param None
 *
 * @returns None
 */
void WaterGroup::Add()
{
	m_Waters.insert(new Water());
}

/**
 * Returns a vector of transformation matrices for each water object in the group.
 *
 * @returns A vector of transformation matrices.
 */
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

/**
 * Default constructor for the Water class.
 *
 * @returns None
 */
Water::Water()
{

}

/**
 * Updates the position of the water based on the projectile motion curve.
 *
 * @param t The time elapsed since the last update.
 * @param curve A pointer to the projectile motion curve.
 *
 * @returns None
 */
void Water::Update(float t, ProjectileMotion* curve)
{
	this->t += t;
	position = curve->Get_PositionOnCurve(this->t);
}

/**
 * Determines if the water object should be deleted.
 *
 * @returns True if the water object should be deleted, false otherwise.
 */
bool Water::Delete()
{
	return t >= 1;
}

//------------------------------------------------------------------------------------------------------------------------

/**
 * Computes the motion of a projectile from a start position to an end position.
 *
 * @param start The starting position of the projectile.
 * @param end The ending position of the projectile.
 *
 * @returns None
 */
ProjectileMotion::ProjectileMotion(glm::vec3 start, glm::vec3 end) :
	m_MotionStartPosition(start),
	m_MotionEndPosition(end)
{
	distanceX = m_MotionEndPosition.x - m_MotionStartPosition.x;
	distanceZ = m_MotionEndPosition.z - m_MotionStartPosition.z;
	distanceY = m_MotionEndPosition.y - m_MotionStartPosition.y;
	distance = sqrtf(powf(distanceX, 2) + powf(distanceZ, 2));
	angle = fmin(45 + (distance > 6.2 ? 0 : abs(distance - 5.2 - 2) * 5), 60) * (M_PI / 180.f);
	speed = sqrtf((-1 * m_Gravity * powf(distance, 2)) / (2 * powf(cosf(angle), 2) * (distanceY - distance * tanf(angle))));
}

/**
 * Computes the position of a projectile at a given time t along a curve.
 *
 * @param t The time at which to compute the position.
 *
 * @returns The position of the projectile at time t as a glm::vec3.
 */
glm::vec3 ProjectileMotion::Get_PositionOnCurve(float t)
{
	float MotionD = t * distance;
	float MotionX = t * distanceX;
	float MotionZ = t * distanceZ;
	float MotionY = MotionD * tan(angle) - ((m_Gravity * powf(MotionD, 2)) / (2 * powf(speed, 2) * powf(cos(angle), 2)));

	return glm::vec3(m_MotionStartPosition.x + MotionX, m_MotionStartPosition.y + MotionY, m_MotionStartPosition.z + MotionZ);
}