#include "Piece.h"
#include "Direction.h"
#include <iostream>

int main()
{
  for (Direction d = Direction::begin(); d != Direction::end(); ++d)
  {
    int i = d.get_index();
  }
}
