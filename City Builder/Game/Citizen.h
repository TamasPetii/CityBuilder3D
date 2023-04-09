#pragma once

class Zone;

class Citizen
{
public:
	Citizen() {}
	~Citizen() {}

	void JoinZone(Zone* zone);
	void LeaveResidence();
	void LeaveWorkplace();

	void ChangeZone(Zone* zone);
	void DeletedZone(Zone* zone);
	float Get_SatisfactionPoints() const;
	float PayTax() const;

private:
	Zone* m_Residence = nullptr;
	Zone* m_Workplace = nullptr;
	int m_Age = 0;
};
