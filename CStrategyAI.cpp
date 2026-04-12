#include "CStrategyAI.h"
#include "_coordinates.h"

std::unique_ptr<IStrategy> CStrategyAI::_strategy = std::make_unique<CRandomStrategy>();

int CStrategyAI::x = 0;
int CStrategyAI::y = 0;
char CStrategyAI::pos = 'v';

void CStrategyAI::Attack(CField* field, std::function<bool(int,int)> attackFunc) {
    if (_strategy)
        while (_strategy->Attack(field, attackFunc));
}

void CStrategyAI::setAttack(std::unique_ptr<IStrategy> strategy) {
    _strategy = std::move(strategy);
}
bool CRandomStrategy::Attack(CField* field, std::function<bool(int,int)> attackFunc) {
    printf("CRandomStrategy::Attack()\n");

    int attempts = 0;
    do {
        CStrategyAI::x = rand() % 10;
        CStrategyAI::y = rand() % 10;
        attempts++;
        if (attempts > 1000) return false;
    } while (field->grid[CStrategyAI::x][CStrategyAI::y]._isShooted);

    if (attackFunc(CStrategyAI::x, CStrategyAI::y)) {
        return false;
    } else {
        if (field->getShipStateByCell(CStrategyAI::x, CStrategyAI::y)) {
            return false; 
        }
        CStrategyAI::setAttack(std::make_unique<CCrossStrategy>());
        return true;
    }
}
bool CCrossStrategy::Attack(CField* field, std::function<bool(int,int)> attackFunc) {
    printf("CCrossStrategy::Attack()\n");

    int directions[4][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    std::vector<int> available;

    for (int i = 0; i < 4; ++i) {
        int nx = CStrategyAI::x + directions[i][0];
        int ny = CStrategyAI::y + directions[i][1];

        if (field->isValidCell(nx, ny) && !field->grid[nx][ny]._isShooted) {
            available.push_back(i);
        }
    }

    if (available.empty()) {
        CStrategyAI::setAttack(std::make_unique<CFinalStrategy>());
        return true;
    }

    int r = available[rand() % available.size()];
    int nx = CStrategyAI::x + directions[r][0];
    int ny = CStrategyAI::y + directions[r][1];

    if (attackFunc(nx, ny)) {
        return false;
    } else {
        if (field->getShipStateByCell(CStrategyAI::x, CStrategyAI::y)) {
            CStrategyAI::setAttack(std::make_unique<CRandomStrategy>());
            return true;
        }
        CStrategyAI::pos = (r < 2) ? 'h' : 'v';
    }

    CStrategyAI::setAttack(std::make_unique<CFinalStrategy>());
    return true;
}
bool CFinalStrategy::Attack(CField* field, std::function<bool(int,int)> attackFunc) {
    printf("CFinalStrategy::Attack()\n");

    int curX = CStrategyAI::x;
    int curY = CStrategyAI::y;

    if (CStrategyAI::pos == 'v') {
        for (int i = 1; i < 4; i++) {
            int ny = curY + i;
            if (!field->isValidCell(curX, ny)) break; 
            if (attackFunc(curX, ny)) break;         
        }
        for (int i = 1; i < 4; i++) {
            int ny = curY - i;
            if (!field->isValidCell(curX, ny)) break;
            if (attackFunc(curX, ny)) break;
        }
    } else if (CStrategyAI::pos == 'h') {
        for (int i = 1; i < 4; i++) {
            int nx = curX + i;
            if (!field->isValidCell(nx, curY)) break;
            if (attackFunc(nx, curY)) break;
        }
        for (int i = 1; i < 4; i++) {
            int nx = curX - i;
            if (!field->isValidCell(nx, curY)) break;
            if (attackFunc(nx, curY)) break;
        }
    }

if (field->getShipStateByCell(CStrategyAI::x, CStrategyAI::y)) {
    CStrategyAI::setAttack(std::make_unique<CRandomStrategy>());
    return false;

    return false;
}