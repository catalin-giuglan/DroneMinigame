# Drone Delivery Minigame

## Overview
A 3D drone simulation game where players control a drone to pick up packages and deliver them to designated locations while navigating through a procedurally generated forest environment with obstacles.

## Features
- ✅ **3D Drone Control**: Full 6 degrees of freedom movement (pitch, roll, yaw, and translation)
- ✅ **Procedural Environment**: Randomly generated forests and rock formations
- ✅ **Collision Detection**: Realistic collision handling with trees, rocks, and terrain
- ✅ **Package Delivery System**: Pick up packages and deliver them to destinations to score points
- ✅ **Camera Controls**: Third-person camera that follows the drone
- ✅ **Physics Simulation**: Realistic drone movement and altitude control

## Controls
- `W/S`: Move forward/backward
- `A/D`: Rotate left/right (yaw)
- `Q/E`: Descend/Ascend
- `Arrow Keys`: Control pitch (up/down) and roll (left/right)
- `Space`: Pick up or drop packages
- `P`: Toggle field of view (normal/wide)

## Technical Details
The game is built using a custom 3D engine with OpenGL. Key components include:

### Rendering
- Custom mesh creation for drone parts, trees, rocks, and packages
- Vertex and fragment shaders for rendering
- Dynamic lighting and coloring

### Physics & Collision
- Bounding sphere collision detection for the drone
- Specialized collision algorithms for tree trunks, tree crowns, and rocks
- Ground collision detection

### Game Mechanics
- Random package and destination generation
- Package pickup and delivery validation

## Project Structure
- **Tema2 Class**: Main game class handling rendering, updates, and input
- **Tema2Camera**: Custom camera implementation for drone following
- **Mesh Creation**: Functions for creating various 3D objects
- **Input Handling**: Keyboard and mouse input processing
- **Collision Detection**: Multiple collision detection algorithms for different object types
