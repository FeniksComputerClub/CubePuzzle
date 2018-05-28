#include "ComboPositions.h"
#include <iostream>
#include <cassert>

void ComboPositions::add(int piece_nr, RotPos const& rot_pos)
{
  m_positions[piece_nr] = rot_pos;
}

void ComboPositions::add(ComboPositions const& combo_positions)
{
  for (int piece_nr = 0; piece_nr < 13; ++piece_nr)
  {
    if (combo_positions.m_positions[piece_nr].exists())
    {
      assert(!m_positions[piece_nr].exists());
      m_positions[piece_nr] = combo_positions.m_positions[piece_nr];
    }
  }
}

std::ostream& operator<<(std::ostream& os, ComboPositions const& combo_positions)
{
  char const* sep = "";
  for (int piece_nr = 0; piece_nr < 13; ++piece_nr)
  {
    if (combo_positions.m_positions[piece_nr].exists())
    {
      os << sep << "#" << piece_nr << " " << combo_positions.m_positions[piece_nr];
      sep = ", ";
    }
  }
}
