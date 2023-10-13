# Punkyoi
Punkyoi is a 2D runner game inspired by the Chrome's Dino game.

![](docs/Screenshot.jpg)
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
![alt](docs/ClassDiagram_stage_2.png)
## Extended
![alt](docs/ClassDiagramFull_stage_2.png)

## Class interaction
![alt](docs/InteractionDiagram.png)

# Build instructions
- CMake build target `punkyoiBundle`.
- **Windows installation wizard:**
    Installation wizard at [GitHub Releases](https://github.com/CreoDen-dev/punkyoi/releases/tag/v1.0.0). Runs as normal windows setup, requires Punkyoi.msi.