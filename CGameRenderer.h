#pragma once
#include "CField.h"
#include <SDL.h>
#include <vector>
#include "CGameLogic.h"

class CGameRenderer
{
public:
    bool isDebug = false;
    void render(SDL_Renderer *renderer,
                RenderData data,
                int curX,
                int curY);
    void renderMenu(SDL_Renderer *renderer);
    void updateCursorBlink();
};