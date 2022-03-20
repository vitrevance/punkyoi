# Punkyoi
## The 2D game
Basic API and strcture is implemented
## Used patterns
- Builder - IWorldProvider, EndpointBuilder
- Factory - PlatformFactory

# UML Diagrams
## Basic
![alt](ClassDiagram.png)
## Extended
![alt](ClassDiagramFull.png)

# Build instructions
## Linux
- ### Manual with premake5
    This project uses premake5 to generate Makefile

    Dependencies:
    ```console
    $ apt-get install libglew-dev
    $ apt-get install libglfw3
    $ apt-get install libglfw3-dev
    ```
    Project
    ```console
    $ premake5 gmake
    $ make config=release
    ```

- ### Build script
    ```console
    $ ./build.sh
    ```