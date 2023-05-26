#include "../Game/City.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("ASD")
{
    City* city = new City(50);
    CHECK(city->Get_GameTableSize() == 50);
}

TEST_CASE("JOIN-DELETE-CHANGE")
{
    City* city2 = new City(5, 10000000, 1);
    city2->Set_GameTableValue(1, 1, RESIDENTIAL_LVL1, FRONT);
    city2->Set_GameTableValue(2, 1, ROAD, FRONT);
    city2->Set_GameTableValue(3, 1, ROAD, FRONT);
    city2->Set_GameTableValue(4, 1, SERVICE_LVL1, FRONT);

    CHECK(city2->Get_CitizenSize() == 0);

    Citizen* citizen2 = new Citizen();

    CHECK(dynamic_cast<Zone*>(city2->Get_GameField(1, 1))->Get_Contain() == 0);

    city2->JoinCity(citizen2);

    CHECK(city2->Get_CitizenSize() == 1);

    CHECK(citizen2->Get_Residence()->Get_Contain() == 1);
    CHECK(citizen2->Get_Residence() == dynamic_cast<Zone*>(city2->Get_GameField(1, 1)));

    CHECK(citizen2->Get_Workplace()->Get_Contain() == 1);
    CHECK(citizen2->Get_Workplace() == dynamic_cast<Zone*>(city2->Get_GameField(4, 1)));

    city2->LeaveCity(citizen2);

    CHECK((dynamic_cast<Zone*>(city2->Get_GameField(1, 1)))->Get_Contain() == 0);
    CHECK((dynamic_cast<Zone*>(city2->Get_GameField(4, 1)))->Get_Contain() == 0);

    CHECK(city2->Get_CitizenSize() == 0);

    delete city2;
}

TEST_CASE("TAX RATE - PAYTAX")
{
    City* city = new City(5, 10000000, 1);

    city->Set_GameTableValue(1, 1, RESIDENTIAL_LVL1, FRONT);
    city->Set_GameTableValue(2, 2, INDUSTRIAL_LVL1, FRONT);
    city->Set_GameTableValue(3, 3, SERVICE_LVL1, FRONT);

    //----Residential zone tax rate----
    //LVL1

    Citizen* citizen = new Citizen();
    citizen->JoinZone(dynamic_cast<Zone*>(city->Get_GameField(1, 1)));

    float lvl1Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(RESIDENTIAL_LVL1, 60);
    float lvl1Tax60 = citizen->PayTax();

    CHECK(lvl1Tax60 > lvl1Tax40);

    //checking if the 20% tax payed by the citizen is lower than the 40% one
    city->Set_TaxRate(RESIDENTIAL_LVL1, 20);
    float lvl1Tax20 = citizen->PayTax();

    CHECK(lvl1Tax20 < lvl1Tax40);

    //LVL2

    city->UpgradeField(1, 1);

    float lvl2Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(RESIDENTIAL_LVL2, 60);
    float lvl2Tax60 = citizen->PayTax();

    CHECK(lvl2Tax60 > lvl2Tax40);

    //checking if the 20% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(RESIDENTIAL_LVL2, 20);
    float lvl2Tax20 = citizen->PayTax();

    CHECK(lvl2Tax20 < lvl2Tax40);

    //LVL3

    city->UpgradeField(1, 1);

    float lvl3Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(RESIDENTIAL_LVL3, 60);
    float lvl3Tax60 = citizen->PayTax();

    CHECK(lvl3Tax60 > lvl3Tax40);

    //checking if the 20% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(RESIDENTIAL_LVL3, 20);
    float lvl3Tax20 = citizen->PayTax();

    CHECK(lvl3Tax20 < lvl3Tax40);

    //----Industrial zone tax rate----
    //LVL1

    citizen = new Citizen();
    citizen->JoinZone(dynamic_cast<Zone*>(city->Get_GameField(2, 2)));

    lvl1Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(INDUSTRIAL_LVL1, 60);
    lvl1Tax60 = citizen->PayTax();

    CHECK(lvl1Tax60 > lvl1Tax40);

    //checking if the 20% tax payed by the citizen is lower than the 40% one
    city->Set_TaxRate(INDUSTRIAL_LVL1, 20);
    lvl1Tax20 = citizen->PayTax();

    CHECK(lvl1Tax20 < lvl1Tax40);

    //LVL2

    city->UpgradeField(2, 2);

    lvl2Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(INDUSTRIAL_LVL2, 60);
    lvl2Tax60 = citizen->PayTax();

    CHECK(lvl2Tax60 > lvl2Tax40);

    //checking if the 20% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(INDUSTRIAL_LVL2, 20);
    lvl2Tax20 = citizen->PayTax();

    CHECK(lvl2Tax20 < lvl2Tax40);

    //LVL3

    city->UpgradeField(2, 2);

    lvl3Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(INDUSTRIAL_LVL3, 60);
    lvl3Tax60 = citizen->PayTax();

    CHECK(lvl3Tax60 > lvl3Tax40);

    //checking if the 20% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(INDUSTRIAL_LVL3, 20);
    lvl3Tax20 = citizen->PayTax();

    CHECK(lvl3Tax20 < lvl3Tax40);

    //----Serivce zone tax rate----
     //LVL1

    citizen = new Citizen();
    citizen->JoinZone(dynamic_cast<Zone*>(city->Get_GameField(3, 3)));

    lvl1Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(SERVICE_LVL1, 60);
    lvl1Tax60 = citizen->PayTax();

    CHECK(lvl1Tax60 > lvl1Tax40);

    //checking if the 20% tax payed by the citizen is lower than the 40% one
    city->Set_TaxRate(SERVICE_LVL1, 20);
    lvl1Tax20 = citizen->PayTax();

    CHECK(lvl1Tax20 < lvl1Tax40);

    //LVL2

    city->UpgradeField(3, 3);

    lvl2Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(SERVICE_LVL2, 60);
    lvl2Tax60 = citizen->PayTax();

    CHECK(lvl2Tax60 > lvl2Tax40);

    //checking if the 20% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(SERVICE_LVL2, 20);
    lvl2Tax20 = citizen->PayTax();

    CHECK(lvl2Tax20 < lvl2Tax40);

    //LVL3

    city->UpgradeField(3, 3);

    lvl3Tax40 = citizen->PayTax();

    //checking if the 60% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(SERVICE_LVL3, 60);
    lvl3Tax60 = citizen->PayTax();

    CHECK(lvl3Tax60 > lvl3Tax40);

    //checking if the 20% tax payed by the citizen is higher than the 40% one
    city->Set_TaxRate(SERVICE_LVL3, 20);
    lvl3Tax20 = citizen->PayTax();

    CHECK(lvl3Tax20 < lvl3Tax40);

    delete citizen;
    delete city;
}


