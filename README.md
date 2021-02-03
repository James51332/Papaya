# Papaya
![Papaya Banner](/resources/branding/Banner.png)

Papaya is my attempt at a modern, straight-forward game engine. It's built in C++17 and largely inspired by TheCherno/Hazel and Godot. I have worked on about a dozen different attemts at game engines however this one has the cleanest codebase, is the easiest to read, and has the most thought put into it!

## Roadmap

There aren't many features right now but the goal will be to have a full framework for creating a game from start to finish using one codebase. The goal is to support Windows, macOS, x11 Linux Systems, iOS, and Android. I wouldn't even say there are any real features yet. You can just create a window and use OpenGL function calls on macOS.

## Building

First clone the repository using:
`git clone --recursive https://github.com/James51332/Papaya`

Make sure you have the required dependecies installed. Windows requires that you have cygwin, gnu-g++, and gmake installed to build. Run scripts/build.bat and type `make` into the terminal in the root directory. MacOS requires the xcode build tools installed. Run scripts/build.sh and then type `make` in the src directory to build. There is currently only support for these platforms however I hope to add Linux and mobile support soon!
