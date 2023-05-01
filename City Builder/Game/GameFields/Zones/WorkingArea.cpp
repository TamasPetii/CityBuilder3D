#include "WorkingArea.h"

float WorkingArea::Calculate_NormalSatisfaction() const {
	float Satisfaction = m_Satisfaction;
	float Safety = m_Safety;
	float Forest = m_ForestSatisfaction;

	if (Satisfaction > 5) Satisfaction = 5;
	if (Safety > 1) Safety = 1;
	if (Forest > 1) Forest = 1;

	return Satisfaction / 5 * 0.65 + Safety * 0.2 + Forest * 0.15;
}

//Industrial area

float IndustrialArea::m_Lvl1TaxRate = 40;
float IndustrialArea::m_Lvl2TaxRate = 40;
float IndustrialArea::m_Lvl3TaxRate = 40;
float IndustrialArea::m_LVL1Payment = 1875;
float IndustrialArea::m_LVL2Payment = 2875;
float IndustrialArea::m_LVL3Payment = 4125;

float IndustrialArea::Calculate_TaxRate() const
{
	switch (m_Level)
	{
	case LEVEL_1: return m_LVL1Payment * (m_Lvl1TaxRate / 100);
	case LEVEL_2: return m_LVL2Payment * (m_Lvl2TaxRate / 100);
	case LEVEL_3: return m_LVL3Payment * (m_Lvl3TaxRate / 100);
	}
}

float IndustrialArea::Calculate_TaxRatePercentage() const
{
	switch (m_Level)
	{
	case LEVEL_1: return m_Lvl1TaxRate;
	case LEVEL_2: return m_Lvl2TaxRate;
	case LEVEL_3: return m_Lvl3TaxRate;
	}
}

//Service area
float ServiceArea::m_Lvl1TaxRate = 40;
float ServiceArea::m_Lvl2TaxRate = 40;
float ServiceArea::m_Lvl3TaxRate = 40;
float ServiceArea::m_LVL1Payment = 2500;
float ServiceArea::m_LVL2Payment = 3750;
float ServiceArea::m_LVL3Payment = 5000;


float ServiceArea::Calculate_TaxRate() const
{
	switch (m_Level)
	{
	case LEVEL_1: return m_LVL1Payment * (m_Lvl1TaxRate / 100);
	case LEVEL_2: return m_LVL2Payment * (m_Lvl2TaxRate / 100);
	case LEVEL_3: return m_LVL3Payment * (m_Lvl3TaxRate / 100);
	}

}

float ServiceArea::Calculate_TaxRatePercentage() const
{
	switch (m_Level)
	{
	case LEVEL_1: return m_Lvl1TaxRate;
	case LEVEL_2: return m_Lvl2TaxRate;
	case LEVEL_3: return m_Lvl3TaxRate;
	}
}