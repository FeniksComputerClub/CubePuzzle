#include "Piece.h"
#include <iostream>

//static
std::array<Piece, 13> const Pieces::s_pieces = {
  R1,           // This is the cross. It must be the first piece.
  Y2,           // This is the only piece that exists of 4 units. It must be second.
  Y1,           // 192 possible unique positions.
  Y3,           // 216 possible unique positions.
  Y5,           // 216 possible unique positions.
  B4,           // 216 possible unique positions.
  B1,           // 384 possible unique positions.
  R2,           // 432 possible unique positions.
  R3,           // 432 possible unique positions.
  R4,           // 432 possible unique positions.
  Y4,           // 432 possible unique positions.
  B2,           // 432 possible unique positions.
  B3            // 432 possible unique positions.
};

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
