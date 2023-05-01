#pragma once
#include <sstream>
#include <cmath>
#include <algorithm>

class Zone;

enum Education
{
	BASIC,
	INTERMEDIATE,
	ADVANCED
};

class Citizen
{
public:
	Citizen();
	~Citizen();

	//Static Methodes / Members
	static std::string ConvertEducationToString(enum Education e);
	static std::string ToString(Citizen* citizen);
	static std::stringstream LOG;
	static int COUNTER;
	static int MONEY_SATISFACTION;

	//Identification Methodes
	inline bool IsPensioner() const { return m_Age >= 65; }

	//Simulation Methodes
	void JoinZone(Zone* zone);
	void ChangeZone(Zone* zone);
	void DeletedZone(Zone* zone);
	void LeaveResidence();
	void LeaveWorkplace();

	//Getter Methodes
	inline int Get_Age() const { return m_Age; }
	inline float Get_Pension() const { return m_Pension; }
	inline int Get_MonthsBeforePension() const { return m_MonthsBeforePension; }
	inline Education Get_Education() const { return m_Education; }
	inline Zone* Get_Residence() { return m_Residence; }
	inline Zone* Get_Workplace() { return m_Workplace; }

	void Increase_EducationLevel(Education maxEducationLevel = Education::ADVANCED);
	void Downgrade_EducationLevel() { m_Education = Education::BASIC; }
	inline bool HasIntermediateEducationLevel() const { return m_Education == Education::INTERMEDIATE; }
	inline bool HasAdvancedEducationLevel() const { return m_Education == Education::ADVANCED; }

	//Setter Methodes
	inline void Set_Age(int Age) { m_Age = Age; }
	inline void Set_Pension(float Pension) { m_Pension = Pension; }
	inline void Set_MonthsBeforePension(int MonthsBeforePension) { m_MonthsBeforePension = MonthsBeforePension; }
	inline void Set_Education(Education Education) { m_Education = Education; }
	inline void Set_Residence(Zone* Residence) { m_Residence = Residence; }
	inline void Set_Workplace(Zone* Workplace) { m_Workplace = Workplace; }

	//Other Methodes
	void  Increase_Age() { ++m_Age; }
	float PayTax();
	float Calculate_Satisfaction();
	float Calculate_ZoneSatisfaction(Zone* zone);
	float Calculate_Distance(Zone* zone1, Zone* zone2);

private:
	int m_Age;
	int m_MonthsBeforePension;
	float m_Pension;
	Education m_Education;
	Zone* m_Residence;
	Zone* m_Workplace;

	static int MIN_AGE;
	static int MAX_AGE;

	static void WRITE_LOG(std::string str, Citizen* citizen, Zone* zone);
};
