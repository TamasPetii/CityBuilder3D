#ifndef SCHOOL_H
#define SCHOOL_H

#include "Building.h"

class School : public Building
{
protected:
    School(FieldType type, int x, int y, float cost) : Building(type, x, y, cost) {};

public:
    ~School() {}

    bool inline IsSchool() const override { return true; }
    virtual inline bool IsHighSchool() const { return false; }
    virtual inline bool IsUniversity() const { return false; }
    float inline GetBuildingSatisfaction() const override { return 1; }

};

class HighSchool : public School
{
public:
    HighSchool(FieldType type, int x, int y, float cost) : School(type, x, y, cost) {};
    ~HighSchool() {}

    bool inline IsHighSchool() const override { return true; };
};

class University : public School
{
public:
    University(FieldType type, int x, int y, float cost) : School(type, x, y, cost) {};
    ~University() {}

    bool inline IsUniversity() const override { return true; };
};

#endif
