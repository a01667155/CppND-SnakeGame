#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <iostream>
#include <memory>


class Controller {
 public:
    Controller(){std::cout<<"Controller constructor \n";};
    ~Controller(){std::cout<<"Controller destructor \n";};
    void HandleInput(bool &running, std::unique_ptr<Snake> &snake) const;

 private:
  void ChangeDirection(std::unique_ptr<Snake> &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif