#include "WorkingArea.h"

float WorkingArea::Get_Satisfaction() const {
	if (m_details.safety < 1) return m_details.safety;
	else return 1;
}

//Industrial area

float IndustrialArea::m_Lvl1TaxRate = 20;
float IndustrialArea::m_Lvl2TaxRate = 20;
float IndustrialArea::m_Lvl3TaxRate = 20;
float IndustrialArea::m_LVL1Payment = 1550;
float IndustrialArea::m_LVL2Payment = 1750;
float IndustrialArea::m_LVL3Payment = 2000;

float IndustrialArea::GetTaxRate() const
{
	if (m_details.level == LEVEL_1) { return m_LVL1Payment * (1 - m_Lvl1TaxRate / 100); }
	if (m_details.level == LEVEL_2) { return m_LVL2Payment * (1 - m_Lvl2TaxRate / 100); }
	else { return m_LVL3Payment * (1 - m_Lvl3TaxRate / 100); }
}

float ServiceArea::GetTaxRatePercentage() const {
	if (m_details.level == LEVEL_1) return m_Lvl1TaxRate;
	if (m_details.level == LEVEL_2) return m_Lvl2TaxRate;
	else return m_Lvl3TaxRate;
}

//Service area

float ServiceArea::m_Lvl1TaxRate = 20;
float ServiceArea::m_Lvl2TaxRate = 20;
float ServiceArea::m_Lvl3TaxRate = 20;
float ServiceArea::m_LVL1Payment = 2550;
float ServiceArea::m_LVL2Payment = 2750;
float ServiceArea::m_LVL3Payment = 3000;

float ServiceArea::GetTaxRate() const
{
	if (m_details.level == LEVEL_1) { return m_LVL1Payment * (1 - m_Lvl1TaxRate / 100); }
	if (m_details.level == LEVEL_2) { return m_LVL2Payment * (1 - m_Lvl2TaxRate / 100); }
	else { return m_LVL3Payment * (1 - m_Lvl3TaxRate / 100); }
}

float IndustrialArea::GetTaxRatePercentage() const {
	if (m_details.level == LEVEL_1) return m_Lvl1TaxRate;
	if (m_details.level == LEVEL_2) return m_Lvl2TaxRate;
	else return m_Lvl3TaxRate;
}