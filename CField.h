#pragma once
#include <vector>
#include <array>
#include <SDL.h>
#include "CCell.h"
#include "CShip.h"
#include "_coordinates.h"
class CShip;
class CField
{
public:
	std::vector<CShip> ships;
	// Represents 10x10 2D-Array of CCell's
	std::array<std::array<CCell, 10>, 10> grid;
	// Represents 10x10 2D-Array of SDL_Rect for every related CCell
	std::array<std::array<SDL_Rect, 10>, 10> gridRect;
	/*std::array<SDL_Rect, 19> gridNumbers;*/
	// Constructor of CField, initialize "grid" and "gridRect" for further
	void isShipDestroyed();
	bool isAllShipsPlaced();
	bool getShipStateByCell(int x, int y);
	bool isValidCell(int x, int y) const;
	CField();
};
