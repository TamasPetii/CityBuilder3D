#include "WorkingArea.h"

//Industrial area

float IndustrialArea::m_Lvl1TaxRate = 20;
float IndustrialArea::m_Lvl2TaxRate = 20;
float IndustrialArea::m_Lvl3TaxRate = 20;

float IndustrialArea::GetTaxRate() const
{
	if (m_details.level == LEVEL_1) { return m_Lvl1TaxRate; }
	if (m_details.level == LEVEL_2) { return m_Lvl2TaxRate; }
	else { return m_Lvl3TaxRate; }
}

//Service area

float ServiceArea::m_Lvl1TaxRate = 20;
float ServiceArea::m_Lvl2TaxRate = 20;
float ServiceArea::m_Lvl3TaxRate = 20;

float ServiceArea::GetTaxRate() const
{
	if (m_details.level == LEVEL_1) { return m_Lvl1TaxRate; }
	if (m_details.level == LEVEL_2) { return m_Lvl2TaxRate; }
	else { return m_Lvl3TaxRate; }
}