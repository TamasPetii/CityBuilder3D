#include "Car.h"

//Static members of CarGroup//

std::unordered_set<Car*> CarGroup::m_Cars;
std::unordered_set<CarAndCoord*> CarGroup::m_InUseIntersections;

int CarGroup::car_limit = 0;

float CarGroup::last_time;
float CarGroup::current_time;
float CarGroup::delta_time;

//Static members of Car//

HitBox Car::m_HitBox = { glm::vec3(-0.35, 0.0, -0.35), glm::vec3(0.35,0.14,0.35) };

//RouteSection//

void RouteSection::CalculateSegmentLength()
{
	if (Get_NumberOfCoordinates() == 2)
	{
		m_Length = sqrt((m_FirstPoint.coord.x - m_LastPoint.coord.x) * (m_FirstPoint.coord.x - m_LastPoint.coord.x) + (m_FirstPoint.coord.z - m_LastPoint.coord.z) * (m_FirstPoint.coord.z - m_LastPoint.coord.z));
	}
	else if (Get_NumberOfCoordinates() == 3)
	{
		float length = 0.0;
		const int num_segments = 100;

		float t = 0.0;
		glm::vec3 px = m_FirstPoint.coord;
		for (int i = 1; i <= num_segments; i++)
		{
			t = (float)i / num_segments;
			glm::vec3 qx = (1 - t) * m_FirstPoint.coord + t * m_MiddlePoint.coord;
			glm::vec3 rx = (1 - t) * m_MiddlePoint.coord + t * m_LastPoint.coord;
			glm::vec3 sx = (1 - t) * qx + t * rx;
			length += glm::length(sx - px);
			px = sx;
		}

		m_Length = length;
	}
}

RouteSection::RouteSection(CarCoord c1, CarCoord c2)
{
	m_FirstPoint = c1;
	m_LastPoint = c2;
	m_MiddlePoint = { glm::vec3(0), false };
	m_NumberOfCooordinates = 2;

	if (c1.isInterSection || c2.isInterSection)
		m_IsInterSection = true;
	else
		m_IsInterSection = false;
}

RouteSection::RouteSection(CarCoord c1, CarCoord c2, CarCoord c3)
{
	m_FirstPoint = c1;
	m_MiddlePoint = c2;
	m_LastPoint = c3;
	m_NumberOfCooordinates = 3;

	if (c1.isInterSection || c2.isInterSection || c3.isInterSection)
		m_IsInterSection = true;

	else
		m_IsInterSection = false;
}

//Car//

void Car::AdjustCurveCoordinates(glm::vec3& coordinate1, glm::vec3& coordinate2, glm::vec3& coordinate3, float roadCompensation)
{
	//Translating the points, so it looks like the car is moving on the right side of the road

	if (coordinate1.x != coordinate2.x && coordinate1.z == coordinate2.z) //road is along x
	{
		if (coordinate2.x - coordinate1.x > 0) //x increasing
		{
			coordinate1.z += roadCompensation;
			coordinate2.z += roadCompensation;
		}
		else //x decreasing
		{
			coordinate1.z -= roadCompensation;
			coordinate2.z -= roadCompensation;
		}

		if (coordinate3.z > coordinate2.z) //z increasing
		{
			coordinate2.x -= roadCompensation;
			coordinate3.x -= roadCompensation;
		}
		else //z decreasing
		{
			coordinate2.x += roadCompensation;
			coordinate3.x += roadCompensation;
		}
	}
	else if (coordinate1.z != coordinate2.z && coordinate1.x == coordinate2.x) //road is along z
	{
		if (coordinate2.z - coordinate1.z > 0) //z increasing
		{
			coordinate1.x -= roadCompensation;
			coordinate2.x -= roadCompensation;
		}
		else //z decreasing
		{
			coordinate1.x += roadCompensation;
			coordinate2.x += roadCompensation;
		}

		if (coordinate3.x > coordinate2.x) //x inc
		{
			coordinate2.z += roadCompensation;
			coordinate3.z += roadCompensation;
		}
		else //x dec
		{
			coordinate2.z -= roadCompensation;
			coordinate3.z -= roadCompensation;
		}
	}
}

void Car::AdjustStraightCoordinates(glm::vec3& coordinate1, glm::vec3& coordinate2, float roadCompensation)
{
	//Translating the points, so it looks like the car is moving on the right side of the road
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
}

void Car::AddStraightSection(CarCoord coord1, CarCoord coord2, float roadCompensation)
{
	glm::vec3& coordinate1 = coord1.coord;
	glm::vec3& coordinate2 = coord2.coord;
	m_OriginalRouteSections.push_back(new RouteSection(coord1, coord2));
	AdjustStraightCoordinates(coordinate1, coordinate2, roadCompensation);
	m_RouteSections.push_back(new RouteSection({ coordinate1 }, { coordinate2 }));
}

