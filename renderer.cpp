#include "renderer.h"
#include <iostream>
#include <string>
#include<memory>

// Constructor
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

// Destructor
Renderer::~Renderer() {
  Cleanup();
}

// Copy Constructor
Renderer::Renderer(const Renderer &other)
    : screen_width(other.screen_width),
      screen_height(other.screen_height),
      grid_width(other.grid_width),
      grid_height(other.grid_height) {
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  std::cout<<"Renderer Copy constructor \n";
}

// Copy Assignment Operator
Renderer& Renderer::operator=(const Renderer &other) {
  if (this == &other) {
    return *this;
  }

  Cleanup();

  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, other.screen_width,
                                other.screen_height, SDL_WINDOW_SHOWN);

  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  std::cout<<"Renderer copy assignment \n";

  return *this;
}

// Move Constructor
Renderer::Renderer(Renderer &&other) noexcept
    : screen_width(other.screen_width),
      screen_height(other.screen_height),
      grid_width(other.grid_width),
      grid_height(other.grid_height),
      sdl_window(other.sdl_window),
      sdl_renderer(other.sdl_renderer) {
  other.sdl_window = nullptr;
  other.sdl_renderer = nullptr;
  std::cout<<"Renderer move constructor";
}

// Move Assignment Operator
Renderer& Renderer::operator=(Renderer &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  Cleanup();

  sdl_window = other.sdl_window;
  sdl_renderer = other.sdl_renderer;

  other.sdl_window = nullptr;
  other.sdl_renderer = nullptr;
  std::cout<<"Renderer move assignment operator \n";
  return *this;
}

// Cleanup function
void Renderer::Cleanup() {
  if (sdl_renderer != nullptr) {
    SDL_DestroyRenderer(sdl_renderer);
    sdl_renderer = nullptr;
  }
  if (sdl_window != nullptr) {
    SDL_DestroyWindow(sdl_window);
    sdl_window = nullptr;
  }
  SDL_Quit();
}

void Renderer::Render(std::unique_ptr<Snake> &snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(std::unique_ptr<Snake> &snake, SDL_Point const &food, SDL_Point const &Obstacle) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render Obstacle
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  block.x = Obstacle.x * block.w;
  block.y = Obstacle.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);


  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(std::unique_ptr<Snake> &snake, SDL_Point const &food, SDL_Point const &Obstacle,
std::unique_ptr<Enemy> &enemy) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  //Render Enemy
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  block.x = static_cast<int>(enemy->pos_x)  * block.w;
  block.y = static_cast<int>(enemy->pos_y) * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);


  // Render Obstacle
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  block.x = Obstacle.x * block.w;
  block.y = Obstacle.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);


  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}


void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
