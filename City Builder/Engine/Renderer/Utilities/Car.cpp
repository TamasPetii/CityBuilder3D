#include "Car.h"

std::unordered_set<Car*> Cars::m_Cars = { new Car(
	{
	glm::vec3(3,0,1),
	glm::vec3(5,0,1),
	glm::vec3(7,0,1),
	glm::vec3(9,0,1),
	glm::vec3(9,0,3),
	glm::vec3(9,0,5),
	glm::vec3(9,0,7),
	glm::vec3(9,0,9),
	glm::vec3(9,0,11),
	glm::vec3(7,0,11),
	glm::vec3(5,0,11),
	glm::vec3(3,0,11),
	glm::vec3(1,0,11),
	glm::vec3(1,0,13),
	glm::vec3(1,0,15),
	glm::vec3(1,0,17),
	glm::vec3(3,0,17),
	glm::vec3(5,0,17),
	glm::vec3(7,0,17),
	glm::vec3(9,0,17),
	glm::vec3(9,0,15),
	glm::vec3(9,0,13),
	}
) };

float Cars::last_time;
float Cars::current_time;
float Cars::delta_time;

//CAR//

Car::Car(std::vector<glm::vec3> coordinates)
{
	int i = 0;

	while (i < coordinates.size())
	{
		if (i + 2 < coordinates.size())
		{
			if ((coordinates[i].x != coordinates[i + 2].x && coordinates[i].z != coordinates[i + 2].z))
			{
				//kanyar
				glm::vec3 coordinate1 = coordinates[i];
				glm::vec3 coordinate2 = coordinates[i + 1];
				glm::vec3 coordinate3 = coordinates[i + 2];

				if (coordinate1.x != coordinate2.x && coordinate1.z == coordinate2.z) //x mentén
				{
					if (coordinate2.x - coordinate1.x > 0) //x növ
					{
						coordinate1.z += 0.25f;
						coordinate2.z += 0.25f;
					}
					else //x csökk
					{
						coordinate1.z -= 0.25f;
						coordinate2.z -= 0.25f;
					}

					if (coordinate3.z > coordinate2.z) //jobbra (z növ)
					{
						coordinate2.x -= 0.25f;
						coordinate3.x -= 0.25f;
					}
					else //balra
					{
						coordinate2.x += 0.25f;
						coordinate3.x += 0.25f;
					}
				}
				else if (coordinate1.z != coordinate2.z && coordinate1.x == coordinate2.x) //z mentén
				{
					if (coordinate2.z - coordinate1.z > 0) //z növ
					{
						coordinate1.x -= 0.25f;
						coordinate2.x -= 0.25f;
					}
					else //z csökk
					{
						coordinate1.x += 0.25f;
						coordinate2.x += 0.25f;
					}

					if (coordinate3.x > coordinate2.x)
					{
						coordinate2.z += 0.25f;
						coordinate3.z += 0.25f;
					}
					else
					{
						coordinate2.z -= 0.25f;
						coordinate3.z -= 0.25f;
					}
				}

				m_RouteSections.push_back(new RouteSection(coordinate1, coordinate2, coordinate3));
				i += 2;
			}
			else
			{
				//egyenes
				glm::vec3 coordinate1 = coordinates[i];
				glm::vec3 coordinate2 = coordinates[i + 1];

				if (coordinate1.x != coordinate2.x && coordinate1.z == coordinate2.z)
				{
					if (coordinate2.x - coordinate1.x > 0)//Ha x növekszik, akkor z-t növekvõ irányba toljuk
					{
						coordinate1.z += 0.25f;
						coordinate2.z += 0.25f;
					}
					else if (coordinate2.x - coordinate1.x < 0)//Ha x csökken, akkor z-t csökkenõ irányba toljuk
					{
						coordinate1.z -= 0.25f;
						coordinate2.z -= 0.25f;
					}
				}
				else if (coordinate1.z != coordinate2.z && coordinate1.x == coordinate2.x)
				{
					if (coordinate2.z - coordinate1.z > 0)
					{
						coordinate1.x -= 0.25f;
						coordinate2.x -= 0.25f;
					}
					else if (coordinate2.z - coordinate1.z < 0)
					{
						coordinate1.x += 0.25f;
						coordinate2.x += 0.25f;
					}
				}

				m_RouteSections.push_back(new RouteSection(coordinate1, coordinate2));
				++i;
			}
		}
		else if (i + 1 < coordinates.size())
		{
			//egyenes
			glm::vec3 coordinate1 = coordinates[i];
			glm::vec3 coordinate2 = coordinates[i + 1];

			if (coordinate1.x != coordinate2.x && coordinate1.z == coordinate2.z)
			{
				if (coordinate2.x - coordinate1.x > 0)//Ha x növekszik, akkor z-t növekvõ irányba toljuk
				{
					coordinate1.z += 0.25f;
					coordinate2.z += 0.25f;
				}
				else if (coordinate2.x - coordinate1.x < 0)//Ha x csökken, akkor z-t csökkenõ irányba toljuk
				{
					coordinate1.z -= 0.25f;
					coordinate2.z -= 0.25f;
				}
			}
			else if (coordinate1.z != coordinate2.z && coordinate1.x == coordinate2.x)
			{
				if (coordinate2.z - coordinate1.z > 0)
				{
					coordinate1.x -= 0.25f;
					coordinate2.x -= 0.25f;
				}
				else if (coordinate2.z - coordinate1.z < 0)
				{
					coordinate1.x += 0.25f;
					coordinate2.x += 0.25f;
				}
			}
			m_RouteSections.push_back(new RouteSection(coordinate1, coordinate2));
			++i;
		}
		else
		{
			++i;
		}
	}
}

