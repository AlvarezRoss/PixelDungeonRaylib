# PixelDungeonRaylib

A **2D top-down game engine prototype** built with **C** and **Raylib**, featuring exploration, combat, and tile-based level design. Demonstrates modular systems for character animation, collision handling, and enemy AI that can be applied to other top-down games.

## Overview

PixelDungeonRaylib is both a playable pixel-art dungeon exploration game and a prototype engine for 2D top-down games. It showcases reusable, modular architecture for character management, tile-based level design, and AI systems. You navigate through procedurally-designed levels, encounter enemies, and engage in real-time combat using the underlying framework.

## Features

- **Top-Down Exploration**: Navigate dungeon rooms with 4x camera zoom for immersive pixel-art visuals
- **Real-Time Combat**: Attack enemies in range; enemies use AI to chase and counter-attack
- **Tile-Based Level Design**: Dungeon rooms constructed from tileset-based terrain with walls, corridors, and doors
- **Dynamic Enemy AI**: Enemies detect, chase, and attack the player within configurable detection radius
- **Character Animation System**: Frame-based sprite animation framework for player and enemy movement, idle, attack, and damage states
- **Collision Detection**: Tile and character collision with directional resolution
- **Health & Damage System**: Track health, apply damage, and handle character defeat
- **Reusable Camera System**: Smooth camera following with zoom support
- **Cross-Platform Build**: Supports Windows and Linux with unified Makefile

## Project Structure

```
PixelDungeonRaylib/
├── src/
│   ├── main.c              # Main game loop and initialization
│   ├── helper.c/h          # Character, animation, and camera systems
│   ├── map.c/h             # Tileset, level data, and collision handling
│   └── enemyBehaviours.c/h # Enemy AI (chase, patrol, attack)
├── Assets/                 # Sprite sheets and textures
├── Makefile                # Build configuration
├── build.bash              # Build script for Unix systems
└── README.md               # This file
```

## Building and Running

### Prerequisites

- **GCC** (or compatible C compiler)
- **Raylib** (graphics library)
- **Make** (for using Makefile)

### On Linux/macOS

Using Make:
```bash
make
./game
```

Or using the build script:
```bash
bash build.bash
```

### On Windows

Using Make:
```bash
make
game.exe
```

The Makefile automatically detects your OS and links the appropriate libraries.

### Clean Build

```bash
make clean
```

## Gameplay

### Controls

- **W / A / S / D** — Move up/left/down/right
- **Left Click** — Attack enemies in range
- **F1** — Toggle fullscreen mode

### Game Mechanics

- **Movement**: 8-directional movement with smooth animation
- **Combat**: Attack enemies that enter your attack range; manage health and defeat enemies
- **Collision**: Navigate around walls and obstacles; collision resolution prevents clipping
- **Detection**: Enemies detect the player within a radius and automatically chase and attack
- **Camera**: Follows the player with a 4x zoom level, keeping the action centered on screen

## Engine Architecture

The prototype demonstrates modular systems designed to be reusable across different 2D top-down games:

### Character System (`helper.h/c`)
- `Character` struct manages position, animation state, health, and entity type
- Animation framework uses frame-based sprite sheets (16x16 pixel sprites)
- Character state machine: IDLE, WALKING, ATTACKING, HURT, DEAD, FOLLOWING, PATROL
- Extensible for different character types and behaviors

### Level & Collision System (`map.c/h`)
- Tile-based level construction from element matrices (walls, corridors, doors, floors, etc.)
- Directional collision resolution for smooth, predictable character movement
- Separates ground layer and object layer rendering
- Easily adaptable tileset system for different environments

### Enemy Behavior System (`enemyBehaviours.h/c`)
- Modular AI functions: `ChasePlayer()`, `FacePlayer()`, `Patrol()`
- Detection radius-based enemy awareness
- Movement and rotation abstraction for easy extension with new behaviors

### Camera System (`helper.h/c`)
- Player-tracking camera with configurable offset
- Zoom support for different visual scales
- Fullscreen toggle capability

### Build System
- **Makefile**: Cross-platform (Windows, Linux) with automatic library detection
- **C Standard**: C99 with strict compile flags (`-Wall -Wextra -std=c99`)
- Clean separation of concerns for maintainability

## Future Roadmap

- [ ] Additional enemy types and AI behaviors
- [ ] Multiple dungeon levels with progression
- [ ] Item and loot system
- [ ] Player abilities and special attacks
- [ ] Sound effects and music
- [ ] UI/HUD (health bar, inventory, minimap)
- [ ] Save/load system with persistent state
- [ ] Procedural level generation
- [ ] Asset pipeline improvements
- [ ] Configuration system for game parameters

## Known Issues & Notes

- `Patrol()` function is a placeholder and not yet implemented
- The game currently supports one enemy type (Orc) in the first level
- Enemy detection uses a simple radius-based system without line-of-sight
- This is a prototype; many engine features are not yet production-ready
- Assets not included in the repository.
- Substitute assets included in the pre-release v.0.5

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests for bug fixes, features, or engine improvements.

## Author

[AlvarezRoss](https://github.com/AlvarezRoss)

---

**Last Updated**: July 2026
