#include "Game.h"
#include <iostream>

int main()
{
  // Create the game window
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Angry Birds!");
  window.setFramerateLimit(60);

  // Create an instance of the game class
  Game game(window);

  // Run the init function of the game class and check if it initializes successfully
  if (!game.init())
  {
    std::cerr << "Failed to initialize the game." << std::endl;
    return 1;
  }

  // Set the initial game state to Intro
  GameState gameState = GameState::Intro;

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // Check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      // Handle events based on the current game state
      if (gameState == GameState::Intro)
      {
        // Handle intro state events
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
        {
          // Switch to the Gameplay state when the player clicks or presses any key
          gameState = GameState::Gameplay;
        }
      }
      else if (gameState == GameState::Gameplay)
      {
        // Handle gameplay state events
        if (event.type == sf::Event::MouseButtonPressed)
        {
          game.mouseClicked(event);
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
          game.mouseReleased(event);
        }
        else if (event.type == sf::Event::MouseMoved)
        {
          game.mouseMoved(event);
        }
        else if (event.type == sf::Event::KeyPressed)
        {
          game.keyPressed(event);
        }
      }
      else if (gameState == GameState::Win || gameState == GameState::Lose)
      {
        // Handle win and lose state events
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
        {
          // Reset the game and switch back to the Intro state
          game.reset();
          gameState = GameState::Intro;
        }
      }
    }

    // Calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    // Update the game based on the current game state
    if (gameState == GameState::Gameplay)
    {
      game.update(dt);

      // Check if the win or lose condition is met and switch to the respective state
      if (game.isWinConditionMet())
      {
        gameState = GameState::Win;
      }
      else if (game.isLoseConditionMet())
      {
        gameState = GameState::Lose;
      }
    }

    // Render the game based on the current game state
    if (gameState == GameState::Intro)
    {
      // Display the introductory screen
      // For simplicity, we'll assume the intro screen transitions to the gameplay instantly
      gameState = GameState::Intro;
    }
    else if (gameState == GameState::Gameplay)
    {
      // Render the gameplay elements
      game.render();
    }
    else if (gameState == GameState::Win)
    {
      // Display the win state screen
      // You can implement the logic to display the win screen here
      // For example, show a "You Win!" message, display the final score
      // and wait for a click to restart the game
      std::cout << "You Win! Score: " << game.getScore() << std::endl;
    }
    else if (gameState == GameState::Lose)
    {
      // Display the lose state screen
      // You can implement the logic to display the lose screen here
      // For example, show a "You Lose!" message and wait for a click to restart the game
      std::cout << "You Lose! Score: " << game.getScore() << std::endl;
    }
  }

  return 0;
}
