#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include<memory>
#include "enemy.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  Renderer(const Renderer &other); // Copy Constructor
  Renderer& operator=(const Renderer &other); // Copy Assignment Operator
  Renderer(Renderer &&other) noexcept; // Move Constructor
  Renderer& operator=(Renderer &&other) noexcept; // Move Assignment Operator

  void Render(std::unique_ptr<Snake> &snake, SDL_Point const &food);
  void Render(std::unique_ptr<Snake> &snake, SDL_Point const &food, SDL_Point const &Obstacle);
  void Render(std::unique_ptr<Snake> &snake, SDL_Point const &food, SDL_Point const &Obstacle, std::unique_ptr<Enemy> &enemy);

  void UpdateWindowTitle(int score, int fps);

 private:
  void Cleanup();

  SDL_Window *sdl_window{nullptr};
  SDL_Renderer *sdl_renderer{nullptr};

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
