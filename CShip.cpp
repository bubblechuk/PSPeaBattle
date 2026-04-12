#include "CShip.h"
#include <iostream>
CShip::CShip(unsigned int size, char position, _coordinates coords, CField *field)
{
	/*printf("\n Creating ship: \n");*/
	_size = size;
	_isDestroyed = false;
	if (size > 4 || size < 1 || (position != 'h' && position != 'v') ||
		coords.x > 9 || coords.x < 0 || coords.y > 9 || coords.y < 0)
	{
		_isCreated = false;
		/*printf("CShip initialization error! Invalid arguments!\n");*/
		return;
	}
	if (position == 'v')
	{
		for (int y = -1; y < int(size + 1); y++)
		{
			for (int x = -1; x < 2; x++)
			{
				if (y + coords.y < 0 || y + coords.y > 9 ||
					x + coords.x < 0 || x + coords.x > 9)
				{
					continue;
				}
				int resX = x + coords.x,
					resY = y + coords.y;
				if (!field->grid[resX][resY]._isEmpty)
				{
					_isCreated = false;
					/*printf("Near ship error!\n");*/
					return;
				}
			}
		}

		for (unsigned int k = 0; k < size; k++)
		{
			if (k + coords.y < 0 || k + coords.y > 9)
			{
				_isCreated = false;
				/*printf("Out of range error!\n");*/
				return;
			}
		}
		// printf("VERTICAL.\n");
		for (unsigned int j = 0; j < size; j++)
		{

			field->grid[coords.x][coords.y + j]._isEmpty = false;

			/*std::cout << "X:" << coords.x << " Y:" << coords.y + j << std::endl;*/
			_shipCoordinates.push_back(&field->grid[coords.x][coords.y + j]);
		}
	}
	else if (position == 'h')
	{
		for (int x = -1; x < int(size + 1); x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (y + coords.y < 0 || y + coords.y > 9 ||
					x + coords.x < 0 || x + coords.x > 9)
				{
					continue;
				}
				int resX = x + coords.x,
					resY = y + coords.y;
				if (!field->grid[resX][resY]._isEmpty)
				{
					_isCreated = false;
					/*printf("Near ship error!\n");*/
					return;
				}
			}
		}

		for (unsigned int k = 0; k < size; k++)
		{
			if (k + coords.x < 0 || k + coords.x > 9)
			{
				_isCreated = false;
				/*printf("Out of range error!\n");*/
				return;
			}
		}
		// printf("HORIZONTAL\n");
		for (unsigned int i = 0; i < size; i++)
		{
			field->grid[coords.x + i][coords.y]._isEmpty = false;
			/*std::cout << "X:" << coords.x + i << " Y:" << coords.y << std::endl;*/
			_shipCoordinates.push_back(&field->grid[coords.x + i][coords.y]);
		}
	}
	_isCreated = true;
	_position = position;
}