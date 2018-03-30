#include "PositionSet.h"
#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, PositionSet const& position_set)
{
  os << position_set.name() << ":\n";
  for (int z = 3; z >= 0; --z)
    for (int x = 0; x <= 3; ++x)
    {
      os << std::string((3 - x), ' ');
      for (int y = 0; y <= 3; ++y)
      {
	uint64_t bit = (uint64_t)1 << (x + y * 4 + z * 16);
	if ((position_set.m_units & bit))
	  os << " ̶/";
	else
	  os << " .";
      }
      os << '\n';
    }
  return os;
}

void PositionSet::shift_towards(Direction direction)
{
  switch (direction.get_index())
  {
    case 0:
      m_units <<= 1;
      break;
    case 1:
      m_units >>= 1;
      break;
    case 2:
      m_units <<= 4;
      break;
    case 3:
      m_units >>= 4;
      break;
    case 4:
      m_units <<= 16;
      break;
    case 5:
      m_units >>= 16;
      break;
  }
}

std::array<PositionSet, 6> const wall = { PositionSet{0}, PositionSet{0}, PositionSet{0}, PositionSet{0}, PositionSet{0}, PositionSet{0} };
