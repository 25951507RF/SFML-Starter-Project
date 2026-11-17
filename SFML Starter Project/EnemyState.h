#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Enemy;

class EnemyState
{
protected:
    Enemy& owner;
public:
    EnemyState(Enemy& owner) : owner(owner) {}
    virtual EnemyState* update(float dt, const Vector2f& playerPos) = 0;
};