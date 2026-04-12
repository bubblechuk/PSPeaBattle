#pragma once
#include <vector>
#include "CField.h"
#include "_coordinates.h"
#include "stdio.h"
class CField;
// CShip is an interface for all related CShip instances
class CShip
{
public:
	int _size;
	bool _isDestroyed;
	bool _isCreated;
	char _position;
	std::vector<CCell *> _shipCoordinates;
	CShip(unsigned int size, char position, _coordinates coords, CField *field);

private:
};
