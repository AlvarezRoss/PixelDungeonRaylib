#include "helper.h"


int InitAnimation(Animation* animation, const char* path, int frameNumber)
{
    if (animation == NULL) return 1;
    
    Image image = LoadImage(path);
    if (image.data == NULL) return 1;
    
    animation->texture = LoadTextureFromImage(image);
    if (animation->texture.id == 0) return 1;
    
    animation->frameCounter = 0;
    // (Rectangle) is a compound literal aka a temporary struct i can create to them assign it to the frameRect
    animation->frameRect = (Rectangle){0.0f,0.0f,(float)animation->texture.width/frameNumber,(float)animation->texture.height};
    animation->frameSpeed = 10;
    animation->frameNum = frameNumber;
    animation->frameWidth = (float)animation->texture.width/animation->frameNum;
    animation->rotated = false;
    UnloadImage(image);
    return 0;
}


int InitCharacter(Character* character, Animation* idleAnimation, Animation* walkAnimation, Animation* attackAnimation)
{
    if(character == NULL || idleAnimation == NULL || walkAnimation == NULL || attackAnimation == NULL) return 1;

    character->idleAnimation = idleAnimation;
    character->walkingAnimation = walkAnimation;
    character->attackAnimation = attackAnimation;
    character->animation = character->idleAnimation;
    character->attacking = false;
    character->walking = false;
    character->damaged = false;
    character->health = 40;
    character->speed = 30;
    character->Postion = (Vector2){800/2,450/2};
    character->rotated = false;
    
    return 0;
}

void UpdateCharacterAnimation(Character* character)
{
    character->animation->frameCounter++;
    // the if statement body is to control how many game frames to wait before switching animation 60/8 = 7.5 -> those are the game frames to wait
    if (character->animation->frameCounter >= (60/character->animation->frameSpeed))
    {
        character->animation->frameCounter = 0; // Reset the frame counter to restart the wait time
        character->animation->currentFrame ++;

        if (character->animation->currentFrame >= character->animation->frameNum)
        {
            if (character->animation == character->attackAnimation) character->attacking = false;
            character->animation->currentFrame = 0; // animation restart
        } 

        character->animation->frameRect.x = (float)character->animation->currentFrame * character->animation->frameWidth;
    }
        
}

void HandleCharacterRotation(Character* character)
{
    // To "Turn a sprite around" we shift the width from positive to negative
    if (character->rotated && !character->animation->rotated)
    {
        character->animation->frameRect.width = -character->animation->frameRect.width;

        character->animation->rotated = true;
    }
    else if (!character->rotated && character->animation->rotated)
    {
        character->animation->frameRect.width = - character->animation ->frameRect.width;
        character->animation->rotated = false;
    }
}