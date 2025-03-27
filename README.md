# World Cup 2026 Simulator (C++)

Welcome to the **World Cup 2026 Simulator**! This project is a C++ program designed to simulate the FIFA World Cup 2026 tournament using multiple randomized game modes. The simulator takes into account the current FIFA international team rankings and employs advanced data structures such as binary trees and vectors to store the tournament's knockout rounds and groups. It supports both **Round Robin** and **Single Match** formats for group and knockout stages.

## Results of teams who won over 10 iterations of the game.
- Argentina: 3
- Senegal: 1
- Germany: 1
- Switzerland: 1
- Belgium: 1
- Brazil: 1
- Italy: 1
- England: 1

> [!NOTE]  
> This was results from running the program ten times. Based on the Fifa rankings from 25th March, each team is given a value between 1 and 49, top 5 teams etc have 49, last X team have 1, this score plays out in the match winners algorithm.
> As we can see it has given some surprising results, Senegal were able to win the tournament, alongside Belgium and Switzerland.

## Features

- **Randomized Game Modes**: The simulator supports a variety of game modes where teams are randomly allocated to groups and the knockout rounds.
- **Team Rankings**: Teams are ranked based on the latest FIFA international team rankings, adding a realistic touch to the simulation.
- **Knockout Rounds**: The simulator uses binary trees to store and manage the knockout rounds of the tournament.
- **Group Stages**: Vectors are used to store and manage groups of teams, simulating a dynamic group stage with both Round Robin and Single Match formats.
- **Simulation Options**: Customize the simulation by choosing between different match formats and group structures.
- **Realistic FIFA Integration**: Based on the current FIFA international team rankings and historical data, the simulator simulates games accordingly.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Game Modes](#game-modes)
- [Data Structures](#data-structures)
- [License](#license)

## Installation

To run the **World Cup 2026 Simulator**, follow the steps below:

### Prerequisites

- **C++ Compiler** (GCC, Clang, Visual Studio, etc.)
- **C++17** (or higher) for language features

### Steps to Build

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/world-cup-2026-simulator.git
    cd world-cup-2026-simulator
    ```

2. Compile the project using `g++` or your preferred C++ compiler:
    ```bash
    g++ -std=c++17 -o world_cup_simulator main.cpp
    ```

3. Run the program:
    ```bash
    Build the project then run the .exe file
    ```

## Usage

Once the project is compiled and executed, the program will simulate the World Cup 2026 tournament. You can customize the simulation by specifying the number of groups, match formats, and whether to use a Round Robin or Single Match format for the group stage.

### Command-line Arguments

- `--groups <number>`: Specifies the number of groups (default: 8).
- `--round-robin`: Simulates group stages with a Round Robin format.
- `--single-match`: Simulates group stages with a Single Match format.
- `--randomize`: Randomizes team allocation into groups and knockout rounds.
- `--seed <number>`: Set a custom seed for randomization.

Example:
```bash
./world_cup_simulator --groups 8 --round-robin --randomize
