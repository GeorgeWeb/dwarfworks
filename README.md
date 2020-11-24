# Dwarfworks Game Engine

### What

This is a work-in-progress early stages project so please bare with its incompleteness. I am eager to start jamming things in as quickly as possible but also do
want to take our time to investigate good/best approaches to the different systems involved. Game Engines are complex and their awesomeness is not measured only in terms of the graphical output you see rendered on the screen. There are many systems that will define and complete the engine in the future.


#### Goal

The goal is to implement a Game/Application development engine that aims to provide an easy to use, yet powerful API that allows developers to create amazing graphical applications and games.

### Building

Currently we support Windows only with a in mind and in code cross-platform design, however, implementations at this stage lack targeting multiple OSs.

For building we use Premake, it is a design choice that can be transitioned to the use of CMake at a later stage but in order to build the engine and
get started on Windows, you need Git installed and type the following command:

```bash
git clone --recursive https://github.com/GeorgeWeb/dwarfworks.git
cd dwarfworks
```

Then run the `GenerateProjects.bat` script. It currently creates a Visual Studio 2019 solution, though it can be modified to setup a VS2017 solution.
Bare in mind that C++ 17 is widely used in development so always try the latest of Visual Studio if you can.

### Continuous Integration

**CI** for Linux/Mac/Windows using GCC/Clang/MSVC will be set up soon, after the introduction of build tools scripts for automating dwarfworks building and testing.

---

This README is in a Work-In-Progress, and when there is more to be shown and/or said, new information will be added.
