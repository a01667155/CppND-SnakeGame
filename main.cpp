#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "Score.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  int difficulty;
 do {
        std::cout << "Enter your difficulty level [1-5]: ";
        std::cin >> difficulty;
        // Clear the error flag on cin (in case of invalid input)
        if (std::cin.fail()) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            difficulty = 0; // Set to an invalid value to keep the loop going
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the rest of the input
        }
    } while (difficulty < 1 || difficulty > 5);
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight,difficulty);
  game.Run(controller, renderer, kMsPerFrame);
  //renderer.~Renderer();
  std::cout << "Game has terminated successfully!\n";
  int score = game.GetScore();
  std::cout << "Score: " << score << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  CheckHighScore(score);
  return 0;
}