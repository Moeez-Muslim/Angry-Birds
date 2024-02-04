
#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window), isDragging(false), velocity(0.f, 0.f), availableBirds(4), numPigs(1), score(0), gameState(GameState::Intro)
{
  srand(time(NULL));

  numStructures = 1;
  addStructure(sf::Vector2f(600.f, 300.f));
}

void Game::addStructure(const sf::Vector2f& position)
{
  Structure newStructure;
  newStructure.sprite.setTexture(structureTexture);
  newStructure.sprite.setPosition(position);
  structures.push_back(newStructure);
}

void Game::updateStructures(float dt)
{
  float gravity = 500.f; // Adjust gravity as needed

  for (auto& structure : structures)
  {
    structure.sprite.move(0.f, gravity * dt);
  }
}

Game::~Game()
{
}

bool Game::init()
{
  // Load bird texture
  //if (!bird_texture.loadFromFile("Data/Images/kenney_animalpackredux/PNG/Round/parrot.png"))
  //{
  //  // Failed to load the bird texture, handle the error
  //  return false;
  //}
    
 

  // Set the bird sprite texture and initial positions
  bird.setTexture(bird_texture);
  birdPositions.push_back(sf::Vector2f(100.f, 500.f));
  birdPositions.push_back(sf::Vector2f(200.f, 500.f));
  birdPositions.push_back(sf::Vector2f(300.f, 500.f));
  birdPositions.push_back(sf::Vector2f(400.f, 500.f));

  if (!menuBackgroundTexture.loadFromFile("Data/Images/menu.jpg"))
  {
    // Failed to load the menu background texture, handle the error
    return false;
  }

  // Load background texture
  if (!backgroundTexture.loadFromFile("Data/Images/lvl1.png"))
  {
    // Failed to load the background texture, handle the error
    return false;
  }

  // Set the background sprite texture
  backgroundSprite.setTexture(backgroundTexture);
  // Set the position of the background sprite to cover the window
  backgroundSprite.setPosition(0.f, 0.f);

  // Load pig texture
  if (!pigTexture.loadFromFile("Data/Images/kenney_animalpackredux/PNG/Square/pig.png"))
  {
    // Failed to load the pig texture, handle the error
    return false;
  }

  // Set the pig sprite texture
  pigSprite.setTexture(pigTexture);
  // Set the initial position of the pig on the screen
  pigSprite.setPosition(800.f, 500.f);

  // Load structure texture
  if (!structureTexture.loadFromFile("Data/Images/kenney_physicspack/Spritesheet/spritesheet_elements.png"))
  {
    // Failed to load the structure texture, handle the error
    return false;
  }

  // Set the structure sprite texture
  structureSprite.setTexture(structureTexture);
  // Set the initial position of the structure on the screen
  structureSprite.setPosition(600.f, 300.f);

  // Load floor texture
  if (!floorTexture.loadFromFile("Data/Images/kenney_physicspack/Spritesheet/spritesheet_tiles.png"))
  {
    // Failed to load the floor texture, handle the error
    return false;
  }

  // Create the floor sprites and set their positions
  // You can adjust the positions and count of floor tiles as needed
  if (!loadFloorTiles())
  {
    return false;
  }

  // Initialize birds
  for (int i = 0; i < 4; ++i)
  {
    birds.push_back(bird);
    birds[i].setPosition(birdPositions[i]);
  }
   // Set the initial number of structures


  return true;
}

bool Game::loadFloorTiles()
{
  for (int i = 0; i < 10; ++i)
  {
    sf::Sprite floorSprite;
    floorSprite.setTexture(floorTexture);
    floorSprite.setPosition(i * 100.f, 600.f); // Adjust the Y position based on your game world
    floorSprites.push_back(floorSprite);
  }
  return true;
}

void Game::reset()
{
  // Reset the game elements
  isDragging = false;
  velocity = sf::Vector2f(0.f, 0.f);
  for (int i = 0; i < 4; ++i)
  {
    birds[i].setPosition(birdPositions[i]);
  }
  availableBirds = 4;
  numPigs = 1;
  score = 0;
}

bool Game::checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
  return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

bool Game::isWinConditionMet()
{
  // Implement your win condition logic here
  // For example, check if all pigs are destroyed
  return numPigs == 0;
}

bool Game::isLoseConditionMet()
{
  // Implement your lose condition logic here
  // For example, check if all birds are fired and there are still pigs on screen
  return availableBirds == 0 && numPigs > 0;
}



