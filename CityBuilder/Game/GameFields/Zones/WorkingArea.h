#ifndef WORKINGAREA_H
#define WORKINGAREA_H

#include "Zone.h"
#include <iostream>

class WorkingArea : public Zone
{
protected:
	WorkingArea(Level level, FieldType type, FieldDirection direction, int x, int y) : Zone(level, type, direction, x, y) {}
public:
	~WorkingArea() {}

	bool inline IsWorkingArea() const override { return true; }
	virtual inline bool IsIndustrialArea() const { return false; }
	virtual inline bool IsServiceArea() const { return false; }
	float Calculate_NormalSatisfaction() const override;
};

class IndustrialArea : public WorkingArea 
{
public:
	IndustrialArea(Level level, FieldType type, FieldDirection direction, int x, int y) : WorkingArea(level, type, direction, x, y) {}
	~IndustrialArea() {}

	bool inline IsIndustrialArea() const override{ return true; }

	//Setter
	static void inline SetLvl1TaxRate(float taxRate) { m_Lvl1TaxRate = taxRate; }
	static void inline SetLvl2TaxRate(float taxRate) { m_Lvl2TaxRate = taxRate; }
	static void inline SetLvl3TaxRate(float taxRate) { m_Lvl3TaxRate = taxRate; }

	//Getter
	float Calculate_TaxRate() const override;
	float Calculate_TaxRatePercentage() const override;

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
	ServiceArea(Level level, FieldType type, FieldDirection direction, int x, int y) : WorkingArea(level, type, direction, x, y) {}
	~ServiceArea() {}

	bool inline IsServiceArea() const override { return true; }

	//Setter
	static void inline SetLvl1TaxRate(float taxRate) { m_Lvl1TaxRate = taxRate; }
	static void inline SetLvl2TaxRate(float taxRate) { m_Lvl2TaxRate = taxRate; }
	static void inline SetLvl3TaxRate(float taxRate) { m_Lvl3TaxRate = taxRate; }

	//Getter
	float Calculate_TaxRate() const override;
	float Calculate_TaxRatePercentage() const override;

private:
	static float m_Lvl1TaxRate;
	static float m_Lvl2TaxRate;
	static float m_Lvl3TaxRate;
	static float m_LVL1Payment;
	static float m_LVL2Payment;
	static float m_LVL3Payment;
};

#endif
