#include "Car.h"

std::unordered_set<Car*> Cars::m_Cars;

//HitBox Car::m_HitBox = { glm::vec3(-0.25 - 0.2, 0.0, -0.115 - 0.2), glm::vec3(0.3 + 0.2,0.14,0.115 + 0.2) };

HitBox Car::m_HitBox = { glm::vec3(-0.3, 0.0, -0.3), glm::vec3(0.3,0.14,0.3) };

float Cars::last_time;
float Cars::current_time;
float Cars::delta_time;

//RouteSection//

void RouteSection::CalculateSegmentLength()
{
	if (Get_NumberOfCoordinates() == 2)
	{
		m_Length = sqrt((m_FirstPoint.x - m_LastPoint.x) * (m_FirstPoint.x - m_LastPoint.x) + (m_FirstPoint.z - m_LastPoint.z) * (m_FirstPoint.z - m_LastPoint.z));
	}
	else if (Get_NumberOfCoordinates() == 3)
	{
		float length = 0.0;
		const int num_segments = 100;

		float t = 0.0;
		glm::vec3 px = m_FirstPoint;
		for (int i = 1; i <= num_segments; i++)
		{
			t = (float)i / num_segments;
			glm::vec3 qx = (1 - t) * m_FirstPoint + t * m_MiddlePoint;
			glm::vec3 rx = (1 - t) * m_MiddlePoint + t * m_LastPoint;
			glm::vec3 sx = (1 - t) * qx + t * rx;
			length += glm::length(sx - px);
			px = sx;
		}

		m_Length = length;
	}
}

//Car//