TEST_CASE("COLLECT MONTHLY TAX")
{
    City* city = new City(5, 10000000, 1);

    city->Set_GameTableValue(1, 1, RESIDENTIAL_LVL1, FRONT);
    city->Set_GameTableValue(1, 2, ROAD, FRONT);
    city->Set_GameTableValue(2, 2, INDUSTRIAL_LVL1, FRONT);

    Citizen* citizen = new Citizen();
    city->JoinCity(citizen);

    //If citizen isn't a pensioner
    int balanceBeforeTax = city->Get_Money();
    city->CollectMonthlyTax();
    int balanceWithTax = city->Get_Money();

    CHECK(balanceBeforeTax < balanceWithTax);

    //If citizen is a pensioner
    citizen->Set_Age(65);
    city->CollectMonthlyTax();
    int balanceWithPension = city->Get_Money();

    CHECK(balanceWithPension < balanceWithTax);

    delete citizen;
    delete city;
}

TEST_CASE("PENSION")
{
    City* city = new City(50);

    city->Set_GameTableValue(1, 1, RESIDENTIAL_LVL1, FRONT);

    Citizen* citizen = new Citizen();
    citizen->Set_Age(64);

    citizen->JoinZone(dynamic_cast<Zone*>(city->Get_GameField(1, 1)));

    citizen->PayTax();
    citizen->Set_Age(65);

    float basicPension = citizen->PayTax();

    CHECK(basicPension < 0);

    //Intermediate pension should be lower (pension is negative tax) than the basic

    Citizen* citizen2 = new Citizen();

    citizen2->Set_Education(INTERMEDIATE);
    citizen2->Set_Age(64);

    citizen2->JoinZone(dynamic_cast<Zone*>(city->Get_GameField(1, 1)));

    citizen2->PayTax();
    citizen2->Set_Age(65);

    float intermPension = citizen2->PayTax();

    CHECK(intermPension < basicPension);

    //Advanced pension should be lower (pension is negative tax) than the intermediate

    Citizen* citizen3 = new Citizen();

    citizen3->Set_Education(ADVANCED);
    citizen3->Set_Age(64);

    citizen3->JoinZone(dynamic_cast<Zone*>(city->Get_GameField(1, 1)));

    citizen3->PayTax();
    citizen3->Set_Age(65);

    float advancedPension = citizen3->PayTax();

    CHECK(advancedPension < intermPension);

    delete citizen3;
    delete citizen2;
    delete citizen;
    delete city;
}

