# Punkyoi
## The 2D game
Punkyoi is a 2D runner game inspired by the Chrome's Dino game.
#### Controlls:
- Jump - space
- Pull to the ground - left shift

## Used patterns
- Builder - IWorldProvider
- Factory - PlatformFactory
- Singletone - Punkyoi
- Observer - Entity, EventListener
- Adaptor AssetManager
- CoR - EventListener + EventBus
- Command - Event

# UML Diagrams
## Basic
![alt](ClassDiagram_stage_2.png)
## Extended
![alt](ClassDiagramFull_stage_2.png)

## Class interaction
![alt](InteractionDiagram.png)

# Build instructions
- CMake build target `punkyoiBundle`.
- **Windows installation wizard:**
    Installation wizard at ./Punkyoi/Release/setup.exe. Runs as normal windows setup, requires Punkyoi.msi.