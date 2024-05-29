#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include<iostream>
#include <memory>


class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height,int d)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),difficulty(d) {std::cout<<"Snake Contructor \n";
        speed=speed*(difficulty/2);}
        
  //Rule of five implementation
  Snake(const Snake& other); // Copy constructor
  Snake& operator=(const Snake& other); // Copy assignment operator
  Snake(Snake&& other) noexcept; // Move constructor
  Snake& operator=(Snake&& other) noexcept; // Move assignment operator
  ~Snake(){std::cout<<"Snake destructor \n";}; // Destructor

  void Update();
  void killSnake();

  void GrowBody();
  bool SnakeCell(int x, int y);
  int getGridWidth(){return grid_width;}
  int getGridHeight(){return grid_height;}
  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  int difficulty=1;

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif