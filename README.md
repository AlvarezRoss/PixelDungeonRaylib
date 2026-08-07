# PixelDungeonRaylib

A 2D top-down pixel-art dungeon engine and prototype written in C using raylib. Designed as a modular foundation for tile-based games, it includes tile-based room rendering, a frame-based animation system, collision and camera utilities, basic enemy AI (chase + attack), and an integrated map editor — suitable for experimentation, learning, and as a starting point for further development.

---

## Quickstart

What you need:
- A C compiler (gcc/clang)
- make
- raylib (desktop)
- On Linux you’ll also want the usual X/OpenGL development packages (see the GitHub Actions workflow for an example list)

Build:
- The Makefile handles Linux and Windows (MSYS2) flavors.
  - Linux/macOS:
    - make
    - ./game
  - Windows (MSYS2 / MinGW):
    - make
    - game.exe

There’s also a small `build.bash` script in the repo (you can try it), but using the Makefile is the straightforward option.

Clean:
- make clean

Note: the repo references an `Assets/` folder (tilesets and character sprites). Those assets are not included here, so you’ll need to add them into `Assets/` for the game to run.

---

## What this is

PixelDungeonRaylib is a simple demo — a playable slice of a top-down dungeon with:
- tile-based room rendering
- basic character animation (sprite sheets)
- collision handling
- a simple enemy that chases and attacks
- an in-game editor to place tiles/entities and then run the custom map

It’s small and intentionally straightforward so you can read the code and experiment.

---

## Repo layout (file-by-file)

Root
- `Makefile` — build rules. Cross-platform-ish: detects Windows vs Unix and links raylib appropriately.
- `build.bash` — quick bash build script (useful for simple runs).
- `README.md` — this file.
- `Todo.txt` — notes and future ideas from the author.
- `LICENSE` — MIT.

.github
- `workflows/build.yml` — CI that builds raylib and compiles the game on Linux and Windows runners, and uploads artifacts.

src/
- `main.c`
  - Program entry and main loop. Sets up graphics, camera, player/enemy(s), and the map editor modes.
  - Handles player input, basic enemy logic, and drawing via raylib.
- `helper.h` / `helper.c`
  - Core types and helpers: Animation, Character, Graphics structs; timers and camera helpers; animation stepping; init/deinit helpers for characters and graphics.
  - Lots of little utilities you’ll use everywhere else.
- `map.h` / `map.c`
  - Tile enums, tileset loading, and map drawing/collision helpers.
  - Contains a test ground layer matrix and object layer matrix that the demo uses to draw the sample level.
  - Helper to compute a tile’s source rect from its enum.
- `enemyBehaviours.h` / `enemyBehaviours.c`
  - Simple enemy AI functions: `ChasePlayer()` moves an enemy toward the player; `FacePlayer()` flips facing; `Patrol()` is present as a placeholder.
- `editor.h` / `editor.c`
  - In-editor map data and UI code.
  - Lets you paint tiles, place entities (player, orc, skeleton), and then initialize/run the custom map you built.

Assets
- The code expects image files under `Assets/` (tileset and character sprite sheets). Add your own sprites or the originals into `Assets/` before running.

---

## Gameplay basics

Controls used by the demo:
- W/A/S/D — move
- Left click — attack (or in-editor selection, depending on mode)
- F1 — toggle fullscreen
- F2 — toggle editor mode
- Space — pause/unpause
- Enter — start custom map from editor

Mechanics in the demo:
- Basic 8-direction movement with frame-based animations.
- Enemies detect the player in a radius and will chase + attempt attacks.
- Tile collisions stop movement and are handled with directional resolution.
- Editor mode lets you paint tiles and place entities, then run the map.

---

## License

MIT — see the LICENSE file.

---

Author
- AlvarezRoss — https://github.com/AlvarezRoss

Last scanned: August 2026