TEST_CASE("PATH FINDER")
{
    GameTable* gameTable = new GameTable(50);

    gameTable->Set_TableValue(1, 1, RESIDENTIAL_LVL1, FRONT);
    gameTable->Set_TableValue(2, 1, ROAD, FRONT);
    gameTable->Set_TableValue(3, 1, ROAD, FRONT);
    gameTable->Set_TableValue(3, 2, ROAD, FRONT);
    gameTable->Set_TableValue(3, 3, ROAD, FRONT);
    gameTable->Set_TableValue(3, 4, RESIDENTIAL_LVL2, FRONT);
    gameTable->Set_TableValue(4, 1, ROAD, FRONT);
    gameTable->Set_TableValue(5, 1, INDUSTRIAL_LVL1, FRONT);

    std::vector<Point> pathShouldBe1 = { {2,1}, {3,1}, {4,1} };
    std::vector<Point> path1 = gameTable->PathFinder({ 2,1 }, { 5,1 });

    std::vector<Point> pathShouldBe2 = { {2,1}, {3,1}, {3,2}, {3,3} };
    std::vector<Point> path2 = gameTable->PathFinder({ 2,1 }, { 3,4 });

    CHECK(pathShouldBe1.size() == path1.size());
    CHECK(pathShouldBe2.size() == path2.size());

    CHECK(!path2[0].isInterSection);
    CHECK(path2[1].isInterSection);
    CHECK(!path2[2].isInterSection);

    delete gameTable;
}

TEST_CASE("BUILDINGS BASIC FUNCTIONS")
{
    Building* building = new Building(STADIUM, LEFT, 0, 0);
    CHECK(Building::ToString(building) != "");
    CHECK(building->IsBuilding());
    CHECK(!building->IsPoliceStation());
    CHECK(!building->IsFireStation());
    CHECK(!building->IsPowerWire());
    CHECK(!building->IsPowerStation());
    CHECK(!building->IsSchool());
    CHECK(!building->IsStadium());
    CHECK(building->GetBuildingSatisfaction() == 0);

    Stadium* field = dynamic_cast<Stadium*>(GameField::CreateField(STADIUM, LEFT, 0, 0));
    CHECK(field->IsBuilding());
    CHECK(field->IsStadium());
    CHECK(field->GetBuildingSatisfaction() == 2);
    delete field;

    HighSchool* highschool = dynamic_cast<HighSchool*>(GameField::CreateField(HIGHSCHOOL, LEFT, 0, 0));
    CHECK(highschool->IsBuilding());
    CHECK(highschool->IsSchool());
    CHECK(highschool->IsHighSchool());
    CHECK(!highschool->IsUniversity());
    CHECK(highschool->GetBuildingSatisfaction() == 1);
    delete highschool;

    University* university = dynamic_cast<University*>(GameField::CreateField(UNIVERSITY, LEFT, 0, 0));
    CHECK(university->IsBuilding());
    CHECK(university->IsSchool());
    CHECK(!university->IsHighSchool());
    CHECK(university->IsUniversity());
    CHECK(university->GetBuildingSatisfaction() == 1);
    delete university;

    PowerWire* powerWire = dynamic_cast<PowerWire*>(GameField::CreateField(POWERWIRE, LEFT, 0, 0));
    CHECK(powerWire->IsBuilding());
    CHECK(powerWire->IsPowerWire());
    CHECK(powerWire->GetBuildingSatisfaction() == 0);
    delete powerWire;

    PowerStation* powerStation = dynamic_cast<PowerStation*>(GameField::CreateField(POWERSTATION, LEFT, 0, 0));
    CHECK(powerStation->IsBuilding());
    CHECK(powerStation->IsPowerStation());
    CHECK(powerStation->GetBuildingSatisfaction() == 1);
    delete powerStation;

    FireStation* fireStation = dynamic_cast<FireStation*>(GameField::CreateField(FIRESTATION, LEFT, 0, 0));
    CHECK(fireStation->IsBuilding());
    CHECK(fireStation->IsFireStation());
    CHECK(fireStation->GetBuildingSatisfaction() == 1);
    delete fireStation;

    PoliceStation* policeStation = dynamic_cast<PoliceStation*>(GameField::CreateField(POLICESTATION, LEFT, 0, 0));
    CHECK(policeStation->IsBuilding());
    CHECK(policeStation->IsPoliceStation());
    CHECK(policeStation->GetBuildingSatisfaction() == 0);
    delete policeStation;
}

