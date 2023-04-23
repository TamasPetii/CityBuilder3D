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

float ResidentalArea::GetTaxRatePercentage() const {
	if (m_details.level == LEVEL_1) return m_Lvl1TaxRate;
	if (m_details.level == LEVEL_2) return m_Lvl2TaxRate;
	else return m_Lvl3TaxRate;
}

float ResidentalArea::Get_Satisfaction() const {
	float satisfaction = 0;
	float safety = 0;
	if (m_details.satisfaction + m_details.industrial_penalty < 5) satisfaction += m_details.satisfaction + m_details.industrial_penalty;
	else satisfaction += 5;

	if (m_details.safety < 1) safety += m_details.safety;
	else safety += 1;

	//végsõ elégedettségbe a kiszolgáló épületek 0.7-t számítanak max,
	//a közbiztonság pedig 0.3-at, így 0-tól 1-ig ad ez a függvény vissza
	return satisfaction / 5 * 0.7 + safety * 0.3;
}