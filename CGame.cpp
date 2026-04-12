#include "CGame.h"
#include "CTextureManager.h"
#include <SDL.h>
#include <SDL_ttf.h>

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 272

void CGame::Init(bool _isBot, bool _isDebug)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
    TTF_Init();
    window = SDL_CreateWindow(
        "window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    CTextureManager::init(renderer);
    CTextureManager::font = TTF_OpenFont("font.ttf", 38);
    logic.setAIMode(_isBot);
    rendererLogic.isDebug = _isDebug;
}

void CGame::Loop()
{

    bool running = true;
    Uint32 lastTicks = SDL_GetTicks();

    while (running)
    {
        try
        {
            Uint32 currentTicks = SDL_GetTicks();
            float dt = (currentTicks - lastTicks) / 1000.f;
            lastTicks = currentTicks;

            InputState input = inputHandler.pollInput();
            if (input.home)
                break;
            if (input.select)
                logic.resetGame();
            logic.update(input, dt);
            if (logic.getLogicData().state == MENU)
            {
                rendererLogic.renderMenu(renderer);
            }
            else
            {
                rendererLogic.updateCursorBlink();
                rendererLogic.render(renderer, logic.getLogicData(), input.cursorX, input.cursorY);
            }
        }
        catch (const std::exception &e)
        {
            SDL_Log("CRASH: %s", e.what());
            logic.resetGame();
        }
    }
}

void CGame::Destroy()
{
    SDL_Log("Exiting...");
    if (CTextureManager::font != nullptr) {
        TTF_CloseFont(CTextureManager::font);
        CTextureManager::font = nullptr;
    }
    CTextureManager::destroy();
    TTF_Quit();
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}