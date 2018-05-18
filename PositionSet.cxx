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
	  os << " /\314\266";
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
    case x_positive_int:
      m_units <<= 1;
      break;
    case x_negative_int:
      m_units >>= 1;
      break;
    case y_positive_int:
      m_units <<= 4;
      break;
    case y_negative_int:
      m_units >>= 4;
      break;
    case z_positive_int:
      m_units <<= 16;
      break;
    case z_negative_int:
      m_units >>= 16;
      break;
  }
}

PositionSet create_wall(Direction direction)
{
  switch (direction.get_index())
  {
    case x_positive_int:
      return PositionSet{(uint64_t)0x1111111111111111 << 3};
    case x_negative_int:
      return PositionSet{(uint64_t)0x1111111111111111};
    case y_positive_int:
      return PositionSet{(uint64_t)0xf000f000f000f << 3 * 4};
    case y_negative_int:
      return PositionSet{(uint64_t)0xf000f000f000f};
    case z_positive_int:
      return PositionSet{(uint64_t)0xffff << 3 * 16};
    case z_negative_int:
      return PositionSet{(uint64_t)0xffff};
  }
}

std::array<PositionSet, 6> const wall = {
  create_wall(x_positive),
  create_wall(x_negative),
  create_wall(y_positive),
  create_wall(y_negative),
  create_wall(z_positive),
  create_wall(z_negative)
};