void Car::AddCurveSection(CarCoord coord1, CarCoord coord2, CarCoord coord3, float roadCompensation)
{
	glm::vec3& coordinate1 = coord1.coord;
	glm::vec3& coordinate2 = coord2.coord;
	glm::vec3& coordinate3 = coord3.coord;
	m_OriginalRouteSections.push_back(new RouteSection(coord1, coord2, coord3));
	AdjustCurveCoordinates(coordinate1, coordinate2, coordinate3, roadCompensation);
	m_RouteSections.push_back(new RouteSection({ coordinate1 }, { coordinate2 }, { coordinate3 }));
}

void Car::AddSegmBetwIntersAndCurve(CarCoord coord1, CarCoord coord2, float roadCompensation)
{
	glm::vec3& coordinate1 = coord1.coord;
	glm::vec3& coordinate2 = coord2.coord;
	m_OriginalRouteSections.push_back(new RouteSection(coord1, coord2));
	m_OriginalRouteSections.push_back(new RouteSection(coord2, coord2));
	AdjustStraightCoordinates(coordinate1, coordinate2, roadCompensation);
	m_RouteSections.push_back(new RouteSection({ coordinate1 }, { coordinate2 }));
	m_RouteSections.push_back(new RouteSection({ coordinate2 }, { coordinate2 }));
}

void Car::AddSegmBetwCurveAndInters(CarCoord coord1, CarCoord coord2, CarCoord coord3, CarCoord coord4, CarCoord coord5 ,float roadCompensation)
{
	glm::vec3& coordinate1 = coord1.coord;
	glm::vec3& coordinate2 = coord2.coord;
	glm::vec3& coordinate3 = coord3.coord;

	glm::vec3& coordinate4 = coord4.coord;
	glm::vec3& coordinate5 = coord5.coord;

	m_OriginalRouteSections.push_back(new RouteSection(coord1, coord2, coord3));
	m_OriginalRouteSections.push_back(new RouteSection(coord3, coord3));
	m_OriginalRouteSections.push_back(new RouteSection(coord4, coord5));

	AdjustCurveCoordinates(coordinate1, coordinate2, coordinate3, roadCompensation);
	AdjustStraightCoordinates(coordinate4, coordinate5, roadCompensation);
	m_RouteSections.push_back(new RouteSection({ coordinate1 }, { coordinate2 }, { coordinate3 }));
	m_RouteSections.push_back(new RouteSection({ coordinate3 }, { coordinate3 }));
	m_RouteSections.push_back(new RouteSection({ coordinate4 }, { coordinate5 }));
}

