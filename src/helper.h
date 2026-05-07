#ifndef HELPER
#define HELPER
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


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
    int speed;
    int health;
    bool attacking;
    bool damaged;
    bool walking;
    bool rotated;
    bool playerDetected; // Only use for enemy characters
}Character;



void InitGraphics(void);
void DeinitGraphics(void);
int InitAnimation(Animation* animation, const char* path, int frameNumber);
void DeinitAnimation(Animation* animation); // DELETE MAYBE?
int InitCharacter(Character* character, Animation* idleAnimation, Animation* walkAnimation, Animation* attackAnimation);
void UpdateCharacterAnimation(Character* character);
void HandleCharacterRotation(Character* character);
#endif