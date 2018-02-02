#include "Piece.h"
#include <iostream>

//static
uint64_t const Piece::s_pieces[13] = { R1, R2, R3, R4, Y1, Y2, Y3, Y4, Y5, B1, B2, B3, B4 };

std::ostream& operator<<(std::ostream& os, Piece const& piece)
{
  os << static_cast<PositionSet const&>(piece);
  return os;
}
