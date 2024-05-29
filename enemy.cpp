#include "enemy.h"
#include "SDL.h"

Enemy::Enemy(const Enemy& other) {std::cout<<"enemy Copy constructor \n";}

// Copy assignment operator
Enemy& Enemy::operator=(const Enemy& other) {
    if (this != &other) {
        std::cout<<"enemy copy assignment \n";
    }
    return *this;
}

// Move constructor
Enemy::Enemy(Enemy&& other) noexcept {std::cout<<"enemy Move constructor \n";}

// Move assignment operator
Enemy& Enemy::operator=(Enemy&& other) noexcept {
    if (this != &other) {
        std::cout<<"enemy move assignment \n";
    }
    return *this;
}
void Enemy::Update(){
    switch (direction) {
    case Direction::kUp:
      pos_y -= speed;
      break;

    case Direction::kDown:
      pos_y += speed;
      break;

    case Direction::kLeft:
      pos_x -= speed;
      break;

    case Direction::kRight:
      pos_x += speed;
      break;
  }


  pos_x = fmod(pos_x + grid_width, grid_width);
  pos_y = fmod(pos_y + grid_height, grid_height);
}
void Enemy::changeDirection(){
    switch (direction) {
    case Direction::kUp:
    direction= Direction::kRight;
      break;

    case Direction::kDown:
    direction= Direction::kLeft;
      break;

    case Direction::kLeft:
      direction= Direction::kUp;
      break;

    case Direction::kRight:
    direction= Direction::kDown;
    break;
  }}

