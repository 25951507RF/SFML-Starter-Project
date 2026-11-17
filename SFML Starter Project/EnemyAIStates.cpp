#pragma once

#include "EnemyAIStates.h"
#include "Enemy.h"
#include <iostream>

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

PatrolState::PatrolState(Enemy& owner) : EnemyState(owner), nextWaypoint(1), direction(1)
{
    if (owner.getPatrol().size() < 2)
    {
        nextWaypoint = 0;
    }
}

EnemyState* PatrolState::update(float dt, const sf::Vector2f& playerPos)
{

    if (distanceSquared(playerPos, owner.getPosition()) < owner.getVisibilityRadius() * owner.getVisibilityRadius())
    {
        std::cout << "Chasing Player\n";
        return new ChaseState(owner);
    }

    sf::Vector2f waypointPos = owner.getPatrol()[nextWaypoint];
    if (distanceSquared(waypointPos, owner.getPosition()) < 0.01f)
    {

        if (nextWaypoint == 0)
            return new IdleState(owner);

        if (nextWaypoint == owner.getPatrol().size() - 1)
        {
            direction = -1;
        }
        nextWaypoint += direction;
        

    }

    owner.setPosition(moveTowards(owner.getPosition(), waypointPos, owner.getSpeed(), dt));

    return nullptr;
}

IdleState::IdleState(Enemy& owner) : EnemyState(owner), idleTimer(owner.getIdleTime())
{

    owner.setPosition(owner.getPatrol()[0]);

}

EnemyState* IdleState::update(float dt, const sf::Vector2f& playerPos)
{

    idleTimer -= dt;

    if (distanceSquared(playerPos, owner.getPosition()) < owner.getVisibilityRadius() * owner.getVisibilityRadius())
    {
        std::cout << "Chasing Player\n";
        return new ChaseState(owner);
    }

    if (idleTimer < 0)
    {
        std::cout << "New IdleState Returned\n";
        return new PatrolState(owner);
    }

    return nullptr;
}

ChaseState::ChaseState(Enemy& owner) : EnemyState(owner)
{



}

EnemyState* ChaseState::update(float dt, const sf::Vector2f& playerPos)
{

    if (distanceSquared(playerPos, owner.getPosition()) > owner.getVisibilityRadius() * owner.getVisibilityRadius())
    {
        std::cout << "Return\n";
        return new ReturnState(owner);
    }
    else
        owner.setPosition(moveTowards(owner.getPosition(), playerPos, owner.getSpeed(), dt));

    return nullptr;
}

ReturnState::ReturnState(Enemy& owner) : EnemyState(owner)
{
}

EnemyState* ReturnState::update(float dt, const sf::Vector2f& playerPos)
{
    sf::Vector2f waypoint0 = owner.getPatrol()[0];
    owner.setPosition(moveTowards(owner.getPosition(), waypoint0, owner.getSpeed(), dt));

    if (distanceSquared(playerPos, owner.getPosition()) < owner.getVisibilityRadius() * owner.getVisibilityRadius())
    {
        std::cout << "Chasing Player\n";
        return new ChaseState(owner);
    }
    else if (distanceSquared(owner.getPosition(), waypoint0) < 0.01f)
        {
            std::cout << "Idle\n";
            return new IdleState(owner);
        }

    return nullptr;
}