void Car::PrepareRoadSections(std::vector<CarCoord> coordinates)
{
	float roadCompensation = 0.3f;

	int i = 0;

	while (i < coordinates.size())
	{
		if (i + 4 < coordinates.size())
		{
			//two simple curves next to each other (1 common point) (we have to add an aditional straight section between them, so the path remains continous)
			if ((coordinates[i].coord.x != coordinates[i + 2].coord.x && coordinates[i].coord.z != coordinates[i + 2].coord.z) &&
				(coordinates[i + 2].coord.x != coordinates[i + 4].coord.x && coordinates[i + 2].coord.z != coordinates[i + 4].coord.z)
				&& (coordinates[i + 1].coord.x == coordinates[i + 3].coord.x || coordinates[i + 1].coord.z == coordinates[i + 3].coord.z))
			{
				glm::vec3 coordinate1 = coordinates[i].coord;
				glm::vec3 coordinate2 = coordinates[i + 1].coord;
				glm::vec3 coordinate3 = coordinates[i + 2].coord;

				m_OriginalRouteSections.push_back(new RouteSection(coordinates[i], coordinates[i + 1], coordinates[i + 2]));
				m_OriginalRouteSections.push_back(new RouteSection(coordinates[i + 2], coordinates[i + 2]));

				AdjustCurveCoordinates(coordinate1, coordinate2, coordinate3, roadCompensation);
				m_RouteSections.push_back(new RouteSection({ coordinate1 }, { coordinate2 }, { coordinate3 }));
				m_RouteSections.push_back(new RouteSection({ coordinate3 }, { coordinate3 }));

				//std::cout << "1 common point" << std::endl;
				i += 2;
			}
			//curve, than straight section which is part of an intersection
			else if ((coordinates[i].coord.x != coordinates[i + 2].coord.x && coordinates[i].coord.z != coordinates[i + 2].coord.z)
				&& coordinates[i + 3].isInterSection && (coordinates[i + 1].coord.x == coordinates[i + 3].coord.x || coordinates[i + 1].coord.z == coordinates[i + 3].coord.z))
			{
				AddSegmBetwCurveAndInters(coordinates[i], coordinates[i + 1], coordinates[i + 2], coordinates[i + 2], coordinates[i + 3], roadCompensation);
				i += 3;
			}
			//entangled curves (two common point)
			else if ((coordinates[i].coord.x != coordinates[i + 2].coord.x && coordinates[i].coord.z != coordinates[i + 2].coord.z)
				&& (coordinates[i + 1].coord.x != coordinates[i + 3].coord.x && coordinates[i + 1].coord.z != coordinates[i + 3].coord.z))
			{
				AddCurveSection(coordinates[i], coordinates[i + 1], coordinates[i + 2], roadCompensation);
				++i;
			}
			//single curve
			else if ((coordinates[i].coord.x != coordinates[i + 2].coord.x && coordinates[i].coord.z != coordinates[i + 2].coord.z))
			{
				AddCurveSection(coordinates[i], coordinates[i + 1], coordinates[i + 2], roadCompensation);
				i += 2;
			}
			//multiple intersection
			else if (coordinates[i].isInterSection && coordinates[i + 1].isInterSection)
			{
				AddStraightSection(coordinates[i], coordinates[i + 1], roadCompensation);
				++i;
			}
			//intersection, than curve
			else if (coordinates[i].isInterSection &&
				(coordinates[i + 1].coord.x != coordinates[i + 3].coord.x && coordinates[i + 1].coord.z != coordinates[i + 3].coord.z))
			{
				AddSegmBetwIntersAndCurve(coordinates[i], coordinates[i + 1], roadCompensation);
				++i;
			}
			//straight
			else
			{
				AddStraightSection(coordinates[i], coordinates[i + 1], roadCompensation);
				++i;
			}
		}
		else if (i + 3 < coordinates.size())
		{
			//curve, than straight section which is part of an intersection
			if ((coordinates[i].coord.x != coordinates[i + 2].coord.x && coordinates[i].coord.z != coordinates[i + 2].coord.z)
				&& coordinates[i + 3].isInterSection && (coordinates[i + 1].coord.x == coordinates[i + 3].coord.x || coordinates[i + 1].coord.z == coordinates[i + 3].coord.z))
			{
				AddSegmBetwCurveAndInters(coordinates[i], coordinates[i + 1], coordinates[i + 2], coordinates[i + 2],coordinates[i + 3], roadCompensation);
				i += 3;
			}
			//entangled curves (two common point)
			else if ((coordinates[i].coord.x != coordinates[i + 2].coord.x && coordinates[i].coord.z != coordinates[i + 2].coord.z)
				&& (coordinates[i + 1].coord.x != coordinates[i + 3].coord.x && coordinates[i + 1].coord.z != coordinates[i + 3].coord.z))
			{
				AddCurveSection(coordinates[i], coordinates[i + 1], coordinates[i + 2], roadCompensation);
				++i;
			}
			//single curve
			else if ((coordinates[i].coord.x != coordinates[i + 2].coord.x && coordinates[i].coord.z != coordinates[i + 2].coord.z))
			{
				AddCurveSection(coordinates[i], coordinates[i + 1], coordinates[i + 2], roadCompensation);
				i += 2;
			}
			//multiple intersection
			else if (coordinates[i].isInterSection && coordinates[i + 1].isInterSection)
			{
				AddStraightSection(coordinates[i], coordinates[i + 1], roadCompensation);
				++i;
			}
			//intersection, than curve
			else if (coordinates[i].isInterSection &&
				(coordinates[i + 1].coord.x != coordinates[i + 3].coord.x && coordinates[i + 1].coord.z != coordinates[i + 3].coord.z))
			{
				AddSegmBetwIntersAndCurve(coordinates[i], coordinates[i + 1], roadCompensation);
				++i;
			}
			//straight
			else
			{
				AddStraightSection(coordinates[i], coordinates[i + 1], roadCompensation);
				++i;
			}
		}
		else if (i + 2 < coordinates.size())
		{
			//single curve
			if ((coordinates[i].coord.x != coordinates[i + 2].coord.x && coordinates[i].coord.z != coordinates[i + 2].coord.z))
			{
				AddCurveSection(coordinates[i], coordinates[i + 1], coordinates[i + 2], roadCompensation);
				i += 2;
			}
			//multiple intersection
			else if (coordinates[i].isInterSection && coordinates[i + 1].isInterSection)
			{
				AddStraightSection(coordinates[i], coordinates[i + 1], roadCompensation);
				++i;
			}
			//straight
			else
			{
				AddStraightSection(coordinates[i], coordinates[i + 1], roadCompensation);
				++i;
			}
		}
		else if (i + 1 < coordinates.size())
		{
			AddStraightSection(coordinates[i], coordinates[i + 1], roadCompensation);
			++i;
		}
		else
			++i;
	}
}

