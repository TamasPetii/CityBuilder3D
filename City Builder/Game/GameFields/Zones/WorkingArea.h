#ifndef WORKINGAREA_H
#define WORKINGAREA_H

#include "Zone.h"

class WorkingArea : public Zone
{
protected:
	WorkingArea(Level level, FieldType type, int x, int y, float cost) : Zone(level, type, x, y, cost) {}
public:
	~WorkingArea() {}

	bool inline IsWorkingArea() const override { return true; }
	virtual inline bool IsIndustrialArea() const { return false; }
	virtual inline bool IsServiceArea() const { return false; }
};

class IndustrialArea : public WorkingArea 
{
public:
	IndustrialArea(Level level, FieldType type, int x, int y, float cost) : WorkingArea(level, type, x, y, cost) {}
	~IndustrialArea() {}

	bool inline IsIndustrialArea() const override{ return true; }

	//Setter
	static void inline SetLvl1TaxRate(float taxRate) { m_Lvl1TaxRate = taxRate; }
	static void inline SetLvl2TaxRate(float taxRate) { m_Lvl2TaxRate = taxRate; }
	static void inline SetLvl3TaxRate(float taxRate) { m_Lvl3TaxRate = taxRate; }

	//Getter
	float GetTaxRate() const override;

private:
	static float m_Lvl1TaxRate;
	static float m_Lvl2TaxRate;
	static float m_Lvl3TaxRate;
	static float m_LVL1Payment;
	static float m_LVL2Payment;
	static float m_LVL3Payment;
};

class ServiceArea : public WorkingArea
{
public:
	ServiceArea(Level level, FieldType type, int x, int y, float cost) : WorkingArea(level, type, x, y, cost) {}
	~ServiceArea() {}

	bool inline IsServiceArea() const override { return true; }

	//Setter
	static void inline SetLvl1TaxRate(float taxRate) { m_Lvl1TaxRate = taxRate; }
	static void inline SetLvl2TaxRate(float taxRate) { m_Lvl2TaxRate = taxRate; }
	static void inline SetLvl3TaxRate(float taxRate) { m_Lvl3TaxRate = taxRate; }

	//Getter
	float GetTaxRate() const override;

private:
	static float m_Lvl1TaxRate;
	static float m_Lvl2TaxRate;
	static float m_Lvl3TaxRate;
	static float m_LVL1Payment;
	static float m_LVL2Payment;
	static float m_LVL3Payment;
};

#endif
