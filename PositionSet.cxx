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
	  os << " \314\266/";
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

void PositionSet::swap_units(PositionSet mask, int distance)
{
  uint64_t tmp = mask.m_units & m_units;
  if (distance < 0)
  {
    tmp >>= -distance;
    mask.m_units >>= -distance;
  }
  else
  {
    tmp <<= distance;
    mask.m_units <<= distance;
  }
  uint64_t diff = tmp ^ (m_units & mask.m_units);
  m_units ^= diff;
  if (distance < 0)
    diff <<= -distance;
  else
    diff >>= distance;
  m_units ^= diff;
}

void PositionSet::invert_axis(Direction direction)
{
  PositionSet mask = wall[(~direction).get_index()];
  int distance = 3 * direction.step();
  swap_units(mask, distance);
  mask.shift_towards(direction);
  swap_units(mask, direction.step());
}

void PositionSet::swap_axes(Direction direction1, Direction direction2)
{
  direction1 = ~direction1;
  int const offset = direction1.step() + direction2.step();
  PositionSet mask = wall[(~direction1).get_index()] & wall[(~direction2).get_index()];
  for (int distance = 3; distance > 0; --distance)
  {
    swap_units(mask, distance * offset);
    PositionSet tmp = mask;
    mask.shift_towards(direction1);
    tmp.shift_towards(direction2);
    mask |= tmp;
  }
}

bool PositionSet::shift(Direction direction)
{
  if ((*this & wall[direction.get_index()]))
    return false;
  shift_towards(direction);
  return true;
}

void PositionSet::rotate_around(Direction direction)
{
  direction = direction.next();
  swap_axes(direction, direction.next());
  invert_axis(direction);
  while (shift(x_negative));
  while (shift(y_negative));
  while (shift(z_negative));
}
