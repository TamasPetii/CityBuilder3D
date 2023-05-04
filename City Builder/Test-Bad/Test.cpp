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
    City* city2 = new City(5, 100000, 1);
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
    City* city = new City(5,100000,1);

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
    City* city = new City(5, 100000, 1);

    city->Set_GameTableValue(1, 1, RESIDENTIAL_LVL1, FRONT);
    city->Set_GameTableValue(1, 2, ROAD, FRONT);
    city->Set_GameTableValue(2, 2, INDUSTRIAL_LVL1, FRONT);

    Citizen* citizen = new Citizen();
    city->JoinCity(citizen);

    //If citizen isn't a pensioner
    float balanceBeforeTax = city->Get_Money();
    city->CollectMonthlyTax();
    float balanceWithTax = city->Get_Money();

    CHECK(balanceBeforeTax < balanceWithTax);

    //If citizen is a pensioner
    citizen->Set_Age(65);
    city->CollectMonthlyTax();

    float balanceWithPension = city->Get_Money();

    CHECK(balanceWithPension < balanceWithTax);

    //delete citizen;
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