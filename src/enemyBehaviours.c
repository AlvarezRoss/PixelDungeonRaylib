#include "enemyBehaviours.h"

void Patrol(Character* enemy)
{
    return;   
}

void ChasePlayer(Character* enemy, Character* target)
{
    if (enemy == NULL || target == NULL);
    if (enemy->Postion.x > target->Postion.x + 10)
    {
        if (enemy->animation != enemy->walkingAnimation) enemy->animation = enemy->walkingAnimation;
        enemy->speed.x = -0.8;
        if (!enemy->rotated) enemy->rotated = true;
    }
    else if(enemy->Postion.x < target->Postion.x - 10 )
    {
        if (enemy->animation != enemy->walkingAnimation) enemy->animation = enemy->walkingAnimation;
        enemy->speed.x = 0.8;
        if (enemy->rotated) enemy->rotated = false;
    }
    else
    {
        enemy->speed.x = 0;
    }

    if (enemy->Postion.y > target->Postion.y + 10)
    {
        if (enemy->animation != enemy->walkingAnimation) enemy->animation = enemy->walkingAnimation;
        enemy->speed.y = -0.8;
    }

    else if(enemy->Postion.y < target->Postion.y - 10)
    {
        if (enemy->animation != enemy->walkingAnimation) enemy->animation = enemy->walkingAnimation;
        enemy->speed.y = 0.8;
    }

    else
    {
        enemy->speed.y = 0;
    }
}