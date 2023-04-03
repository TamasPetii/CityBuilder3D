#ifndef RESIDENTALAREA_H
#define RESIDENTALAREA_H

#include "Zone.h"

class ResidentalArea : public Zone
{
public:
	ResidentalArea(Level level) : Zone(level) {}
	~ResidentalArea() {}

	bool inline IsResidentalArea() const override { return true; }
};

#endif

