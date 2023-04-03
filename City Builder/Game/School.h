#ifndef SCHOOL_H
#define SCHOOL_H

#include "Building.h"

class School : public Building
{
protected:
    School() : Building() {};

public:
    ~School() {}

    bool inline IsSchool() const override { return true; }
    virtual inline bool IsHighSchool() const { return false; }
    virtual inline bool IsUniversity() const { return false; }

};

class HighSchool : public School
{
public:
    HighSchool() : School() {};
    ~HighSchool() {}

    bool inline IsHighSchool() const override { return true; };
};

class University : public School
{
public:
    University() : School() {};
    ~University() {}

    bool inline IsUniversity() const override { return true; };
};

#endif
