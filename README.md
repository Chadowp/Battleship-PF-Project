# Battleship (C++) – Raylib Graphics Edition

A player-vs-computer Battleship game built in C++ using the Raylib graphics library. This game was developed as a university group project and features mouse-based interaction, simple AI, visuals, and a leaderboard system.

## Game Features

- Player vs. Computer gameplay
- 2D graphics using Raylib
- Mouse-based targeting
- Animated ship placement and explosions
- Leaderboard system with file-based score tracking
- Background music and sound effects

## Technologies Used

- **C++** (Visual Studio 2022)
- **Raylib** graphics library
- Raylib Premake build system
- `.txt` file I/O for high score tracking
- PNG and MP3 assets

## Demo video
- https://www.youtube.com/watch?v=J2C5mFClaSo

## 📁 Project Structure
```plaintext
battleship-graphics-cpp/
├── game-premake-main.sln            # Visual Studio solution file
├── leaderboard.txt                  # Stores high scores and player names
├── game/
│   ├── game-premake-main.vcxproj    # Visual Studio project file
│   └── src/
│       └── main.cpp                 # All game logic in one file
├── Assets/
│   ├── hship5.png
│   ├── vship2.PNG
│   ├── vship3.PNG
│   ├── vship4.PNG
│   ├── test0.PNG
│   ├── bgm.mp3
│   └── other ship-related assets
├── .gitignore
├── README.md
└── RAYLIB-SETUP.md
```
## How to Build & Run

1. Clone or download this repository.
   #https://github.com/raylib-extras/raylib-quickstart
2. Make sure you have Raylib set up in Visual Studio.

3.Open game-premake-main.sln in Visual Studio.

4. Build and run the project.

## Team

This project was developed as part of a university group assignment:

    1.Laiba Fida (me) – Computer AI logic, leaderboard system, partial graphics development

    2.Hareem Ahmed Rana – Raylib integration, player logic, board handling, ship mechanics

    3.Umda Nasir – Assisted with ship sinking logic and minor features

## Audio Credit

The background music used in this project is from the game Deltarune by Toby Fox.
All rights to the original music belong to the creator.
Used for educational purposes only under fair use.

## License

This project is for academic and learning purposes only.
Not intended for commercial distribution or reuse.