TEST_CASE("GENERAL BASIC FUNCTIONS")
{
    Road* road = dynamic_cast<Road*>(GameField::CreateField(ROAD, LEFT, 0, 0));
    CHECK(road->IsRoad());
    delete road;

    Lake* lake = dynamic_cast<Lake*>(GameField::CreateField(LAKE, LEFT, 0, 0));
    CHECK(lake->IsLake());
    delete lake;

    Empty* empty = dynamic_cast<Empty*>(GameField::CreateField(EMPTY, LEFT, 0, 0));
    CHECK(empty->IsEmpty());
    delete empty;

    Crater* crater = dynamic_cast<Crater*>(GameField::CreateField(CRATER, LEFT, 0, 0));
    CHECK(crater->IsCrater());
    delete crater;

    Forest* forest = dynamic_cast<Forest*>(GameField::CreateField(FOREST, LEFT, 0, 0));
    CHECK(forest->IsForest());
    CHECK(forest->Get_Age() == 0);
    forest->Set_Age(10);
    CHECK(forest->Get_Age() == 10);
    forest->Increase_Age();
    CHECK(forest->Get_Age() == 11);
    CHECK(forest->Get_SatisfactionPoints() == forest->Get_Booster() * forest->Get_Age());
    delete forest;
}

TEST_CASE("ZONE BASIC FUNCTIONS")
{
    //RESIDENTIAL AREA
    ResidentalArea* residentialArea = dynamic_cast<ResidentalArea*>(GameField::CreateField(RESIDENTIAL_LVL1, LEFT, 0, 0));
    CHECK(residentialArea->IsZone());
    CHECK(residentialArea->IsResidentalArea());
    CHECK(!residentialArea->IsWorkingArea());

    residentialArea->Set_Capacity(10);
    residentialArea->Set_Contain(10);
    residentialArea->Set_Satisfaction(10);
    residentialArea->Set_Safety(10);
    residentialArea->Set_IndustrialPenalty(10);
    residentialArea->Set_Level(LEVEL_3);
    residentialArea->Set_ForestSatisfaction(10);

    CHECK((int)residentialArea->Get_Capacity() == 10);
    CHECK((int)residentialArea->Get_Contain() == 10);
    CHECK((int)residentialArea->Get_Satisfaction() == 10);
    CHECK((int)residentialArea->Get_Safety() == 10);
    CHECK((int)residentialArea->Get_IndustrialPenalty() == 10);
    CHECK(residentialArea->Get_Level() == LEVEL_3);
    CHECK((int)residentialArea->Get_ForestSatisfaction() == 10);

    residentialArea->Set_Capacity(10);
    residentialArea->Set_Contain(0);
    CHECK(residentialArea->IsThereEmptySpace());
    residentialArea->Set_Contain(10);
    CHECK(!residentialArea->IsThereEmptySpace());

    residentialArea->Add_Satisfaction(1);
    residentialArea->Add_Safety(1);
    residentialArea->Add_IndustrialPenalty(1);
    residentialArea->Add_ForestSatisfaction(1);
    CHECK(residentialArea->Get_Satisfaction() >= 10);
    CHECK(residentialArea->Get_Safety() >= 10);
    CHECK(residentialArea->Get_IndustrialPenalty() >= 10);
    CHECK(residentialArea->Get_ForestSatisfaction() >= 10);

    //WORKING AREA
    IndustrialArea* industrialArea = dynamic_cast<IndustrialArea*>(GameField::CreateField(INDUSTRIAL_LVL1, LEFT, 0, 0));
    CHECK(industrialArea->IsZone());
    CHECK(industrialArea->IsWorkingArea());
    CHECK(industrialArea->IsIndustrialArea());
    CHECK(!industrialArea->IsResidentalArea());

    industrialArea->Set_Capacity(10);
    industrialArea->Set_Contain(10);
    industrialArea->Set_Satisfaction(10);
    industrialArea->Set_Safety(10);
    industrialArea->Set_IndustrialPenalty(10);
    industrialArea->Set_Level(LEVEL_3);
    industrialArea->Set_ForestSatisfaction(10);

    CHECK((int)industrialArea->Get_Capacity() == 10);
    CHECK((int)industrialArea->Get_Contain() == 10);
    CHECK((int)industrialArea->Get_Satisfaction() == 10);
    CHECK((int)industrialArea->Get_Safety() == 10);
    CHECK((int)industrialArea->Get_IndustrialPenalty() == 10);
    CHECK(industrialArea->Get_Level() == LEVEL_3);
    CHECK((int)industrialArea->Get_ForestSatisfaction() == 10);

    industrialArea->Set_Capacity(10);
    industrialArea->Set_Contain(0);
    CHECK(industrialArea->IsThereEmptySpace());
    industrialArea->Set_Contain(10);
    CHECK(!industrialArea->IsThereEmptySpace());

    //Add Methodes
    industrialArea->Add_Satisfaction(1);
    industrialArea->Add_Safety(1);
    industrialArea->Add_IndustrialPenalty(1);
    industrialArea->Add_ForestSatisfaction(1);
    CHECK(industrialArea->Get_Satisfaction() >= 10);
    CHECK(industrialArea->Get_Safety() >= 10);
    CHECK(industrialArea->Get_IndustrialPenalty() >= 10);
    CHECK(industrialArea->Get_ForestSatisfaction() >= 10);

    //WORKING AREA
    ServiceArea* serviceArea = dynamic_cast<ServiceArea*>(GameField::CreateField(SERVICE_LVL1, LEFT, 0, 0));
    CHECK(serviceArea->IsZone());
    CHECK(serviceArea->IsWorkingArea());
    CHECK(serviceArea->IsServiceArea());
    CHECK(!serviceArea->IsResidentalArea());

    serviceArea->Set_Capacity(10);
    serviceArea->Set_Contain(10);
    serviceArea->Set_Satisfaction(10);
    serviceArea->Set_Safety(10);
    serviceArea->Set_IndustrialPenalty(10);
    serviceArea->Set_Level(LEVEL_3);
    serviceArea->Set_ForestSatisfaction(10);

    CHECK((int)serviceArea->Get_Capacity() == 10);
    CHECK((int)serviceArea->Get_Contain() == 10);
    CHECK((int)serviceArea->Get_Satisfaction() == 10);
    CHECK((int)serviceArea->Get_Safety() == 10);
    CHECK((int)serviceArea->Get_IndustrialPenalty() == 10);
    CHECK(serviceArea->Get_Level() == LEVEL_3);
    CHECK((int)serviceArea->Get_ForestSatisfaction() == 10);

    serviceArea->Set_Capacity(10);
    serviceArea->Set_Contain(0);
    CHECK(serviceArea->IsThereEmptySpace());
    serviceArea->Set_Contain(10);
    CHECK(!serviceArea->IsThereEmptySpace());

    //Add Methodes
    serviceArea->Add_Satisfaction(1);
    serviceArea->Add_Safety(1);
    serviceArea->Add_IndustrialPenalty(1);
    serviceArea->Add_ForestSatisfaction(1);
    CHECK(serviceArea->Get_Satisfaction() >= 10);
    CHECK(serviceArea->Get_Safety() >= 10);
    CHECK(serviceArea->Get_IndustrialPenalty() >= 10);
    CHECK(serviceArea->Get_ForestSatisfaction() >= 10);
}

