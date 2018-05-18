#include "Piece.h"
#include <iostream>

//static
std::array<Piece, 13> const Pieces::s_pieces = { R1, R2, R3, R4, Y1, Y2, Y3, Y4, Y5, B1, B2, B3, B4 };

std::ostream& operator<<(std::ostream& os, Piece const& piece)
{
  os << static_cast<PositionSet const&>(piece);
  return os;
}

Piece::Piece(int nr) : PositionSet(Pieces::instance().get(nr))
{
}

//static
Pieces& Pieces::instance()
{
  if (s_pieces_instance == nullptr)
    s_pieces_instance = new Pieces;
  return *s_pieces_instance;
}

Pieces* Pieces::s_pieces_instance;
