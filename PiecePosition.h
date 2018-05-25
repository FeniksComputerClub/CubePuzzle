#include "Piece.h"

class PiecePosition : public PositionSet
{
 public:
  PiecePosition(PositionSet const& position_set) : PositionSet(position_set) { }

  char const* name() const override { return "PiecePosition"; }
};