glm::vec3 Car::Get_CurrentPosition(float& rotation)
{
	int interval = static_cast<int>(m_Param);

	if (interval >= m_RouteSections.size())
	{
		return m_RouteSections[m_RouteSections.size() - 1]->Get_LastPoint();
	}

	float localT = m_Param - interval;

	if (m_RouteSections[static_cast<int>(m_Param)]->Get_NumberOfCoordinates() == 3)
	{
		glm::vec3 der = 2 * (1 - localT) * (m_RouteSections[interval]->Get_MiddlePoint() - m_RouteSections[interval]->Get_FirstPoint()) + 2 * localT * (m_RouteSections[interval]->Get_LastPoint() - m_RouteSections[interval]->Get_MiddlePoint());
		std::cout << der.x << " " << der.y << " " << der.z << std::endl;
		if (m_RouteSections[interval]->Get_FirstPoint().x < m_RouteSections[interval]->Get_LastPoint().x)
			rotation = -glm::atan(der.z, der.x);
		else
			rotation = glm::atan(-der.z, der.x);

		return (1 - localT) * (1 - localT) * m_RouteSections[interval]->Get_FirstPoint() + 2 * (1 - localT) * localT * m_RouteSections[interval]->Get_MiddlePoint() + localT * localT * m_RouteSections[interval]->Get_LastPoint();
	}
	else
	{
		if (m_RouteSections[interval]->Get_FirstPoint().x < m_RouteSections[interval]->Get_LastPoint().x)
			rotation = 0;
		else if (m_RouteSections[interval]->Get_FirstPoint().x > m_RouteSections[interval]->Get_LastPoint().x)
			rotation = M_PI;
		else if (m_RouteSections[interval]->Get_FirstPoint().z < m_RouteSections[interval]->Get_LastPoint().z)
			rotation = -M_PI / 2;
		else if (m_RouteSections[interval]->Get_FirstPoint().z > m_RouteSections[interval]->Get_LastPoint().z)
			rotation = M_PI / 2;

		return (1 - localT) * m_RouteSections[interval]->Get_FirstPoint() + localT * m_RouteSections[interval]->Get_LastPoint();
	}
}

glm::mat4 Car::Get_Transform()
{
	return glm::translate(Get_CurrentPosition(m_Rotation)) * glm::rotate(m_Rotation, glm::vec3(0, 1, 0));
}

void Car::Move(float t)
{
	if (m_Param < m_RouteSections.size())
	{
		if (m_RouteSections[static_cast<int>(m_Param)]->Get_NumberOfCoordinates() == 3)
			m_Param += (t * 0.27f);
		else
			m_Param += (t * 0.5f);
	}
	else {
		m_Param = 0.0f;
	}

	//std::cout << m_Param << std::endl;
}

//CARS//

std::vector<glm::mat4> Cars::Get_Transforms()
{
	std::vector<glm::mat4> transforms;

	for (Car* car : m_Cars)
	{
		transforms.push_back(car->Get_Transform());
	}

	return transforms;
}

void Cars::Update()
{
	current_time = glfwGetTime();
	delta_time = current_time - last_time;
	last_time = current_time;

	for (Car* car : m_Cars)
	{
		car->Move(delta_time);
	}
}