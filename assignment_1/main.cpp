#include <iostream>
#include <vector>
#include <unistd.h>
#include "grid.hpp"
#include "game_of_life.h"

using StateVec = std::vector<unsigned int>;

int main() {
  // Create the game
  GameOfLife gol;
  std::string text_file;
  cin >> text_file;
  if (!gol.ReadInitialState(text_file))
    return -1;

  // get the initial state to fill in the grid
  StateVec initial_state = gol.state();

  // create the window
  sf::RenderWindow window(sf::VideoMode(gol.cols() * 32, gol.rows() * 32), "Tilemap");

  // create the grid
  Grid grid0, grid1, grid2, grid3, grid4;
  std::vector<Grid> grids{grid0, grid1, grid2, grid3, grid4};
  string image = "/home/piet/Projects/cs106bx/assignment_1/data/tileset2.ascii.png";
  unsigned int ctr = 0;
  if (!grids[ctr].load(image, 
    sf::Vector2u(32, 32), initial_state, gol.rows(), gol.cols()))
    return -1;

  // run the main loop
  while (window.isOpen())
  {
    // handle events
    sf::Event event;
    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::KeyPressed) {
        ctr += 1;
        gol.NextState();
        // we cannot deal with entries higher than 1 yet
        for (int i = 0; i != gol.rows() * gol.cols(); i ++) {
          if (gol.state()[i] == 2) {
            unsigned int one = 1;
            gol.at(i / gol.cols(), i % gol.cols()) = one;
          }
        }
        if (!grids[ctr].load(image, 
            sf::Vector2u(32, 32), gol.state(), gol.rows(), gol.cols()))
          return -1;
        }
      }

    // draw the map
    window.clear();
    window.draw(grids[ctr]);
    window.display();
  }

  return 0;
}