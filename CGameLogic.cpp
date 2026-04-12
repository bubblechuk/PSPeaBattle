#include "CGameLogic.h"
#include <cstdlib>
Uint32 _waitUntil = 0;
CGameLogic::CGameLogic()
{
    _currentField = &_fieldPlayer1;
    _turn = true;
    _isBot = false;
}
void CGameLogic::setAIMode(bool isBot)
{
    _isBot = isBot;
}
RenderData CGameLogic::getLogicData()
{
    RenderData data;
    data.field = _currentField;
    data.turn = _turn;
    data.state = _state;
    data.isBot = _isBot;
    data.scoreP1 = _scoreP1;
    data.scoreP2 = _scoreP2;
    return data;
}
void CGameLogic::update(const InputState &input, float dt)
{
    switch (_state)
    {
    case MENU:
        if (input.leftClick)
        {
            _isBot = false;
            _state = PLACING;
        }
        else if (input.rightClick)
        {
            _isBot = true;
            _state = PLACING;
        }
        // if ((input.rightClick || input.leftClick) && (input.keyR))
        // {
        //     _isDebug = true;
        // }
        break;
    case PLACING:
        if (input.rightClick)
        {
            _position = !_position;
        }

        if (input.leftClick)
        {
            if (!_currentField->isAllShipsPlaced())
            {
                addShip(input.cursorX, input.cursorY, _position ? 'h' : 'v');
            }
        }

        if (input.keyR)
        {
            randomShip();
        }

        if (_currentField->isAllShipsPlaced() && input.keyEnter || (_isBot && !_turn))
        {
            if (_currentField == &_fieldPlayer1)
            {
                _currentField = &_fieldPlayer2;
                if (_isBot)
                    randomShip();
                _turn = !_turn;
            }
            else
            {
                printf("BATTLE\n");
                _state = BATTLE;

                _currentField = &_fieldPlayer2;
                _turn = true;
                return;
            }
        }

        break;
    case WAIT:
        if (SDL_GetTicks() >= _waitUntil)
        {

            if (_isBot && !_turn)
            {
                CStrategyAI::Attack(_currentField, [this](int x, int y)
                                    {
                auto &cell = _currentField->grid[x][y];
                bool shooted = cell._isShooted;
                bool miss = this->attackCell(x, y);

                if(!miss) {
                    if(!shooted)
                    {
                        if(_turn) _scoreP1++;
                        else _scoreP2++;
                    }
                }

                return miss; });
                _turn = !_turn;
                switchField();

                _state = WAIT;
                _waitUntil = SDL_GetTicks() + 300;
            }
            else
            {
                _state = BATTLE;
            }
        }
        break;
    case BATTLE:

        if (input.leftClick)
        {
            auto &cell = _currentField->grid[input.cursorX][input.cursorY];
            bool shooted = cell._isShooted;
            bool miss = attackCell(input.cursorX, input.cursorY);

            if (!miss)
            {
                if (!shooted)
                {
                    if (_turn)
                        _scoreP1++;
                    else
                    {
                        _scoreP2++;
                    }
                }
            }
            else
            {
                _turn = !_turn;
                _state = WAIT;
                _waitUntil = SDL_GetTicks() + 800;
                switchField();
            }

            _currentField->isShipDestroyed();
        }
        if (isEndgame(_fieldPlayer1) || isEndgame(_fieldPlayer2))
        {
            _state = END;
        }

        break;
    case END:
        SDL_Delay(2000);
        resetGame();
        break;
    }
}
void CGameLogic::resetGame()
{
    _fieldPlayer1 = CField();
    _fieldPlayer2 = CField();

    _currentField = &_fieldPlayer1;
    _state = MENU;
    _turn = true;
    _scoreP1 = 0;
    _scoreP2 = 0;
}
void CGameLogic::addShip(int i, int j, char pos)
{
    int size = _currentField->ships.size();
    int shipSize = 1;
    if (size == 0)
        shipSize = 4;
    else if (size == 1 || size == 2)
        shipSize = 3;
    else if (size > 2 && size < 6)
        shipSize = 2;
    else if (size > 5 && size < 10)
        shipSize = 1;
    CShip ship(shipSize, pos, _coordinates(i, j), _currentField);
    if (ship._isCreated)
        _currentField->ships.push_back(ship);
}

bool CGameLogic::attackCell(int i, int j)
{
    auto *cell = &_currentField->grid[i][j];
    if (cell->_isShooted)
        return false;
    if (cell->_isEmpty)
    {
        cell->_isShooted = !cell->_isShooted;
        return true;
    }
    else
    {
        cell->_isShooted = !cell->_isShooted;
        return false;
    }
}
void CGameLogic::switchField()
{
    if (_currentField == &_fieldPlayer1)
        _currentField = &_fieldPlayer2;
    else
        _currentField = &_fieldPlayer1;
}
bool CGameLogic::isEndgame(const CField &field) const
{
    for (const auto &ship : field.ships)
        if (!ship._isDestroyed)
            return false;
    return true;
}
void CGameLogic::randomShip()
{
    while (!_currentField->isAllShipsPlaced())
    {
        int pos = rand() % 2;
        addShip(rand() % 10, rand() % 10, pos ? 'h' : 'v');
    }
}