void Car::CompensateCurves()
{
	//compensation in curves (making the curves shorter)
	for (int i = 0; i < m_RouteSections.size(); ++i)
	{
		if (i < m_RouteSections.size() - 1)
		{
			//if there's a curve after a straight section
			if (m_RouteSections[i]->Get_NumberOfCoordinates() == 2 && m_RouteSections[i + 1]->Get_NumberOfCoordinates() == 3
				&& m_RouteSections[i]->Get_FirstPoint() != m_RouteSections[i]->Get_LastPoint())
			{
				RouteSection* straight = m_RouteSections[i];

				if (straight->Get_FirstPoint().x < straight->Get_LastPoint().x) //x rising
					straight->Increase_LastX(1);

				else if (straight->Get_FirstPoint().x > straight->Get_LastPoint().x) //x decreasing
					straight->Increase_LastX(-1);

				else if (straight->Get_FirstPoint().z < straight->Get_LastPoint().z) //z rising
					straight->Increase_LastZ(1);

				else if (straight->Get_FirstPoint().z > straight->Get_LastPoint().z) //z decreasing
					straight->Increase_LastZ(-1);
			}
			//if a straight section goes through an intersection (the intersection is after the first straight section) (have to do it because of the collsion detection)
			if (m_RouteSections[i]->Get_NumberOfCoordinates() == 2 && m_RouteSections[i + 1]->Get_NumberOfCoordinates() == 2 && m_OriginalRouteSections[i + 1]->Get_IsInterSection())
			{
				RouteSection* straight_first = m_RouteSections[i];
				RouteSection* straight_second = m_RouteSections[i + 1];

				if (straight_first->Get_FirstPoint().x < straight_first->Get_LastPoint().x) //x rising
				{
					straight_first->Increase_LastX(1);
					straight_second->Increase_FirstX(1);
				}
				else if (straight_first->Get_FirstPoint().x > straight_first->Get_LastPoint().x) //x decreasing
				{
					straight_first->Increase_LastX(-1);
					straight_second->Increase_FirstX(-1);
				}
				else if (straight_first->Get_FirstPoint().z < straight_first->Get_LastPoint().z) //z rising
				{
					straight_first->Increase_LastZ(1);
					straight_second->Increase_FirstZ(1);
				}
				else if (straight_first->Get_FirstPoint().z > straight_first->Get_LastPoint().z) //z decreasing
				{
					straight_first->Increase_LastZ(-1);
					straight_second->Increase_FirstZ(-1);
				}
			}
		}
		if (i > 0)
		{
			//if there's a curve before a straight section, the straight section should be extended to reach the shortened curve
			if (m_RouteSections[i]->Get_NumberOfCoordinates() == 2 && m_RouteSections[i - 1]->Get_NumberOfCoordinates() == 3
				&& m_RouteSections[i]->Get_FirstPoint() != m_RouteSections[i]->Get_LastPoint())
			{
				RouteSection* straight = m_RouteSections[i];

				if (straight->Get_FirstPoint().x < straight->Get_LastPoint().x) //x rising
					straight->Increase_FirstX(-1);
				else if (straight->Get_FirstPoint().x > straight->Get_LastPoint().x) //x decreasing
					straight->Increase_FirstX(1);
				else if (straight->Get_FirstPoint().z < straight->Get_LastPoint().z) //z rising
					straight->Increase_FirstZ(-1);
				else if (straight->Get_FirstPoint().z > straight->Get_LastPoint().z) //z decreasing
					straight->Increase_FirstZ(1);
			}
			//if a straight section goes through an inersection (the intersection is before the first straight section) (we have to do it because of the collsion detection)
			if (m_RouteSections[i]->Get_NumberOfCoordinates() == 2 && m_RouteSections[i - 1]->Get_NumberOfCoordinates() == 2 && m_OriginalRouteSections[i - 1]->Get_IsInterSection())
			{
				RouteSection* straight = m_RouteSections[i];
				RouteSection* straight_before = m_RouteSections[i - 1];

				if (straight->Get_FirstPoint().x < straight->Get_LastPoint().x) //x rising
				{
					straight->Increase_FirstX(-1);
					straight_before->Increase_LastX(-1);
				}
				else if (straight->Get_FirstPoint().x > straight->Get_LastPoint().x) //x decreasing
				{
					straight->Increase_FirstX(1);
					straight_before->Increase_LastX(1);
				}
				else if (straight->Get_FirstPoint().z < straight->Get_LastPoint().z) //z rising
				{
					straight->Increase_FirstZ(-1);
					straight_before->Increase_LastZ(-1);
				}
				else if (straight->Get_FirstPoint().z > straight->Get_LastPoint().z) //z decreasing
				{
					straight->Increase_FirstZ(1);
					straight_before->Increase_LastZ(1);
				}
			}
		}
		//curve
		if (m_RouteSections[i]->Get_NumberOfCoordinates() == 3)
		{
			RouteSection* curve_first = m_RouteSections[i];

			if (curve_first->Get_FirstPoint().x < curve_first->Get_MiddlePoint().x) //x rising
			{
				curve_first->Increase_FirstX(1);

				if (curve_first->Get_MiddlePoint().z < curve_first->Get_LastPoint().z) //right
					curve_first->Increase_LastZ(-1);
				else //left
					curve_first->Increase_LastZ(1);
			}
			else if (curve_first->Get_FirstPoint().x > curve_first->Get_MiddlePoint().x) //x decreasing
			{
				curve_first->Increase_FirstX(-1);

				if (curve_first->Get_MiddlePoint().z < curve_first->Get_LastPoint().z) //right
					curve_first->Increase_LastZ(-1);
				else //left
					curve_first->Increase_LastZ(1);
			}
			else if (curve_first->Get_FirstPoint().z < curve_first->Get_MiddlePoint().z) //z rising
			{
				curve_first->Increase_FirstZ(1);

				if (curve_first->Get_MiddlePoint().x < curve_first->Get_LastPoint().x) //up
					curve_first->Increase_LastX(-1);
				else //down
					curve_first->Increase_LastX(1);
			}
			else if (curve_first->Get_FirstPoint().z > curve_first->Get_MiddlePoint().z) //z decreasing
			{
				curve_first->Increase_FirstZ(-1);

				if (curve_first->Get_MiddlePoint().x < curve_first->Get_LastPoint().x) //up
					curve_first->Increase_LastX(-1);
				else //down
					curve_first->Increase_LastX(1);
			}
		}
	}
}

