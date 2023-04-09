#pragma once

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
	~Citizen() {}

	void JoinZone(Zone* zone);
	void LeaveZone(Zone* zone);
	void ChangeZone(Zone* zone);
	void DeleteZone(Zone* zone);
	float Get_SatisfactionPoints() const;
	float PayTax() const;
	bool inline IsPensioner() const { return m_Age >= 65 ? true : false; }

private:
	Zone* m_Residence = nullptr;
	Zone* m_Workplace = nullptr;
	int m_Age = 0;
	Education m_Education;
};
