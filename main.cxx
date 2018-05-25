#include "Piece.h"
#include "Direction.h"
#include <iostream>

int main()
{
  Piece piece = Pieces::instance().get(4);
  std::cout << piece << std::endl;
  piece.mirror_in(z_negative);
  std::cout << piece << std::endl;

#if 0
  //prints out the walls
  for (Direction d = Direction::begin(); d != Direction::end(); ++d)
  {
    //std::cout << d << ": " << wall[d.get_index()] << std::endl;
    std::cout << d << ": opposite dir = " << ~d << std::endl;
  }
#endif
}
