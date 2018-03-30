#include "Piece.h"
#include "Direction.h"
#include <iostream>

int main()
{
  for (Direction d = Direction::begin(); d != Direction::end(); ++d)
  {
    std::cout << d << std::endl;
  }
}
