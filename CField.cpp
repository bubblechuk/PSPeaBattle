#include <vector>
#include <array>
#include <SDL.h>
#include "CField.h"
#include "CTextureManager.h"
#include "ETextures.h"
#include "CShip.h"
#include "_coordinates.h"
bool CField::isAllShipsPlaced()
{
    if (ships.size() == 10)
        return true;
    else
        return false;
}
bool operator==(_coordinates coords1, _coordinates coords2)
{
    if (coords1.x == coords2.x && coords1.y == coords2.y)
        return true;
    else
        return false;
}
bool CField::getShipStateByCell(int x, int y)
{
    CShip *shipptr = nullptr;
    for (auto &ship : ships)
    {
        for (auto &cell : ship._shipCoordinates)
        {
            if (cell->x == x && cell->y == y)
            {
                shipptr = &ship;
            }
        }
    }
    if (shipptr == NULL)
        return false;
    for (auto cell : shipptr->_shipCoordinates)
    {
        if (!cell->_isEmpty && !cell->_isShooted)
        {
            return false;
        }
    }
    return true;
}
void CField::isShipDestroyed()
{
    for (auto &ship : ships)
    {
        bool isDestroyed = false;
        for (auto &cell : ship._shipCoordinates)
        {
            if (cell->_isShooted)
            {
                isDestroyed = true;
            }
            else
            {
                isDestroyed = false;
                break;
            }
        }
        ship._isDestroyed = isDestroyed;
        if (isDestroyed)
        {

            switch (ship._position)
            {
            case 'h':
            {
                for (int i = ship._shipCoordinates.at(0)->x - 1; i < ship._shipCoordinates.at(0)->x + ship._size + 1; i++)
                {
                    for (int j = ship._shipCoordinates.at(0)->y - 1; j < ship._shipCoordinates.at(0)->y + 2; j++)
                    {
                        if (i < 0 || i > 9 ||
                            j < 0 || j > 9)
                        {
                            continue;
                        }
                        this->grid[i][j]._isShooted = 1;
                    }
                }
                break;
            }
            case 'v':
            {
                for (int i = ship._shipCoordinates.at(0)->y - 1; i < ship._shipCoordinates.at(0)->y + ship._size + 1; i++)
                {
                    for (int j = ship._shipCoordinates.at(0)->x - 1; j < ship._shipCoordinates.at(0)->x + 2; j++)
                    {
                        if (i < 0 || i > 9 ||
                            j < 0 || j > 9)
                        {
                            continue;
                        }
                        this->grid[j][i]._isShooted = 1;
                    }
                }
            }
            break;
            }
        }
    }
}
bool CField::isValidCell(int x, int y) const
{
    return x >= 0 && x < 10 && y >= 0 && y < 10;
}

CField::CField()
{
    const int cellSize = 20;
    const int offsetX = 140;
    const int offsetY = 36;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            SDL_Rect destRect = {
                offsetX + i * cellSize,
                offsetY + j * cellSize,
                cellSize,
                cellSize};

            gridRect[i][j] = destRect;

            grid[i][j]._isFocused = false;
            grid[i][j].x = i;
            grid[i][j].y = j;
        }
    }
}
