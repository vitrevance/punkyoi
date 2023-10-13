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
![alt](ClassDiagram.png)
## Extended
![alt](ClassDiagramFull.png)

## Class interaction
![alt](InteractionDiagram.png)

# Build
Build target `punkyoiBundle` with CMake