TEST_CASE("1x2/2x2 Fields")
{
    City* city = new City(10, 1, 1);

    //Normal 2x2 field on the table
    city->Set_GameTableValue(0, 0, STADIUM, LEFT);
    CHECK(city->Get_GameField(0, 0)->Get_Type() == STADIUM);
    CHECK(city->Get_GameField(0, 1)->Get_Type() == STADIUM);
    CHECK(city->Get_GameField(1, 0)->Get_Type() == STADIUM);
    CHECK(city->Get_GameField(1, 1)->Get_Type() == STADIUM);

    //2x2 field on the sides
    city->Set_GameTableValue(9, 9, STADIUM, LEFT);
    CHECK(city->Get_GameField(9, 9)->Get_Type() != STADIUM);
    city->Set_GameTableValue(9, 0, STADIUM, LEFT);
    CHECK(city->Get_GameField(9, 0)->Get_Type() != STADIUM);
    city->Set_GameTableValue(0, 9, STADIUM, LEFT);
    CHECK(city->Get_GameField(0, 9)->Get_Type() != STADIUM);

    //Normal 1x2 field on the table
    city->Set_GameTableValue(5, 5, HIGHSCHOOL, LEFT);
    CHECK(city->Get_GameField(5, 5)->Get_Type() == HIGHSCHOOL);
    CHECK(city->Get_GameField(6, 5)->Get_Type() == HIGHSCHOOL);
    city->Set_GameTableValue(7, 7, HIGHSCHOOL, FRONT);
    CHECK(city->Get_GameField(7, 7)->Get_Type() == HIGHSCHOOL);
    CHECK(city->Get_GameField(7, 8)->Get_Type() == HIGHSCHOOL);

    //Side 1x2 field on the table
    city->Set_GameTableValue(9, 3, HIGHSCHOOL, LEFT);
    CHECK(city->Get_GameField(9, 3)->Get_Type() != HIGHSCHOOL);
    city->Set_GameTableValue(3, 9, HIGHSCHOOL, FRONT);
    CHECK(city->Get_GameField(3, 9)->Get_Type() != HIGHSCHOOL);

    delete city;
}