void Car::AdjustAdditionalSegments()
{
	//Adjusting the coordinates of the straight route sections that were added between two neighbouring curves

	for (int i = 1; i < m_RouteSections.size() - 1; ++i)
	{
		if (m_RouteSections[i]->Get_NumberOfCoordinates() == 2
			&& m_RouteSections[i - 1]->Get_NumberOfCoordinates() == 3
			&& m_RouteSections[i + 1]->Get_NumberOfCoordinates() == 3
			&& m_RouteSections[i]->Get_FirstPoint() == m_RouteSections[i]->Get_LastPoint())
		{
			RouteSection* curve_before = m_RouteSections[i - 1];
			RouteSection* straight = m_RouteSections[i];
			RouteSection* curve_after = m_RouteSections[i + 1];

			m_RouteSections[i]->Set_FirstPoint(curve_before->Get_LastPoint());
			m_RouteSections[i]->Set_LastPoint(curve_after->Get_FirstPoint());
			//std::cout << "v1" << std::endl;
		}
		else if (i < m_RouteSections.size() - 2)
		{
			if (m_RouteSections[i]->Get_NumberOfCoordinates() == 3
				&& m_OriginalRouteSections[i + 2]->Get_IsInterSectionLastCoord()
				&& m_RouteSections[i + 1]->Get_NumberOfCoordinates() == 2
				&& m_OriginalRouteSections[i + 2]->Get_NumberOfCoordinates() == 2
				)
			{
				//when theres's an intersection after a curve, we have to modifiy the two straight sections between the intersection and the curve
				glm::vec3 coordinate1 = m_RouteSections[i]->Get_LastPoint(); //will be used as it is

				//coordinate2 will be modified based on the straight sections directions
				//this will be the second coordinate of the section between the curve and the intersection
				//also used as the first coordinate of the second straight section. (this section's last coordinate is  the intersection point)
				glm::vec3 coordinate2 = m_RouteSections[i + 2]->Get_LastPoint();

				float compensation = 1.0f;

				if (i < m_RouteSections.size() - 3)
				{
					if (m_RouteSections[i + 3]->Get_NumberOfCoordinates() == 3)
						compensation = 2.0f;
				}

				if (coordinate2.x > coordinate1.x)
					coordinate2.x -= compensation;
				else if (coordinate2.x < coordinate1.x)
					coordinate2.x += compensation;
				else if (coordinate2.z > coordinate1.z)
					coordinate2.z -= compensation;
				else if (coordinate2.z < coordinate1.z)
					coordinate2.z += compensation;

				m_RouteSections[i + 1]->Set_FirstPoint(coordinate1);
				m_RouteSections[i + 1]->Set_LastPoint(coordinate2);

				m_RouteSections[i + 2]->Set_FirstPoint(coordinate2);
				//std::cout << "v2" << std::endl;
			}
			else if (m_RouteSections[i]->Get_NumberOfCoordinates() == 2
				&& m_RouteSections[i + 1]->Get_NumberOfCoordinates() == 2
				&& m_RouteSections[i + 2]->Get_NumberOfCoordinates() == 3)
			{
				RouteSection* straight_first = m_RouteSections[i];
				RouteSection* straight_second = m_RouteSections[i + 1];
				RouteSection* curve = m_RouteSections[i + 2];

				if (straight_second->Get_FirstPoint() == straight_second->Get_LastPoint())
				{
					glm::vec3 coordinate1 = straight_first->Get_FirstPoint();
					glm::vec3 coordinate2 = straight_first->Get_LastPoint();

					if (coordinate2.x > coordinate1.x)
						coordinate2.x -= 1;
					else if (coordinate2.x < coordinate1.x)
						coordinate2.x += 1;
					else if (coordinate2.z > coordinate1.z)
						coordinate2.z -= 1;
					else if (coordinate2.z < coordinate1.z)
						coordinate2.z += 1;

					m_RouteSections[i]->Set_LastPoint(coordinate2);
					m_RouteSections[i + 1]->Set_FirstPoint(coordinate2);
					m_RouteSections[i + 1]->Set_LastPoint(curve->Get_FirstPoint());
					//std::cout << "v3" << std::endl;
				}
			}
		}
	}
}

