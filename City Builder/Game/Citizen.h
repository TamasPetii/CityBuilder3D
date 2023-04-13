#pragma once

#include <sstream>

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
	void ChangeZone(Zone* zone);
	void DeletedZone(Zone* zone);
	void LeaveResidence();
	void LeaveWorkplace();

	float PayTax() const;
	float Get_SatisfactionPoints() const;
	bool inline IsPensioner() const { return m_Age >= 65 ? true : false; }

	inline int Get_Age() const	{ return m_Age;	}
	inline Zone* Get_Residence() const { return m_Residence; }
	inline Zone* Get_Workplace() const { return m_Workplace; }

	static std::string Get_Log() { return log.str(); }
	static std::stringstream& Log() { return log; }
	static bool& Log_Changed() { return log_changed; }
private:
	Zone* m_Residence = nullptr;
	Zone* m_Workplace = nullptr;

	int m_Age = 0;
	Education m_Education;
	
	static bool log_changed;
	static std::stringstream log;
};
