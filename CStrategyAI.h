#pragma once
#include <memory>
#include <functional>
#include "CField.h"
#include <stdexcept>

class IStrategy
{
public:
    virtual ~IStrategy() = default;
    virtual bool Attack(CField *field, std::function<bool(int, int)> attackFunc) = 0;
};

class CStrategyAI
{
private:
    static std::unique_ptr<IStrategy> _strategy;

public:
    static int x, y;
    static int baseX;
    static int baseY;
    static char pos;

    static void setAttack(std::unique_ptr<IStrategy> strategy);
    static void Attack(CField *field, std::function<bool(int, int)> attackFunc);
};

class CRandomStrategy : public IStrategy
{
public:
    bool Attack(CField *field, std::function<bool(int, int)> attackFunc) override;
};

class CCrossStrategy : public IStrategy
{
public:
    bool Attack(CField *field, std::function<bool(int, int)> attackFunc) override;
};

class CFinalStrategy : public IStrategy
{
public:
    bool Attack(CField *field, std::function<bool(int, int)> attackFunc) override;
};