Car::Car(std::vector<CarCoord> coordinates)
{
	m_LastMove = static_cast<float>(glfwGetTime());

	PrepareRoadSections(coordinates);
	CompensateCurves();
	AdjustAdditionalSegments();

	//Calculating the length of each RouteSection
	for (int i = 0; i < m_RouteSections.size(); ++i)
		m_RouteSections[i]->CalculateSegmentLength();

	//We push the car until it isn't in an intersection
	bool foundNonIntersection = false;

	for (int i = 0; i < m_OriginalRouteSections.size(); ++i)
	{
		if (!foundNonIntersection)
		{
			if (m_OriginalRouteSections[i]->Get_IsInterSection())
				m_Param += 1.05f;
			else
				foundNonIntersection = true;
		}
	}
}

glm::vec3 Car::Get_CurrentPosition(float& rotation)
{
	int interval = static_cast<int>(m_Param);

	if (interval >= m_RouteSections.size())
		return m_RouteSections[m_RouteSections.size() - 1]->Get_LastPoint();

	float localT = m_Param - interval;

	if (m_RouteSections[static_cast<int>(m_Param)]->Get_NumberOfCoordinates() == 3)
	{
		glm::vec3 der = 2 * (1 - localT) * (m_RouteSections[interval]->Get_MiddlePoint() - m_RouteSections[interval]->Get_FirstPoint()) + 2 * localT * (m_RouteSections[interval]->Get_LastPoint() - m_RouteSections[interval]->Get_MiddlePoint());
		if (m_RouteSections[interval]->Get_FirstPoint().x < m_RouteSections[interval]->Get_LastPoint().x)
			rotation = -glm::atan(der.z, der.x);
		else
			rotation = glm::atan(-der.z, der.x);

		return (1 - localT) * (1 - localT) * m_RouteSections[interval]->Get_FirstPoint() + 2 * (1 - localT) * localT * m_RouteSections[interval]->Get_MiddlePoint() + localT * localT * m_RouteSections[interval]->Get_LastPoint();
	}
	else
	{
		if (m_RouteSections[interval]->Get_FirstPoint().x < m_RouteSections[interval]->Get_LastPoint().x)
			rotation = 0.0f;
		else if (m_RouteSections[interval]->Get_FirstPoint().x > m_RouteSections[interval]->Get_LastPoint().x)
			rotation = static_cast<float>(M_PI);
		else if (m_RouteSections[interval]->Get_FirstPoint().z < m_RouteSections[interval]->Get_LastPoint().z)
			rotation = -static_cast<float>(M_PI) / 2.0f;
		else if (m_RouteSections[interval]->Get_FirstPoint().z > m_RouteSections[interval]->Get_LastPoint().z)
			rotation = static_cast<float>(M_PI) / 2.0f;

		return (1 - localT) * m_RouteSections[interval]->Get_FirstPoint() + localT * m_RouteSections[interval]->Get_LastPoint();
	}
}

void Car::Move(float t)
{
	//(eltelt idõ) * (sebesség) * (útszakasz hossza miatti kompenzáció)
	if (static_cast<int>(m_Param) <= m_RouteSections.size() - 1)
	{
		m_Param += t * (VELOCITY / 200.0f) * (10.0f / m_RouteSections[static_cast<int>(m_Param)]->Get_Length());
		m_LastMove = static_cast<float>(glfwGetTime());
	}
	else
	{
		m_Param += (t * 0.5f);
		m_LastMove = static_cast<float>(glfwGetTime());
	}
}

Car::~Car()
{
	for (int i = 0; i < m_RouteSections.size(); ++i)
	{
		delete(m_RouteSections[i]);
		delete(m_OriginalRouteSections[i]);
	}

	m_RouteSections.clear();
	m_OriginalRouteSections.clear();
}

