# Papaya

Papaya is my attempt at a modern, straight-forward game engine. It's built in C++17 and largely inspired by TheCherno/Hazel and Godot.

## Roadmap

There aren't many features right now but the goal will be to have a full framework for creating a game from start to finish using one codebase. The goal is to support Windows, macOS, x11 Linux Systems, iOS, and Android.

## Building

First clone the repository using:

'''git clone --recursive https://github.com/James51332/Papaya'''

Make sure you have the required dependecies installed. Windows requires that you have cygwin, gnu-g++, and gmake installed to build. Run the build.bat and type '''make''' into the terminal in the root directory. MacOS requires the xcode build tools installed. Run the build.sh script and type '''make''' to build. 