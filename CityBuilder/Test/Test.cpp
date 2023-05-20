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

    Building* building = new Building(FIRESTATION, LEFT, 0, 0);
    CHECK(building->IsBuilding());
    CHECK(!building->IsPoliceStation());
    CHECK(!building->IsFireStation());
    CHECK(!building->IsPowerWire());
    CHECK(!building->IsPowerStation());
    CHECK(!building->IsSchool());
    CHECK(!building->IsStadium());
    CHECK(building->GetBuildingSatisfaction() == 0);
    delete building;
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