#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include<iostream>
#include <memory>
#include<mutex>
#include<condition_variable>
#include "enemy.h"
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int difficulty);
  ~Game(){std::cout<<"Game destructor \n";}
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
 
 private:
  std::unique_ptr<Snake> snake;
  std::unique_ptr<Enemy> enemy;
  SDL_Point food;
  SDL_Point obstacle;
  bool running{true};


  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int _difficulty{1};

  void PlaceFood();
  void Update(bool &running);
  void PlaceObstacle();
  void UpdateGame(bool &running);
  void RenderGame(Renderer &renderer, std::size_t target_frame_duration, bool &running);
  std::mutex mtx;
  std::condition_variable cv;
  bool updated = false;

};

#endif