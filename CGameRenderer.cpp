#include "CGameRenderer.h"
#include "CTextureManager.h"
#include "ETextures.h"
#include <string>
#include <cmath> 

int cursorAlpha = 0;
int cursorDir = 1;
Uint32 lastCursorUpdate = 0;
SDL_Rect menu = {23, 20, 434, 75};
SDL_Rect options = {163, 130, 154, 80};
SDL_Color green = {0, 255, 0, 255};
SDL_Rect player_icon = {40, 20, 35, 35};
SDL_Rect bot_icon = {405, 20, 35, 35};
SDL_Rect rectP1 = {50, 80, 20, 30};
SDL_Rect rectP2 = {415, 80, 20, 30};
SDL_Rect rectP1Text = {30, 65, 60, 15};
SDL_Rect rectP2Text = {395, 65, 60, 15};
void CGameRenderer::render(SDL_Renderer *renderer, RenderData data, int curX, int curY)
{
    GameState state = data.state;
    CField *field = data.field;
    bool showShip = isDebug || state == PLACING;
    Textures P2ICON = data.isBot ? BOTIMG : PLAYERIMG;
    auto &texture = CTextureManager::texture;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            const auto &cell = field->grid[i][j];
            SDL_Texture *tex = nullptr;

            if (cell._isShooted && !cell._isEmpty)
                tex = texture[DESTROY];
            else if (cell._isShooted && cell._isEmpty)
                tex = texture[MISS];
            else if (!cell._isEmpty)
                tex = showShip ? texture[SHIP] : texture[EMPTY];
            else
                tex = texture[EMPTY];

            SDL_RenderCopy(renderer, tex, nullptr, &field->gridRect[i][j]);
            if (i == curX && j == curY && state != WAIT)
            {

                SDL_Texture *cursorTex = nullptr;

                if (cell._isShooted && cell._isEmpty)
                {
                    cursorTex = texture[CURSORMISS];
                }
                else if (cell._isShooted && !cell._isEmpty)
                {
                    cursorTex = texture[CURSORDESTROY];
                }
                else if (!cell._isEmpty)
                {
                    cursorTex = texture[isDebug ? CURSORSHIP : CURSOR];
                }
                else
                {
                    cursorTex = texture[CURSOR];
                }

                SDL_SetTextureAlphaMod(cursorTex, cursorAlpha);
                SDL_RenderCopy(renderer, cursorTex, nullptr, &field->gridRect[i][j]);
                SDL_SetTextureAlphaMod(cursorTex, 255);
            }
        }
    }

    SDL_Texture *scoreP1Tex = CTextureManager::renderText(
        renderer,
        CTextureManager::font,
        std::to_string(data.scoreP1),
        green);
    SDL_Texture *scoreP2Tex = CTextureManager::renderText(
        renderer,
        CTextureManager::font,
        std::to_string(data.scoreP2),
        green);
    SDL_Texture *textP1Tex = CTextureManager::renderText(
        renderer,
        CTextureManager::font,
        "Player 1",
        green);
    SDL_Texture *textP2Tex = CTextureManager::renderText(
        renderer,
        CTextureManager::font,
        "Player 2",
        green);

    SDL_RenderCopy(renderer, scoreP1Tex, nullptr, &rectP1);
    SDL_RenderCopy(renderer, scoreP2Tex, nullptr, &rectP2);
    SDL_RenderCopy(renderer, textP1Tex, nullptr, &rectP1Text);
    SDL_RenderCopy(renderer, textP2Tex, nullptr, &rectP2Text);
    SDL_DestroyTexture(scoreP1Tex);
    SDL_DestroyTexture(scoreP2Tex);
    SDL_DestroyTexture(textP1Tex);
    SDL_DestroyTexture(textP2Tex);
    SDL_SetTextureAlphaMod(texture[PLAYERIMG], data.turn ? cursorAlpha : 255);
    SDL_RenderCopy(renderer, texture[PLAYERIMG], nullptr, &player_icon);
    SDL_SetTextureAlphaMod(texture[PLAYERIMG], 255);

    SDL_SetTextureAlphaMod(texture[P2ICON], !data.turn ? cursorAlpha : 255);
    SDL_RenderCopy(renderer, texture[P2ICON], nullptr, &bot_icon);
    SDL_SetTextureAlphaMod(texture[P2ICON], 255);
    SDL_RenderPresent(renderer);
}

void CGameRenderer::renderMenu(SDL_Renderer *renderer)
{
    auto &tex = CTextureManager::texture;
    
    double angle = 5.0 * std::sin(SDL_GetTicks() / 500.0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopyEx(renderer, tex[MENULOGO], nullptr, &menu, angle, nullptr, SDL_FLIP_NONE);
    
    SDL_RenderCopy(renderer, tex[OPTIONS], nullptr, &options);
    SDL_RenderPresent(renderer);
}
void CGameRenderer::updateCursorBlink()
{
    Uint32 now = SDL_GetTicks();

    if (now > lastCursorUpdate + 10)
    {
        cursorAlpha += cursorDir * 2;

        if (cursorAlpha >= 255)
        {
            cursorAlpha = 255;
            cursorDir = -1;
        }
        else if (cursorAlpha <= 155)
        {
            cursorAlpha = 155;
            cursorDir = 1;
        }

        lastCursorUpdate = now;
    }
}