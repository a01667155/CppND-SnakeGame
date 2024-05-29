#include "game.h"
#include <iostream>
#include "SDL.h"
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include "enemy.h"

//std::ofstream logFile("game_log.txt");

Game::Game(std::size_t grid_width, std::size_t grid_height, int difficulty)
    : snake(std::make_unique<Snake>(grid_width, grid_height, difficulty)),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  //logFile << "Game constructor \n";
  _difficulty = difficulty;
  PlaceFood();
  if (_difficulty>4) {
    enemy = std::make_unique<Enemy>(grid_width,grid_height);
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    if (!snake->SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      //logFile << "Placed food at: " << x << ", " << y << std::endl;
      return;
    }
  }
}

void Game::PlaceObstacle() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    if (!snake->SnakeCell(x, y) && food.x != x && food.y != y) {
      obstacle.x = x;
      obstacle.y = y;
      //logFile << "Placed obstacle at: " << x << ", " << y << std::endl;
      return;
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;
  
  

  std::thread update_thread(&Game::UpdateGame, this, std::ref(running));
  std::thread render_thread(&Game::RenderGame, this, std::ref(renderer), target_frame_duration, std::ref(running));

  while (running) {
    frame_start = SDL_GetTicks();

    controller.HandleInput(running, snake);

    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  update_thread.join();
  render_thread.join();
}

void Game::UpdateGame(bool &running) {
  while (running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::unique_lock<std::mutex> lock(mtx);
    //logFile << "UpdateGame: Acquired lock" << std::endl;
    Update(running);
    updated = true;
    //logFile << "UpdateGame: Notifying render thread" << std::endl;
    cv.notify_one();
  }
}

void Game::RenderGame(Renderer &renderer, std::size_t target_frame_duration, bool &running) {
  while (running) {
    std::unique_lock<std::mutex> lock(mtx);
    //logFile << "RenderGame: Waiting for update" << std::endl;
    cv.wait(lock, [this] { return updated; });
    //logFile << "RenderGame: Acquired lock and proceeding to render" << std::endl;
    updated = false;
    if (_difficulty>4){
      renderer.Render(snake, food, obstacle, enemy);
    }else
    {
      if (_difficulty > 3) {
      renderer.Render(snake, food, obstacle);
      } else{renderer.Render(snake, food);}
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(target_frame_duration));
  }
}

void Game::Update(bool &running) {
  if (!snake->alive) {
    //ogFile << "Update: Snake is dead, stopping game" << std::endl;
    running = false;
    return;
  }

  snake->Update();

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);
  int enemy_x = static_cast<int>(enemy->pos_x);
  int enemy_y = static_cast<int>(enemy->pos_y);

  if (food.x == new_x && food.y == new_y) {
    //logFile << "Update: Snake ate food at " << new_x << ", " << new_y << std::endl;
    score++;
    PlaceFood();
    if (_difficulty > 3) {
      PlaceObstacle();
    }
    if (_difficulty>4)
    {
      enemy->changeDirection();
    }
    
    snake->GrowBody();
    snake->speed += 0.02;
  }
  if(_difficulty>4){
    enemy->Update();
    if (enemy_x == new_x && enemy_y == new_y) {
      snake->killSnake();
      std::cout<<"Snake killed by enemy \n";
    }
  }


  if (_difficulty > 3) {
    if (obstacle.x == new_x && obstacle.y == new_y) {
      //logFile << "Update: Snake hit obstacle at " << new_x << ", " << new_y << std::endl;
      snake->killSnake();
    }

  }
}
