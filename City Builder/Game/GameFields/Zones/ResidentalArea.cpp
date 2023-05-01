#include "ResidentalArea.h"

float ResidentalArea::m_Lvl1TaxRate = 40;
float ResidentalArea::m_Lvl2TaxRate = 40;
float ResidentalArea::m_Lvl3TaxRate = 40;
float ResidentalArea::m_LVL1Payment = 1250;
float ResidentalArea::m_LVL2Payment = 1812;
float ResidentalArea::m_LVL3Payment = 2625;

float ResidentalArea::Calculate_TaxRate() const
{
	switch(m_Level)
	{
	case LEVEL_1: return m_LVL1Payment * (m_Lvl1TaxRate / 100);
	case LEVEL_2: return m_LVL2Payment * (m_Lvl2TaxRate / 100);
	case LEVEL_3: return m_LVL3Payment * (m_Lvl3TaxRate / 100);
	}
}

float ResidentalArea::Calculate_TaxRatePercentage() const
{
	switch (m_Level)
	{
	case LEVEL_1: return m_Lvl1TaxRate;
	case LEVEL_2: return m_Lvl2TaxRate;
	case LEVEL_3: return m_Lvl3TaxRate;
	}
}

float ResidentalArea::Calculate_NormalSatisfaction() const
{

	float Satisfaction = m_Satisfaction + m_IndustrialPenalty;
	float Safety = m_Safety;
	float Forest = m_ForestSatisfaction;

	if (Satisfaction > 5) Satisfaction = 5;
	if (Safety > 1) Safety = 1;
	if (Forest > 1) Forest = 1;

	return Satisfaction / 5 * 0.65 + Safety * 0.2 + Forest * 0.15;
}