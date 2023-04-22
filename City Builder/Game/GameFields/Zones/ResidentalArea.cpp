#include "ResidentalArea.h"

float ResidentalArea::m_Lvl1TaxRate = 20;
float ResidentalArea::m_Lvl2TaxRate = 20;
float ResidentalArea::m_Lvl3TaxRate = 20;
float ResidentalArea::m_LVL1Payment = 350;
float ResidentalArea::m_LVL2Payment = 450;
float ResidentalArea::m_LVL3Payment = 550;

float ResidentalArea::GetTaxRate() const
{
	if (m_details.level == LEVEL_1) { return m_LVL1Payment * (1 - m_Lvl1TaxRate / 100); }
	if (m_details.level == LEVEL_2) { return m_LVL2Payment * (1 - m_Lvl2TaxRate / 100); }
	else { return m_LVL3Payment * (1 - m_Lvl3TaxRate / 100); }
}

Citizen* ResidentalArea::GetRandomDriver()
{
	double probability = (m_details.contain + 1) * 0.001;
	double random = (double)rand() / RAND_MAX;

	if (random < probability)
	{
		//TODO: Random element from unordered set
		return *m_citizens.begin();
	}
	else
		return nullptr;
}