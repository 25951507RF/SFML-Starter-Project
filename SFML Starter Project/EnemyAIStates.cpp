#include "EnemyAIStates.h"
#include "Enemy.h"

// helper functions
float distanceSquared(const sf::Vector2f& p0, const sf::Vector2f& p1)
{
    return (p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y);
}

sf::Vector2f moveTowards(const sf::Vector2f& cur, const sf::Vector2f& target, float speed, float time)
{
    float distSq = distanceSquared(cur, target);
    if (distSq < speed * speed * time * time)
        return target;
    sf::Vector2f direction = target - cur;
    direction /= sqrt(direction.x * direction.x + direction.y * direction.y);
    return cur + direction * speed * time;
}

PatrolState::PatrolState(Enemy& owner) : EnemyState(owner)
{
}

EnemyState* PatrolState::update(float dt, const sf::Vector2f& playerPos)
{
    return nullptr;
}

IdleState::IdleState(Enemy& owner) : EnemyState(owner)
{
}

EnemyState* IdleState::update(float dt, const sf::Vector2f& playerPos)
{
    return nullptr;
}

ChaseState::ChaseState(Enemy& owner) : EnemyState(owner)
{
}

EnemyState* ChaseState::update(float dt, const sf::Vector2f& playerPos)
{
    return nullptr;
}

ReturnState::ReturnState(Enemy& owner) : EnemyState(owner)
{
}

EnemyState* ReturnState::update(float dt, const sf::Vector2f& playerPos)
{
    return nullptr;
}