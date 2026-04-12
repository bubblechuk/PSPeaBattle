#pragma once
#include "CGameLogic.h"
#include "CGameRenderer.h"
#include "CGameInput.h"
#include <SDL.h>

class CGame
{
public:
    void Init(bool _isBot = false, bool _isDebug = false);
    void Loop();
    void Destroy();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    CGameLogic logic;
    CGameRenderer rendererLogic;
    CGameInput inputHandler;
};