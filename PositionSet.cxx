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
