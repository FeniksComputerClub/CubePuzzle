#include "Piece.h"
#include "Direction.h"
#include <iostream>

int main()
{
  for (int p = 0; p < 4; ++p)
  {
    Piece piece(p);
    std::cout << piece << std::endl;
  }
}
