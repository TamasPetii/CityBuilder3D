#ifndef SCHOOL_H
#define SCHOOL_H

#include "Building.h"

class School : public Building
{
protected:
    School(float cost) : Building(cost) {};

public:
    ~School() {}

    bool inline IsSchool() const override { return true; }
    virtual inline bool IsHighSchool() const { return false; }
    virtual inline bool IsUniversity() const { return false; }

};

class HighSchool : public School
{
public:
    HighSchool(float cost) : School(cost) {};
    ~HighSchool() {}

    bool inline IsHighSchool() const override { return true; };
};

class University : public School
{
public:
    University(float cost) : School(cost) {};
    ~University() {}

    bool inline IsUniversity() const override { return true; };
};

#endif
