#ifndef ENEMYBEHAVIOURS_H
#define ENEMYBEHAVIOURS_H

#include "helper.h"

void Patrol(Character* enemy);
void ChasePlayer(Character* enemy, Character* target);
void FacePlayer(Character* player, Character* enemy);

#endif