#pragma once
// CCell represents cell of game field.
class CCell
{
public:
	int x;
	int y;
	/*Defines if cell is empty.
	0 - NOT empty, 1 - empty*/
	bool _isEmpty;

	/*Defines if player shooted specified cell
	0 - NOT shooted, 1 - shooted*/
	bool _isShooted;

	/*Defines if mouse cursor focused on specified cell
	0 - is NOT focused, 1 - focused*/
	bool _isFocused;

	/*Constructor initialize Cell with
	ALL of its properties equals to 0*/
	CCell();
};
