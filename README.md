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
[Premake 5](https://premake.github.io/) is required to build Punkyoi.

Supported platforms:
- Linux (Ubuntu 20.04+)
- Windows (Windows 10)

## Linux
- ### Manual with premake5
    Using premake5 to generate Makefile

    Dependencies:
    ```console
    $ apt-get install libglew-dev
    $ apt-get install libglfw3
    $ apt-get install libglfw3-dev
    ```
    Project
    ```console
    $ premake5 gmake
    $ make config=release_x86_64
    ```

- ### Build script
    ```console
    $ ./build.sh
    ```
## Windows
- ### Manual with premake5
    Using premake5 to generate Visual Studio solution

    ```console
    $ premake5 vs2022
    ```