void Game::update(float dt)
{
  // Apply gravity to the pig's vertical velocity to make them move down
  float gravity = 500.f; // Adjust gravity as needed
  for (int i = 0; i < numPigs; ++i)
  {
    pigSprite.move(0.f, gravity * dt);
  }

  // Apply gravity to the structure's vertical velocity to make it move down
  for (int i = 0; i < numStructures; ++i)
  {
    structureSprite.move(0.f, gravity * dt);
  }
  updateStructures(dt);

  // Check for collisions between the bird and structures/pigs
  for (int i = 0; i < 4; ++i)
  {
    // Check collision with structures
    if (birds[i].getGlobalBounds().intersects(structureSprite.getGlobalBounds()))
    {
      // Apply resistance to the bird's movement
      // You can adjust the resistance factor as needed to control the effect
      float resistanceFactor = 0.1f;
      velocity -= velocity * resistanceFactor;
    }

    // Check collision with pigs
    if (birds[i].getGlobalBounds().intersects(pigSprite.getGlobalBounds()))
    {
      // Handle the collision, e.g., increase the score and despawn the pig
      score += 10;
      numPigs--;
    }
  }

  // Update the bird position if it's dragging and has been released
  if (isDragging && velocity != sf::Vector2f(0.f, 0.f))
  {
    // Apply the velocity to the bird position to move it
    bird.move(velocity * dt);

    // Apply gravity to the bird's vertical velocity to make the trajectory curve
    float gravity = 500.f; // Adjust gravity as needed
    velocity.y += gravity * dt;

    // Check for collision with the pig
    if (checkCollision(bird, pigSprite))
    {
      // Handle the collision, e.g., increase the score and despawn the pig
      score += 10;
      numPigs--;
    }
  }

  // Check if the bird's velocity is zero and reset its position
  if (!isDragging && velocity == sf::Vector2f(0.f, 0.f))
  {
    // Despawn the fired bird and move the next bird to the firing position
    for (int i = 0; i < 4; ++i)
    {
      if (birds[i].getPosition() == bird.getPosition())
      {
        availableBirds--;
        break;
      }
    }

    // Check if all birds are fired
    if (availableBirds == 0)
    {
      // This logic is removed from here and will be handled in the main.cpp
    }
    else
    {
      // Move the next available bird to the firing position
      for (int i = 0; i < 4; ++i)
      {
        if (birds[i].getPosition() == birdPositions[i])
        {
          birds[i].setPosition(100.f, 500.f);
          break;
        }
      }
    }
  }
}

void Game::renderIntro()
{
  // Implement the rendering of the introductory screen here
}

void Game::renderWin()
{
  // Implement the rendering of the win state screen here
  drawText("You Win!", 400.f, 300.f, 40, sf::Color::White);
  drawText("Score: " + std::to_string(score), 400.f, 400.f, 30, sf::Color::White);
  drawText("Click or press any key to restart", 350.f, 500.f, 20, sf::Color::White);
}

void Game::renderLose()
{
  // Implement the rendering of the lose state screen here
  drawText("You Lose!", 400.f, 300.f, 40, sf::Color::White);
  drawText("Score: " + std::to_string(score), 400.f, 400.f, 30, sf::Color::White);
  drawText("Click or press any key to restart", 350.f, 500.f, 20, sf::Color::White);
}

void Game::render()
{
  // Draw the game elements to the window

  // Clear the window
  window.clear(sf::Color::Black);

  // Render the appropriate background based on the game's current state
  if (gameState == GameState::Intro)
  {
    // Render the intro state background (if you have one)
    window.draw(menuBackgroundSprite);
  }
  else if (gameState == GameState::Gameplay)
  {
    // Render the gameplay state background
    window.draw(backgroundSprite);
  }
  else if (gameState == GameState::Win)
  {
    // Render the win state background (if you have one)
    window.draw(backgroundSprite);
  }
  else if (gameState == GameState::Lose)
  {
    // Render the lose state background (if you have one)
    window.draw(backgroundSprite);
  }

  // Draw the pig sprite
  window.draw(pigSprite);

  // Draw the structure sprite
  window.draw(structureSprite);

  // Draw the floor sprites
  for (const auto& floorSprite : floorSprites)
  {
    window.draw(floorSprite);
  }

  // Draw the bird sprites
  for (int i = 0; i < availableBirds; ++i)
  {
    window.draw(birds[i]);
  }

  // Draw the score text
  drawText("Score: " + std::to_string(score), 10.f, 10.f, 30, sf::Color::White);

  // Render the appropriate state based on the game's current state
  if (isWinConditionMet())
  {
    renderWin();
  }
  else if (isLoseConditionMet())
  {
    renderLose();
  }
  else
  {
    renderIntro(); // For simplicity, we'll always render the intro state first
  }

  // Display the window content
  window.display();
}

void Game::drawText(const std::string& text, float x, float y, int fontSize, const sf::Color& color)
{
  sf::Font font;
  if (font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(fontSize);
    scoreText.setFillColor(color);
    scoreText.setString(text);
    scoreText.setPosition(x, y);

    window.draw(scoreText);
  }
}


void Game::mouseClicked(sf::Event event)
{
  // Check if there are available birds and get the position of the next bird to fire
  if (availableBirds > 0)
  {
    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
    for (int i = 0; i < 4; ++i)
    {
      if (birds[i].getGlobalBounds().contains(mousePos) && birds[i].getPosition() == birdPositions[i])
      {
        isDragging = true;
        startPos = birds[i].getPosition();
        break;
      }
    }
  }
}

void Game::mouseReleased(sf::Event event)
{
  // Check if the bird is being dragged and has been released
  if (isDragging)
  {
    isDragging = false;
    endPos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

    // Calculate the velocity of the bird based on the drag distance and speed factor
    float speedFactor = 0.1f; // Adjust the speed factor as needed
    velocity = (startPos - endPos) * speedFactor;
  }
}

void Game::mouseMoved(sf::Event event)
{
  // Update the end position when the mouse is moved during the drag
  if (isDragging)
  {
    endPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
  }
}

void Game::keyPressed(sf::Event event)
{
  // Handle key press event here
}