Car::Car(std::vector<glm::vec3> coordinates)
{
	float roadCompensation = 0.3f;

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
						coordinate1.z += roadCompensation;
						coordinate2.z += roadCompensation;
					}
					else //x csökk
					{
						coordinate1.z -= roadCompensation;
						coordinate2.z -= roadCompensation;
					}

					if (coordinate3.z > coordinate2.z) //jobbra (z növ)
					{
						coordinate2.x -= roadCompensation;
						coordinate3.x -= roadCompensation;
					}
					else //balra
					{
						coordinate2.x += roadCompensation;
						coordinate3.x += roadCompensation;
					}
				}
				else if (coordinate1.z != coordinate2.z && coordinate1.x == coordinate2.x) //z mentén
				{
					if (coordinate2.z - coordinate1.z > 0) //z növ
					{
						coordinate1.x -= roadCompensation;
						coordinate2.x -= roadCompensation;
					}
					else //z csökk
					{
						coordinate1.x += roadCompensation;
						coordinate2.x += roadCompensation;
					}

					if (coordinate3.x > coordinate2.x)
					{
						coordinate2.z += roadCompensation;
						coordinate3.z += roadCompensation;
					}
					else
					{
						coordinate2.z -= roadCompensation;
						coordinate3.z -= roadCompensation;
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
						coordinate1.z += roadCompensation;
						coordinate2.z += roadCompensation;
					}
					else if (coordinate2.x - coordinate1.x < 0)//Ha x csökken, akkor z-t csökkenõ irányba toljuk
					{
						coordinate1.z -= roadCompensation;
						coordinate2.z -= roadCompensation;
					}
				}
				else if (coordinate1.z != coordinate2.z && coordinate1.x == coordinate2.x)
				{
					if (coordinate2.z - coordinate1.z > 0)
					{
						coordinate1.x -= roadCompensation;
						coordinate2.x -= roadCompensation;
					}
					else if (coordinate2.z - coordinate1.z < 0)
					{
						coordinate1.x += roadCompensation;
						coordinate2.x += roadCompensation;
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
					coordinate1.z += roadCompensation;
					coordinate2.z += roadCompensation;
				}
				else if (coordinate2.x - coordinate1.x < 0)//Ha x csökken, akkor z-t csökkenõ irányba toljuk
				{
					coordinate1.z -= roadCompensation;
					coordinate2.z -= roadCompensation;
				}
			}
			else if (coordinate1.z != coordinate2.z && coordinate1.x == coordinate2.x)
			{
				if (coordinate2.z - coordinate1.z > 0)
				{
					coordinate1.x -= roadCompensation;
					coordinate2.x -= roadCompensation;
				}
				else if (coordinate2.z - coordinate1.z < 0)
				{
					coordinate1.x += roadCompensation;
					coordinate2.x += roadCompensation;
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

	for (int i = 0; i < m_RouteSections.size(); ++i)
	{
		m_RouteSections[i]->CalculateSegmentLength();
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

glm::mat4 Car::Get_HitBoxTransform()
{
	return glm::translate(Get_CurrentPosition(m_Rotation));
}

void Car::Move(float t)
{
	//(eltelt idõ) * (sebesség) * (útszakasz hossza miatti kompenzáció)
	if (static_cast<int>(m_Param) <= m_RouteSections.size() - 1)
	{
		m_Param += t * (VELOCITY / 200.0f) * (10.0f / m_RouteSections[static_cast<int>(m_Param)]->Get_Length());
		m_LastMove = glfwGetTime();
	}
	else
	{
		m_Param += (t * 0.5f);
		m_LastMove = glfwGetTime();
	}
}

Car::~Car()
{
	for (int i = 0; i < m_RouteSections.size(); ++i)
	{
		delete(m_RouteSections[i]);
	}
}

RouteSection* Car::Get_CurrentRouteSection()
{
	if (static_cast<int>(m_Param) <= m_RouteSections.size() - 1)
	{
		return m_RouteSections[static_cast<int>(m_Param)];
	}
	else 
	{
		return nullptr;
	}
}

HitBox Car::Get_HitBox()
{
	glm::vec4 min = Get_HitBoxTransform() * glm::vec4(m_HitBox.min, 1);
	glm::vec4 max = Get_HitBoxTransform() * glm::vec4(m_HitBox.max, 1);

	//std::cout << min.x << "," << min.y << "," << min.z << std::endl;

	return { glm::vec3(min.x, min.y, min.z), glm::vec3(max.x, max.y, max.z) };
}

//Cars//

std::vector<glm::mat4> Cars::Get_Transforms()
{
	std::vector<glm::mat4> transforms;

	for (Car* car : m_Cars)
	{
		transforms.push_back(car->Get_Transform());
	}

	return transforms;
}

bool Cars::Intersect(Car* car1, Car* car2)
{
	HitBox a = car1->Get_HitBox();
	HitBox b = car2->Get_HitBox();

	return a.min.x <= b.max.x &&
		a.max.x >= b.min.x &&
		a.min.y <= b.max.y &&
		a.max.y >= b.min.y &&
		a.min.z <= b.max.z &&
		a.max.z >= b.min.z;
}

void Cars::Update()
{
	//std::cout << m_Cars.size() << std::endl;
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
			bool noCollison = true;

			for (const auto& carPtr : m_Cars)
			{
				float dummy;
				if (carPtr != car)
				{
					if (Cars::Intersect(car,carPtr))
					{
						//std::cout << "collison" << std::endl;
						
						if (car->Get_CurrentRouteSection() != nullptr && carPtr->Get_CurrentRouteSection() != nullptr)
						{
							//Ha ugyanazon útszakaszon vagyunk
							if (car->Get_CurrentRouteSection()->Get_FirstPoint() == carPtr->Get_CurrentRouteSection()->Get_FirstPoint()
								&& car->Get_CurrentRouteSection()->Get_LastPoint() == carPtr->Get_CurrentRouteSection()->Get_LastPoint()
							)
							{
								//std::cout << "ugyanaz" << std::endl;
								if (car->Get_LocalParam() < carPtr->Get_LocalParam())
								{
									noCollison = false;
								}
							}
							//Ha a mi kocsink van késõbbi útszakaszon
							else if (car->Get_CurrentRouteSection()->Get_FirstPoint() == carPtr->Get_CurrentRouteSection()->Get_LastPoint()
							&& car->Get_CurrentRouteSection()->Get_LastPoint() != carPtr->Get_CurrentRouteSection()->Get_FirstPoint()
							)
							{
								//std::cout << "elorebb" << std::endl;
								//ekkor nincs baj, mi jutunk elõre
							}
							//Ha a másik kocsi van késõbbi útszakaszon
							else if (car->Get_CurrentRouteSection()->Get_LastPoint() == carPtr->Get_CurrentRouteSection()->Get_FirstPoint()
							&& car->Get_CurrentRouteSection()->Get_FirstPoint() != carPtr->Get_CurrentRouteSection()->Get_LastPoint()
							)
							{
								//ITT A HIBA
								//std::cout << "hatrebb" << std::endl;
								//noCollison = false;
							}
							// Ha csak az utolsó koordináták eggyeznek, akkor azonos végpontú, különbözõ kanyarokban vagyunk, ekkor a végponthoz közelebbi jut tovább
							else if (car->Get_CurrentRouteSection()->Get_LastPoint() == carPtr->Get_CurrentRouteSection()->Get_LastPoint()
							&& car->Get_CurrentRouteSection()->Get_FirstPoint() != carPtr->Get_CurrentRouteSection()->Get_FirstPoint()
							)
							{
								if (glm::distance(car->Get_CurrentPosition(dummy), car->Get_CurrentRouteSection()->Get_LastPoint())
								> glm::distance(carPtr->Get_CurrentPosition(dummy), carPtr->Get_CurrentRouteSection()->Get_LastPoint())
								)
								{
									noCollison = false;
								}
							}
							//Mint az elõzõ eset, csak elsõ koordinátákkal
							else if (car->Get_CurrentRouteSection()->Get_FirstPoint() == carPtr->Get_CurrentRouteSection()->Get_FirstPoint()
							&& car->Get_CurrentRouteSection()->Get_LastPoint() == carPtr->Get_CurrentRouteSection()->Get_LastPoint()
							)
							{
								if (glm::distance(car->Get_CurrentPosition(dummy), car->Get_CurrentRouteSection()->Get_FirstPoint())
								< glm::distance(carPtr->Get_CurrentPosition(dummy), carPtr->Get_CurrentRouteSection()->Get_FirstPoint())
								)
								{
									noCollison = false;
								}
							}
							else
							{
								if (car->Get_LocalParam() < carPtr->Get_LocalParam())
								{
									noCollison = false;
								}

							}
						}
						else
						{
							if (car->Get_LocalParam() < carPtr->Get_LocalParam())
							{
								noCollison = false;
							}
						}
						
					}
				}
			}

			if (noCollison)
			{
				car->Move(delta_time);
			}
			/*
			else if ((current_time - car->Get_LastMove()) > 3)
			{
				car->Move(0.5);
			}
			*/
			++it;
		}
	}
}

void Cars::Add(std::vector<glm::vec3> coords)
{
	m_Cars.insert(new Car(coords));
}

void Cars::Clear()
{
	for (auto it = m_Cars.begin(); it != m_Cars.end(); ++it)
	{
		delete* it;
	}
	m_Cars.clear();
}