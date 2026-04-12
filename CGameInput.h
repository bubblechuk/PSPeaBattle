#pragma once
#include <SDL.h>
#include "InputState.h"

class CGameInput
{
public:
    InputState pollInput();
};