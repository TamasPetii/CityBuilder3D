#ifndef RESIDENTALAREA_H
#define RESIDENTALAREA_H

#include "Zone.h"

class ResidentalArea : public Zone
{
public:
	ResidentalArea(Level level, FieldType type, FieldDirection direction, int x, int y) : Zone(level, type, direction, x, y) {}
	~ResidentalArea() {}

	bool inline IsResidentalArea() const override { return true; }

	//Setter
	static void inline SetLvl1TaxRate(float taxRate) { m_Lvl1TaxRate = taxRate; }
	static void inline SetLvl2TaxRate(float taxRate) { m_Lvl2TaxRate = taxRate; }
	static void inline SetLvl3TaxRate(float taxRate) { m_Lvl3TaxRate = taxRate; }

	//Getter
	float Calculate_TaxRate() const override;
	float Calculate_TaxRatePercentage() const override;
	float Calculate_NormalSatisfaction() const override;

private:
	static float m_Lvl1TaxRate;
	static float m_Lvl2TaxRate;
	static float m_Lvl3TaxRate;
	static float m_LVL1Payment;
	static float m_LVL2Payment;
	static float m_LVL3Payment;
};

#endif

