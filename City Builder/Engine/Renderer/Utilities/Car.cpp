#include "Car.h"

std::unordered_set<Car*> Cars::m_Cars;

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

	//kompenzáció kanyarokban
	for (int i = 0; i < m_RouteSections.size(); i++)
	{
		//az út után kanyar van
		if (i < m_RouteSections.size() - 1)
		{
			if (m_RouteSections[i]->Get_NumberOfCoordinates() == 2 && m_RouteSections[i + 1]->Get_NumberOfCoordinates() == 3)
			{
				RouteSection* straight = m_RouteSections[i];
				RouteSection* curve = m_RouteSections[i + 1];

				if (straight->Get_FirstPoint().x < straight->Get_LastPoint().x) //x mentén növekvõen vagyunk
				{
					straight->Increase_LastX(1);
					curve->Increase_FirstX(1);
				}
				else if (straight->Get_FirstPoint().x > straight->Get_LastPoint().x) //x mentén csökkenõen vagyunk
				{
					straight->Increase_LastX(-1);
					curve->Increase_FirstX(-1);
				}
				else if (straight->Get_FirstPoint().z < straight->Get_LastPoint().z) //z mentén növekvõen vagyunk
				{
					straight->Increase_LastZ(1);
					curve->Increase_FirstZ(1);
				}
				else if (straight->Get_FirstPoint().z > straight->Get_LastPoint().z) //z mentén csökkenõen vagyunk
				{
					straight->Increase_LastZ(-1);
					curve->Increase_FirstZ(-1);
				}
			}
		}
		if (i > 0)
		{
			if (m_RouteSections[i]->Get_NumberOfCoordinates() == 2 && m_RouteSections[i - 1]->Get_NumberOfCoordinates() == 3)
			{
				RouteSection* straight = m_RouteSections[i];
				RouteSection* curve = m_RouteSections[i - 1];

				if (straight->Get_FirstPoint().x < straight->Get_LastPoint().x) //x mentén növekvõen vagyunk
				{
					straight->Increase_FirstX(-1);
					curve->Increase_LastX(-1);
				}
				else if (straight->Get_FirstPoint().x > straight->Get_LastPoint().x) //x mentén csökkenõen vagyunk
				{
					straight->Increase_FirstX(1);
					curve->Increase_LastX(1);
				}
				else if (straight->Get_FirstPoint().z < straight->Get_LastPoint().z) //z mentén növekvõen vagyunk
				{
					straight->Increase_FirstZ(-1);
					curve->Increase_LastZ(-1);
				}
				else if (straight->Get_FirstPoint().z > straight->Get_LastPoint().z) //z mentén csökkenõen vagyunk
				{
					straight->Increase_FirstZ(1);
					curve->Increase_LastZ(1);
				}
			}
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
		//std::cout << der.x << " " << der.y << " " << der.z << std::endl;
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
	if (m_RouteSections[static_cast<int>(m_Param)]->Get_NumberOfCoordinates() == 3)
		m_Param += (t * 0.5f);
	else
		m_Param += (t * 0.4f);
}

Car::~Car()
{
	for (int i = 0; i < m_RouteSections.size(); ++i)
	{
		delete(m_RouteSections[i]);
	}
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

	for (auto it = m_Cars.begin(); it != m_Cars.end(); )
	{
		Car* car = *it;
		if (car->ShouldBeDeleted())
		{
			delete car;
			it = m_Cars.erase(it);
		}
		else
		{
			car->Move(delta_time);
			++it;
		}
	}
}

void Cars::Add(std::vector<glm::vec3> coords)
{
	m_Cars.insert(new Car(coords));
}