RouteSection* Car::Get_CurrentRouteSection()
{
	if (static_cast<int>(m_Param) <= m_RouteSections.size() - 1)
		return m_RouteSections[static_cast<int>(m_Param)];
	else
		return nullptr;
}

RouteSection* Car::Get_CurrentOriginalRouteSection()
{
	if (static_cast<int>(m_Param) <= m_RouteSections.size() - 1)
		return m_OriginalRouteSections[static_cast<int>(m_Param)];
	else
		return nullptr;
}

HitBox Car::Get_HitBox()
{
	glm::vec4 min = Get_HitBoxTransform() * glm::vec4(m_HitBox.min, 1);
	glm::vec4 max = Get_HitBoxTransform() * glm::vec4(m_HitBox.max, 1);

	return { glm::vec3(min.x, min.y, min.z), glm::vec3(max.x, max.y, max.z) };
}

//CarGroup//

std::vector<glm::mat4> CarGroup::Get_Transforms()
{
	std::vector<glm::mat4> transforms;

	for (Car* car : m_Cars)
		transforms.push_back(car->Get_Transform());

	return transforms;
}

bool CarGroup::Intersect(Car* car1, Car* car2)
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

void CarGroup::Update()
{
	//ultimate full self-driving system (Elon Musk elbujhat)//

	current_time = static_cast<float>(glfwGetTime());
	delta_time = current_time - last_time;
	last_time = current_time;

	for (auto it = m_Cars.begin(); it != m_Cars.end(); )
	{
		Car* car = *it;

		if (car->ShouldBeDeleted() || (current_time - car->Get_LastMove()) > 20)
		{
			for (auto it_pos = m_InUseIntersections.begin(); it_pos != m_InUseIntersections.end();)
			{
				if ((*it_pos)->Get_Car() == car)
				{
					//std::cout << "1 Intersection liberated when terminated in intersection! " << car << std::endl;
					delete* it_pos;
					it_pos = m_InUseIntersections.erase(it_pos);
				}
				else
					++it_pos;
			}
			//std::cout << "Car deleted: " << car << std::endl;
			delete car;
			it = m_Cars.erase(it);
		}
		else
		{
			bool noCollison = true;

			if (car->Get_CurrentOriginalRouteSection()->Get_IsInterSection())
			{
				bool found = false;

				for (const auto& occupiedIntersection : m_InUseIntersections)
				{
					if (occupiedIntersection->Get_Car() == car)
					{
						found = true;
					}
					else
					{
						if (car->Get_CurrentOriginalRouteSection()->Get_IsInterSectionFirstCoord())
						{
							if (occupiedIntersection->Get_Coord() == car->Get_CurrentOriginalRouteSection()->Get_FirstPoint() && occupiedIntersection->Get_Car() != car)
							{
								found = true;
								noCollison = false;
							}
						}
						if (car->Get_CurrentOriginalRouteSection()->Get_IsInterSectionMiddleCoord())
						{
							if (occupiedIntersection->Get_Coord() == car->Get_CurrentOriginalRouteSection()->Get_MiddlePoint() && occupiedIntersection->Get_Car() != car)
							{
								found = true;
								noCollison = false;
							}
						}
						if (car->Get_CurrentOriginalRouteSection()->Get_IsInterSectionLastCoord())
						{
							if (occupiedIntersection->Get_Coord() == car->Get_CurrentOriginalRouteSection()->Get_LastPoint() && occupiedIntersection->Get_Car() != car)
							{
								found = true;
								noCollison = false;
							}
						}

						int interval = static_cast<int>(car->Get_Param());
						bool intersectionEnded = false;

						//if the car's route contains more intersections one after another, than we have to check if those are occupied. If they're occupied, then we have to stop 'car'.
						for (int i = interval; i < car->Get_NumberOfRouteSections(); ++i)
						{
							if (!intersectionEnded)
							{
								intersectionEnded = !(car->Get_SpecificCurOrigRouteSection(i)->Get_IsInterSection());
							}
							if (!intersectionEnded)
							{
								//std::cout << "Additional routeSections found!" << std::endl;
								if (car->Get_SpecificCurOrigRouteSection(i)->Get_IsInterSectionFirstCoord())
								{
									if (car->Get_SpecificCurOrigRouteSection(i)->Get_FirstPoint() == occupiedIntersection->Get_Coord())
									{
										found = true;
										noCollison = false;
									}
									if (car->Get_SpecificCurOrigRouteSection(i)->Get_MiddlePoint() == occupiedIntersection->Get_Coord())
									{
										found = true;
										noCollison = false;
									}
									if (car->Get_SpecificCurOrigRouteSection(i)->Get_LastPoint() == occupiedIntersection->Get_Coord())
									{
										found = true;
										noCollison = false;
									}
								}
							}
						}
					}
				}
				//if we can't find any car in that intersection than 'car' can occupy the intersection (gets inserted to the set)
				//we have to occupy all the intersections that 'car' will use at the same time, so no other car will disturbe it's way in the intersections
				if (!found)
				{
					int interval = static_cast<int>(car->Get_Param());
					bool intersectionEnded = false;

					for (int i = interval; i < car->Get_NumberOfRouteSections(); ++i)
					{
						if (!intersectionEnded)
						{
							intersectionEnded = !(car->Get_SpecificCurOrigRouteSection(i)->Get_IsInterSection());
							//std::cout << car->Get_SpecificCurOrigRouteSection(i)->Get_IsInterSection() << std::endl;;
						}
						if (!intersectionEnded)
						{
							if (car->Get_SpecificCurOrigRouteSection(i)->Get_IsInterSectionFirstCoord())
							{
								//std::cout << "Intersection occupied! " << car << std::endl;
								m_InUseIntersections.insert(new CarAndCoord(car->Get_SpecificCurOrigRouteSection(i)->Get_FirstPoint(), car));
							}
							if (car->Get_SpecificCurOrigRouteSection(i)->Get_IsInterSectionMiddleCoord())
							{
								//std::cout << "Intersection occupied! " << car << std::endl;
								m_InUseIntersections.insert(new CarAndCoord(car->Get_SpecificCurOrigRouteSection(i)->Get_MiddlePoint(), car));
							}
							if (car->Get_SpecificCurOrigRouteSection(i)->Get_IsInterSectionLastCoord())
							{
								//std::cout << "Intersection occupied! " << car << std::endl;
								m_InUseIntersections.insert(new CarAndCoord(car->Get_SpecificCurOrigRouteSection(i)->Get_LastPoint(), car));
							}
						}
					}
				}
			}
			//if 'car' isn't in any intersection, than we have to liberate the intersections it once used
			else if (!car->Get_CurrentOriginalRouteSection()->Get_IsInterSection())
			{
				for (auto it_pos = m_InUseIntersections.begin(); it_pos != m_InUseIntersections.end();)
				{
					CarAndCoord* pos = *it_pos;
					if (pos->Get_Car() == car)
					{
						//std::cout << "Intersection liberated!" << std::endl;
						delete pos;
						it_pos = m_InUseIntersections.erase(it_pos);
					}
					++it_pos;
				}
			}
			//if 'car' wasn't stopped at any intersection, than we have to check if it collides with any other car's hitbox
			if (noCollison)
			{
				for (const auto& otherCar : m_Cars)
				{
					if (otherCar != car && otherCar != nullptr)
					{
						if (CarGroup::Intersect(car, otherCar))
						{
							//std::cout << "collison" << std::endl;
							if (car->Get_CurrentRouteSection() != nullptr && otherCar->Get_CurrentRouteSection() != nullptr)
							{
								//'car' and 'otherCar' is on the same RouteSection
								if (car->Get_CurrentRouteSection()->Get_FirstPoint() == otherCar->Get_CurrentRouteSection()->Get_FirstPoint()
									&& car->Get_CurrentRouteSection()->Get_LastPoint() == otherCar->Get_CurrentRouteSection()->Get_LastPoint()
									)
								{
									//we stop 'car' if it's closer to it's RouteSection's first point than the 'otherCar' to it's first point
									if (car->Get_LocalParam() < otherCar->Get_LocalParam())
									{
										noCollison = false;
									}
								}
								//'otherCar' is on the RouteSection in front of 'car'
								else if (car->Get_CurrentRouteSection()->Get_LastPoint() == otherCar->Get_CurrentRouteSection()->Get_FirstPoint()
									&& car->Get_CurrentRouteSection()->Get_FirstPoint() != otherCar->Get_CurrentRouteSection()->Get_LastPoint()
									)
								{
									noCollison = false;
								}
							}
						}
					}
				}
			}
			//std::cout << "length: " << m_InUseIntersections.size() << std::endl;
			//moving 'car' if it doesn't collide with anything
			if (noCollison)
			{
				car->Move(delta_time);
			}
			++it;
		}
	}
}

void CarGroup::Add(std::vector<CarCoord> coords)
{
	if (m_Cars.size() < car_limit)
	{
		Car* newCar = new Car(coords);
		bool noCollison = true;

		for (const auto& otherCar : m_Cars)
		{
			if (otherCar != nullptr)
			{
				if (CarGroup::Intersect(newCar, otherCar))
					noCollison = false;
			}
		}

		if (noCollison)
			m_Cars.insert(newCar);
		else
			delete newCar;
	}
}

void CarGroup::Clear()
{
	for (auto it = m_Cars.begin(); it != m_Cars.end(); ++it)
		delete* it;

	m_Cars.clear();

	for (auto it = m_InUseIntersections.begin(); it != m_InUseIntersections.end(); ++it)
		delete* it;

	m_InUseIntersections.clear();
}