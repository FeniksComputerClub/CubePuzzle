#pragma once

#include "ComboPositions.h"
#include "PositionSet.h"
#include <memory>

class Combinations
{
 private:
  PositionSet m_position_set;
  std::unique_ptr<ComboPositions> m_combo_positions;

 public:
  Combinations() : m_combo_positions(new ComboPositions) { }
  Combinations(PositionSet position_set, int piece_nr, RotPos const& rot_pos) : m_position_set(position_set)
  {
    m_combo_positions->add(piece_nr, rot_pos);
  }

  Combinations& operator+=(Combinations const&);

  friend std::ostream& operator<<(std::ostream& os, Combinations const& combinations);
};
