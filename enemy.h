#ifndef ENEMY_H
#define ENEMY_H
#include "SDL.h"
#include<iostream>


class Enemy
{
public:
Enemy(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        pos_x(grid_width / 3),
        pos_y(grid_height / 3) {std::cout<<"Enemy Contructor \n";}
  Enemy(const Enemy& other); // Copy constructor
  Enemy& operator=(const Enemy& other); // Copy assignment operator
  Enemy(Enemy&& other) noexcept; // Move constructor
  Enemy& operator=(Enemy&& other) noexcept; // Move assignment operator
  ~Enemy(){std::cout<<"Enemy destructor \n";}; // Destructor
  void changeDirection();



  enum class Direction { kUp, kDown, kLeft, kRight };
  float speed{0.05};
  void Update();
  float pos_x;
  float pos_y;



private:
    SDL_Point point;
    Direction direction = Direction::kLeft;
    int grid_width;
    int grid_height;

};
#endif