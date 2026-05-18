#ifndef HELPER
#define HELPER
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define SPRITELEN 16
#define SPRITEHEIGHT 16
#define ENEMIES_IN_LEVEL_ONE 5


typedef struct Animation{
    Texture2D texture;
    Rectangle frameRect;
    int frameCounter;
    int currentFrame;
    int frameSpeed;
    int frameNum;
    int frameWidth;
    bool rotated; // if character is rotated and animation isn't then we rotate the animation
}Animation;

typedef struct Character{
    Vector2 Postion;
    Animation* animation;
    Animation* idleAnimation;
    Animation* walkingAnimation;
    Animation* attackAnimation;
    Animation* hurtAnimation;
    int speed;
    int maxHealth;
    int health;
    bool attacking;
    bool damaged;
    bool walking;
    bool rotated;
    bool playerDetected; // Only use for enemy characters
    bool takingDamage;
    bool enemy;
    bool inAttackRange; // Used to determine whcih enemies are within range
}Character;

typedef struct level{
    int enemyNumber;
    Character* player;
    Character* enemies;
}level;


int InitAnimation(Animation* animation, const char* path, int frameNumber);
void DeinitAnimation(Animation* animation); // DELETE MAYBE?
int InitCharacter(Character* character, Animation* idleAnimation, Animation* walkAnimation, Animation* attackAnimation, Animation* hurtAnimation);
void UpdateCharacterAnimation(Character* character);
void HandleCharacterRotation(Character* character);
void TakeDamage(Character* character, int damage);
void initLevel(level* level, Character* player, Character* enemies);
#endif