TEST_CASE("Citizen")
{
    ResidentalArea* residentialArea = new ResidentalArea(LEVEL_1, RESIDENTIAL_LVL1, LEFT, 0, 0);
    IndustrialArea* workingArea = new IndustrialArea(LEVEL_1, INDUSTRIAL_LVL1, LEFT, 1, 0);
    Citizen* citizen = new Citizen();

    citizen->Set_Age(40);
    citizen->Set_Pension(10);
    citizen->Set_MonthsBeforePension(10);
    citizen->Set_Education(BASIC);
    citizen->Set_Residence(residentialArea);
    citizen->Set_Workplace(workingArea);

    CHECK(citizen->Get_Age() == 40);
    CHECK(citizen->Get_Pension() == 10);
    CHECK(citizen->Get_MonthsBeforePension() == 10);
    CHECK(citizen->Get_Education() == BASIC);
    CHECK(citizen->Get_Residence() == residentialArea);
    CHECK(citizen->Get_Workplace() == workingArea);

    //Education
    citizen->Increase_EducationLevel();
    CHECK(citizen->HasIntermediateEducationLevel());
    citizen->Increase_EducationLevel();
    CHECK(citizen->HasAdvancedEducationLevel());
    citizen->Downgrade_EducationLevel();
    CHECK(!citizen->HasIntermediateEducationLevel());
    CHECK(!citizen->HasAdvancedEducationLevel());
}

TEST_CASE("CITIZEN EDUCATION LEVEL")
{
    Citizen* citizen = new Citizen();
    Education maxEducationLevel;

    maxEducationLevel = Education::INTERMEDIATE;
    citizen->Increase_EducationLevel(maxEducationLevel);
    CHECK(citizen->Get_Education() == Education::INTERMEDIATE);

    citizen->Set_Education(Education::BASIC);

    maxEducationLevel = Education::ADVANCED;
    citizen->Increase_EducationLevel(maxEducationLevel);
    CHECK(citizen->Get_Education() == Education::INTERMEDIATE);

    citizen->Set_Education(Education::INTERMEDIATE);

    maxEducationLevel = Education::ADVANCED;
    citizen->Increase_EducationLevel(maxEducationLevel);
    CHECK(citizen->Get_Education() == Education::ADVANCED);

    citizen->Set_Education(Education::INTERMEDIATE);

    maxEducationLevel = Education::INTERMEDIATE;
    citizen->Increase_EducationLevel(maxEducationLevel);
    CHECK(citizen->Get_Education() == Education::INTERMEDIATE);

    delete citizen;
}

