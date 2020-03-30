#include <iostream>
#include <vector>
#include <unistd.h>
#include "grid.hpp"
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
  while (!gol.ReadInitialState(text_file)) {
    cout << "File not found, reenter the path" << endl;
    cin.clear();
    cin.ignore();
    cin >> text_file;
    gol.ReadInitialState(text_file);
  }

  // get the initial state to fill in the grid
  StateVec initial_state = gol.state();

  // create the window
  sf::RenderWindow window(sf::VideoMode(gol.cols() * 32, gol.rows() * 32), "Tilemap");

  // create the grid
  Grid grid;
  string image = "/home/piet/Projects/cs106bx/assignment_1/data/tileset2.ascii.png";
  unsigned int ctr = 0;
  if (!grid.load(image, 
    sf::Vector2u(32, 32), initial_state, gol.rows(), gol.cols()))
    return -1;

  sf::Clock clock;

  // run the main loop
  while (window.isOpen())
  {
    // check the time
    sf::Time elapsed = clock.getElapsedTime();

    // if time > 2, go to the next state
    if (elapsed.asSeconds() > 2) {
      gol.NextState();
      
      if (!grid.load(image, 
          sf::Vector2u(32, 32), gol.state(), gol.rows(), gol.cols()))
        return -1;
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
        if (!grid.load(image, 
            sf::Vector2u(32, 32), gol.state(), gol.rows(), gol.cols()))
          return -1;
        }
      }

    // draw the map
    window.clear();
    window.draw(grid);
    window.display();
  }

  return 0;
}

