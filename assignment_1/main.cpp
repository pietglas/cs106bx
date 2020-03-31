#include <iostream>
#include <vector>
#include <unistd.h>
#include "game_of_life.h"

using StateVec = std::vector<unsigned int>;

int main() {
  // Create the game, check whether correct values are entered
  cout << "Welcome to the game of life!" << endl;
  bool simple_game = false;
  cout << "Should cells age in this game? (1/0)" << endl;
  while (!(cin >> simple_game)) {
    cin.clear();
    cin.ignore();
    cin >> simple_game;
  }
  GameOfLife gol{simple_game};
  std::string text_file;
  cout << "Enter the path to the file from which to read the initial state" << endl;
  cin >> text_file;
  while (!gol.read_initial_state(text_file)) {
    cout << "File not found, reenter the path" << endl;
    cin.clear();
    cin.ignore();
    cin >> text_file;
    gol.read_initial_state(text_file);
  }
  std::cout << "Enter the path to the tileset: " << std::endl;
  std::string tile_set;
  cin >> tile_set;
  gol.set_tile_set(tile_set);

  // create the grid
  gol.DrawGrid();
  
  // create the window
  sf::RenderWindow window(sf::VideoMode(gol.cols() * 32, gol.rows() * 32), "Tilemap");

  // keep track of time in the game loop
  sf::Clock clock;

  // run the main loop
  while (window.isOpen())
  {
    // check the time
    sf::Time elapsed = clock.getElapsedTime();

    // if time > 2, go to the next state
    if (elapsed.asSeconds() > 2) {
      gol.NextState();
      gol.DrawGrid();
      clock.restart();  
    }

    // handle events
    sf::Event event;
    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
      
      // go to next state if a key is pressed
      else if (event.type == sf::Event::KeyPressed) {   
        gol.NextState();
        gol.DrawGrid();
        }
      }

    // draw the map
    window.clear();
    window.draw(gol.grid());
    window.display();
  }

  return 0;
}

