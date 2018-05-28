#pragma once

#include "RotPos.h"
#include <iosfwd>
#include <array>

class ComboPositions
{
 private:
  std::array<RotPos, 13> m_positions;

 public:
  void add(int piece_nr, RotPos const& rot_pos);
  void add(ComboPositions const& combo_positions);

  friend std::ostream& operator<<(std::ostream& os, ComboPositions const& combo_positions);
};
