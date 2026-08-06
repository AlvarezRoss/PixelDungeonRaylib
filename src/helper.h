#ifndef HELPER
#define HELPER
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define SPRITELEN 16
#define SPRITEHEIGHT 16
#define ENEMIES_IN_LEVEL_ONE 2
#define WINDOWED_MODE_SIZE 800.0f
#define CHARACTER_TEXTURE_SIZE 100


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

typedef enum ENTITY_TYPE
{
    ENTITY_PLAYER,
    ENTITY_ORC,
    ENTITY_SKELLETON,
    

    ENTITY_TOTAL,
    ENTITY_NONE,  // Used to skip iteration on custom map init
    
}ENTITY_TYPE;

// I will probably have to unify all grpahics into a single struct
typedef struct CharacterGraphics
{
    Animation* idleAnimation;
    Animation* walkingAnimation;
    Animation* attackAnimation;
    Animation* hurtAnimation;
    Animation* deathAnimation;
} Graphics;

typedef struct Area{
    Vector2 center;
    float radius;
    Color color;
}Area;
typedef enum GAME_STATE
{
    GAME_STATE_RUNNING,
    GAME_STATE_PAUSED,
    GAME_STATE_IN_EDITOR,
    GAME_STATE_UNINITIALIZED_CUSTON_MAP,
    GAME_STATE_RUNNING_CUSTOM_MAP
} GAME_STATE;

typedef struct GameState
{
    GAME_STATE State;
    int level;
    int targetFps;
} GameState;



typedef enum ENTITY_STATE
{
    STATE_IDLE,
    STATE_WALKING,
    STATE_ATTACKING,
    STATE_HURT,
    STATE_DEAD,
    STATE_FOLLOWING, // Only used for companions and enemies
    STATE_PATROL,
    STATE_INACTIVE
} ENTITY_STATE;



typedef struct Timer
{
    float lifetime;
}Timer;

typedef struct Character{
    Vector2 Postion;
    Animation* animation;
    Graphics* graphics;
    Timer* attackTimer;
    ENTITY_TYPE entityType;
    ENTITY_STATE entityState;
    Area detectionArea; // Used only for enemies
    Vector2 speed;
    Rectangle collisionRect;
    int maxHealth;
    int health;
    int editorTileX; // Used to keep track of the tile index in which they are added in the editor
    int editorTileY;
    bool rotated;
    bool inAttackRange; // Used to determine whcih enemies are within range
}Character;


int InitAnimation(Animation* animation, const char* path, int frameNumber);
void DeinitAnimation(Animation* animation); // DELETE MAYBE?
int InitGraphics(Graphics* graphics,ENTITY_TYPE entity);
void DeinitGraphics(Graphics* graphics);
int InitCharacter(Character* character, Graphics* graphics);
void UpdateCharacterAnimation(Character* character);
Rectangle HandleCharacterRotation(Character* character);
int InitCamera(Camera2D* camera, Character* player, Rectangle window); // Pass by value of the window rectangle is deliverate 
void UpdateCharacterCamera(Camera2D* camera, Character* player);
void StartTimer(Timer* timer, float lifetime);
void UpdateTimer(Timer* timer);
int TimerFinished(Timer* timer);
void FullScreen(float* windowWidth, float* windowHeight, Camera2D* camera);
int InitGameState(GameState* gameState);
int GameStateInputHandle(GameState* gameState);
int InitPlayer(Character* player, Graphics* graphics,float x, float y);
void DeinitPlayer(Character* player);
int InitEnemy(Character* enemy, ENTITY_TYPE entity, Graphics* graphics,float x, float y);
#endif