#ifndef HELPER
#define HELPER
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define SPRITELEN 16
#define SPRITEHEIGHT 16
#define ENEMIES_IN_LEVEL_ONE 2


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

typedef struct Area{
    Vector2 center;
    float radius;
    Color color;
}Area;

typedef enum ENTITY_TYPE
{
    ENTITY_PLAYER,
    ENTITY_ORC,
    
}ENTITY_TYPE;

typedef enum ENTITY_STATE
{
    STATE_IDLE,
    STATE_WALKING,
    STATE_ATTACKING,
    STATE_HURT,
    STATE_DEAD,
    STATE_FOLLOWING, // Only used for companions and enemies
    STATE_PATROL
} ENTITY_STATE;

typedef struct Character{
    Vector2 Postion;
    Animation* animation;
    Animation* idleAnimation;
    Animation* walkingAnimation;
    Animation* attackAnimation;
    Animation* hurtAnimation;
    Animation* deathAnimation;
    ENTITY_TYPE entityType;
    ENTITY_STATE entityState;
    Area detectionArea; // Used only for enemies
    Vector2 speed;
    Rectangle collisionRect;
    int maxHealth;
    int health;
    bool rotated;
    bool inAttackRange; // Used to determine whcih enemies are within range
}Character;


int InitAnimation(Animation* animation, const char* path, int frameNumber);
void DeinitAnimation(Animation* animation); // DELETE MAYBE?
int InitCharacter(Character* character, Animation* idleAnimation, Animation* walkAnimation, Animation* attackAnimation, Animation* hurtAnimation, Animation* deathAnimation);
void UpdateCharacterAnimation(Character* character);
void HandleCharacterRotation(Character* character);
int InitCamera(Camera2D* camera, Character* player, Rectangle window); // Pass by value of the window rectangle is deliverate 
void UpdateCharacterCamera(Camera2D* camera, Character* player);
#endif