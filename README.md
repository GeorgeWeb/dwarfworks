# Dwarfworks Game Engine

### Why yet another Game Engine attempt ?

1. Firstly, we believe that there is nothing wrong with experimenting and learning new skills, right?
2. My main goal is clear and it is to implement a Game/Application development engine that aims to provide an easy to use, yet powerful API that allows developers to create amazing graphical applications and games.
3. Learning best practies for software design and architecture is always a great motivation, thus the reason why we are spending countless hours in research so that others can benefit from this project and also teach themselves in a good general design of a Game Engine and also use it to create cool games in the process.
4. I (**GeorgeWeb**), and my collaborator **wolfstrasz** are aiming to create the game we've always wanted alongside the custom AA Game Engine we've also always desired to create with no intension to impress the world but learn all techniques for ourselves and then be able to apply them in a professional environment at the end.
5. This is a work-in-progress early stages project so please bare with the incompleteness with it. We do want to jam things in as quickly as possible but also do
want to take our time to investigate the best approach to each system. Game Engines are complex and their awesomeness is not measured in terms of the graphical
output you see rendered on the screen. There are many systems that make up a complete **cross-platform** engine such that Dwarfworks is going to be.

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

**CI** for Linux/Mac/Windows , GCC/Clang/MSVC will be set up very soon, after we decide on our final set of build tools and cross-platform design.

---

This README is in a Work-In-Progress, and when there is more to be shown and/or said, new information will be added.
