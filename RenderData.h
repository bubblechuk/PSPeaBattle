#include "CField.h"
#include "GameState.h"
struct RenderData
{
    CField *field;
    bool turn;
    GameState state;
    bool isBot;
    int scoreP1;
    int scoreP2;
};