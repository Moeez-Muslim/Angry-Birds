
#ifndef ANGRYBIRDS_GAME_H
#define ANGRYBIRDS_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

enum class GameState
{
  Intro,
  Gameplay,
  Win,
  Lose
};

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void reset();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void mouseMoved(sf::Event event);
  void keyPressed(sf::Event event);
  int getScore() const { return score; }
  class Structure
  {
   public:
    sf:: Sprite sprite;
  };
  void addStructure(const sf::Vector2f& position);
  void updateStructures(float dt);

  bool isLoseConditionMet();

  bool isWinConditionMet();

 private:
  // Other members
  // ...

  bool loadFloorTiles();
  std::vector<sf::Sprite> floorTiles;
  sf::RenderWindow& window;
  bool isDragging;
  sf::Vector2f velocity;
  sf::Vector2f startPos;
  sf::Vector2f endPos;
  sf::Sprite bird;
  sf::Texture bird_texture;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  sf::Texture menuBackgroundTexture;
  sf::Sprite menuBackgroundSprite;
  sf::Texture pigTexture;
  sf::Sprite pigSprite;
  sf::Texture structureTexture;
  sf::Sprite structureSprite;
  sf::Texture floorTexture;
  std::vector<sf::Sprite> floorSprites; // Floor sprites
  std::vector<sf::Sprite> birds; // Store the 4 birds available for firing
  std::vector<sf::Vector2f> birdPositions; // Initial positions of the 4 birds
  int availableBirds; // Number of available birds
  int numPigs; // Number of pigs on the screen
  int score;
  int numStructures;

  GameState gameState;

  bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
  void renderIntro();
  void renderWin();
  void renderLose();
  void drawText(const std::string& text, float x, float y, int fontSize, const sf::Color& color);
  std::vector<Structure> structures;
  float structureGravity;
};

#endif // ANGRYBIRDS_GAME_H