TEST_CASE("APPLY_FUNCTION_TO_ALL_ZONES") {
    RoadNetwork::ResetNetworks();
    City* city = new City(25, 10000000, 1);

    for (int i = 0; i < 3; ++i) {
        int networkId = RoadNetwork::CreateNetwork();
        for (int j = 0; j < 10; ++j) {
            GameField* zone;
            if (j % 2 == 0) {
                zone = GameField::CreateField(ROAD, FRONT, i, j);
            }
            else {
                zone = GameField::CreateField(RESIDENTIAL_LVL1, FRONT, i, j);
            }
            RoadNetwork::AddToNetwork(zone, networkId);
        }
    }

    int counter = 0;
    RoadNetwork::ApplyToAllZones([&](GameField* const gameField) { ++counter; });

    CHECK(counter == 15);
}

TEST_CASE("APPLY_FUNCTION_TO_ALL_BUILDINGS") {
    RoadNetwork::ResetNetworks();
    City* city = new City(25, 10000000, 1);

    for (int i = 0; i < 3; ++i) {
        int networkId = RoadNetwork::CreateNetwork();
        for (int j = 0; j < 20; ++j) {
            GameField* zone;
            if (j % 2 == 0) {
                zone = GameField::CreateField(ROAD, FRONT, i, j);
            }
            else {
                zone = GameField::CreateField(POLICESTATION, FRONT, i, j);
            }
            RoadNetwork::AddToNetwork(zone, networkId);
        }
    }

    int counter = 0;
    RoadNetwork::ApplyToAllBuilding([&](GameField* const gameField) { ++counter; });

    CHECK(counter == 30);
}

TEST_CASE("Road Network General Tests") {
    RoadNetwork::ResetNetworks();
    City* city = new City(5, 10000000, 1);

    city->Set_GameTableValue(0, 0, ROAD, LEFT);
    city->Set_GameTableValue(1, 0, ROAD, LEFT);
    city->Set_GameTableValue(2, 0, ROAD, LEFT);

    CHECK((RoadNetwork::GetNetworkId(city->Get_GameField(0, 0)) == RoadNetwork::GetNetworkId(city->Get_GameField(1, 0))));
    CHECK((RoadNetwork::GetNetworkId(city->Get_GameField(1, 0)) == RoadNetwork::GetNetworkId(city->Get_GameField(2, 0))));

    city->Set_GameTableValue(0, 1, RESIDENTIAL_LVL1, LEFT);
    city->Set_GameTableValue(2, 1, INDUSTRIAL_LVL1, LEFT);
    Zone* residential = dynamic_cast<Zone*>(city->Get_GameField(0, 1));
    Zone* industrial = dynamic_cast<Zone*>(city->Get_GameField(2, 1));

    //Is Connected
    CHECK(RoadNetwork::IsConnected(residential, industrial));

    //Deleting road, network splits up into 2
    city->Set_GameTableValue(1, 0, EMPTY, LEFT);
    CHECK(!(RoadNetwork::IsConnected(residential, industrial)));
    CHECK((RoadNetwork::GetNetworkId(residential) != RoadNetwork::GetNetworkId(industrial)));
    CHECK(RoadNetwork::FindEmptyWorkingArea(residential, 1) == nullptr);

    //Merging 2 networks
    city->Set_GameTableValue(1, 0, ROAD, LEFT);
    CHECK(RoadNetwork::FindEmptyResidentialArea() == residential);
    CHECK(RoadNetwork::FindOptimalResidentialArea(1) == residential);
    CHECK(RoadNetwork::FindEmptyWorkingArea(residential, 1) == industrial);

    //Deleting industrial zone
    city->Set_GameTableValue(2, 1, EMPTY, LEFT);
    CHECK(RoadNetwork::FindEmptyWorkingArea(residential, 1) == nullptr);
}

