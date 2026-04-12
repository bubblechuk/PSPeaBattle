#pragma once
#include "CField.h"
#include "CShip.h"
#include "CStrategyAI.h"
#include "CGameInput.h"
#include "RenderData.h"
class CGameLogic
{
public:
    CGameLogic();
    void setAIMode(bool isBot);
    void update(const InputState &input, float dt);
    void addShip(int i, int j, char pos);
    bool attackCell(int i, int j);
    bool isEndgame(const CField &field) const;
    void switchField();
    void resetGame();
    RenderData getLogicData();

private:
    CField _fieldPlayer1;
    CField _fieldPlayer2;
    CField *_currentField;
    GameState _state = MENU;
    bool _turn;
    bool _isBot;
    int _scoreP1 = 0;
    int _scoreP2 = 0;
    bool _position = false;
    void randomShip();
};