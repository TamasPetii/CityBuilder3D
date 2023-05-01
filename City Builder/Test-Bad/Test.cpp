#include "../Game/City.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("ASD")
{
    City* city = new City(50);
    CHECK(city->Get_GameTableSize() == 50);
}