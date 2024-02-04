# Angry Birds Game

![Angry Birds Logo](link_to_logo_image.png)

## Overview

This is a simple implementation of the classic Angry Birds game using C++ and the SFML (Simple and Fast Multimedia Library) framework. The game features bird launching, pig targets, and structures for a player to knock down.

## Features

- Bird launching and trajectory simulation.
- Pigs as targets with collision detection.
- Structures that react to gravity and can be toppled.
- Win and lose conditions.
- Score tracking.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- C++ compiler with C++11 support.
- SFML library installed. ([SFML Installation Guide](https://www.sfml-dev.org/tutorials/2.5/))

## How to Run

Follow these steps to run the Angry Birds game:

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/angry-birds-game.git
   ```

2. Compile the source code:

   ```bash
   cd angry-birds-game
   g++ main.cpp Game.cpp -o AngryBirdsGame -lsfml-graphics -lsfml-window -lsfml-system
   ```

3. Run the executable:

   ```bash
   ./AngryBirdsGame
   ```

## Controls

- Mouse click: Launch the bird.
- Mouse drag: Aim the bird trajectory.
- Key press: [Implement your custom key controls]

## Screenshots

[Include screenshots or gameplay GIFs here]

## Contributing

Contributions are welcome! Please follow our [contribution guidelines](CONTRIBUTING.md).

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to the creators of SFML for providing a great multimedia library.

## Author

Moeez Muslim

Feel free to fork and modify this project according to your needs. If you have any questions or suggestions, please open an issue!
