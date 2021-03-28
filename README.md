# Papaya

![Papaya Banner](/resources/branding/Banner.png)

Papaya is my attempt at a modern, straight-forward game engine. It's built in C++17 and largely inspired by TheCherno/Hazel and Godot. I have worked on about a dozen different attemts at game engines however this one has the cleanest codebase, is the easiest to use, and has the most features! I have also recently started a small [blog](https://jdab.xyz) over at [jdab.xyz](https://jdab.xyz)

## Getting Started

First off, clone the repository using `git clone --recursive https://github.com/James51332/Papaya.git`. If you didn't use `--recursive` or downloaded from the github website, run `git submodule update --init` to fetch submodules. Papaya uses premake to generate project files. Currently, Papaya can be built using, Visual Studio 2019, Xcode, or GNU-GCC (MinGW-64 on Windows). `cd` into the source directory and run the batch or script file corresponding to the system you want to use to build. If you built using a makefile, you can run `make` and optionally `config=[Debug, Release, Dist]` to compile Papaya into a static library and build the Sandbox project along with it. Xcode and Visual Studio can be built using their respective tools.

## Features

As we're currently are focusing on building a strong foundation for performant applications, Papaya doesn't have a whole lot of features yet. At the time of writing, Papaya supports Windows and MacOS builds and uses OpenGL 4.x for it's rendering. Our API is built strongly and will be able to utilize the performance of next-gen render API's soon!

## Roadmap

The biggest feature under development is the 2D Renderer and workflow. We are working to create a toolset that can be used to build a full game from start to finish in our editor and export to MacOS and Windows from it. Papaya's in-depth roadmap is layed out on our public [Trello page](https://trello.com/b/225yK9yq/papaya), and is subject to change at any time.

## Contributions

Contributions are welcome and encouraged! If you see something in the code that could be improved, or want to add an entirely new feature, the best way to get your code into the core engine is to submit a pull request. If you would like to become a member of our team directly, join our [discord](https://discord.gg/x4gxGc9YMa)!