TEST_CASE("Citizen Satisfaction") {
    RoadNetwork::ResetNetworks();
    City* city = new City(5, 10000000, 1);
    Citizen* citizen = new Citizen();

    city->Set_GameTableValue(0, 0, ROAD, LEFT);
    city->Set_GameTableValue(1, 0, ROAD, LEFT);
    city->Set_GameTableValue(2, 0, ROAD, LEFT);
    city->Set_GameTableValue(0, 1, RESIDENTIAL_LVL1, LEFT);
    Zone* residential = dynamic_cast<Zone*>(city->Get_GameField(0, 1));

    //Initial satisfaction
    city->JoinCity(citizen);
    float satisfaction1 = citizen->Calculate_Satisfaction();

    //Satisfaction increases after finding a workplace
    city->Set_GameTableValue(2, 1, SERVICE_LVL1, LEFT);
    Zone* service = dynamic_cast<Zone*>(city->Get_GameField(2, 1));
    city->HandleLosingZone();
    float satisfaction2 = citizen->Calculate_Satisfaction();
    CHECK(satisfaction1 < satisfaction2);
    CHECK(citizen->Get_Workplace() == service);
    CHECK(citizen->Get_Residence() == residential);

    //Connected utility building increases satisfaction
    city->Set_GameTableValue(1, 1, POLICESTATION, LEFT);
    float satisfaction3 = citizen->Calculate_Satisfaction();
    CHECK(satisfaction2 < satisfaction3);

    //Unconnected utility building does not increase satisfaction
    city->Set_GameTableValue(4, 4, POLICESTATION, LEFT);
    float satisfaction4 = citizen->Calculate_Satisfaction();
    CHECK(satisfaction3 == satisfaction4);

    //Nearby industrial area lowers satisfaction
    city->Set_GameTableValue(3, 0, INDUSTRIAL_LVL1, LEFT);
    float satisfaction5 = citizen->Calculate_Satisfaction();
    CHECK(satisfaction4 > satisfaction5);
    city->Set_GameTableValue(3, 0, EMPTY, LEFT);

    int cost1 = city->Get_GameTable()->Get_TotalAnnualCost();
    std::string str1 = RoadNetwork::NetworksToString();

    //2x2 buildings increase satisfaction
    city->Set_GameTableValue(3, 0, STADIUM, LEFT);
    float satisfaction6 = citizen->Calculate_Satisfaction();
    CHECK(satisfaction4 < satisfaction6);

    //Deleting 2x2 building from network
    city->Set_GameTableValue(3, 0, EMPTY, LEFT);
    float satisfaction7 = citizen->Calculate_Satisfaction();
    CHECK(satisfaction6 > satisfaction7);

    //Annual cost and networks are the same before building and after deleting
    int cost2 = city->Get_GameTable()->Get_TotalAnnualCost();
    std::string str2 = RoadNetwork::NetworksToString();
    CHECK(cost1 == cost2);
    CHECK(str1 == str2);

    city->Set_GameTableValue(3, 0, ROAD, LEFT);
    city->Set_GameTableValue(4, 0, ROAD, LEFT);
    city->Set_GameTableValue(3, 1, SERVICE_LVL1, LEFT);
    city->Set_GameTableValue(4, 1, INDUSTRIAL_LVL1, LEFT);

    //FindEmptyWorkingArea chooses properly based on ratio
    WorkingArea* w1 = dynamic_cast<WorkingArea*>(RoadNetwork::FindEmptyWorkingArea(residential, 2));
    WorkingArea* w2 = dynamic_cast<WorkingArea*>(RoadNetwork::FindEmptyWorkingArea(residential, 0.5));
    CHECK(w1->IsIndustrialArea());
    CHECK(w2->IsServiceArea());

    
}

TEST_CASE("Basic simulation") {
    RoadNetwork::ResetNetworks();
    City* city = new City(5, 10000000, 1);

    city->Set_GameTableValue(0, 0, ROAD, LEFT);
    city->Set_GameTableValue(1, 0, ROAD, LEFT);
    city->Set_GameTableValue(2, 0, ROAD, LEFT);
    city->Set_GameTableValue(3, 0, FOREST, LEFT);

    city->Set_GameTableValue(0, 1, RESIDENTIAL_LVL1, LEFT);
    city->Set_GameTableValue(2, 1, SERVICE_LVL1, LEFT);

    Zone* residential = dynamic_cast<Zone*>(city->Get_GameField(0, 1));
    Zone* service = dynamic_cast<Zone*>(city->Get_GameField(2, 1));
    Forest* forest = dynamic_cast<Forest*>(city->Get_GameField(3, 0));
    int age1 = forest->Get_Age();

    for (int i = 0; i < 500; i++) {
        city->Simulate();
    }

    //Citizens auto join zones
    CHECK(service->Get_Contain() == 4);
    CHECK(residential->Get_Contain() == 4);

    //Forest age increases
    int age2 = forest->Get_Age();
    CHECK(age1 < age2);

    //Citizens leave after their home is destroyed
    city->Set_GameTableValue(0, 1, EMPTY, LEFT);
    for (int i = 0; i < 100; i++) {
        city->Simulate();
    }
    CHECK(city->Get_CitizenSize() == 0);
}