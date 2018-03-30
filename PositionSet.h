#pragma once

#include "Direction.h"
#include <cstdint>
#include <iosfwd>
#include <array>

class PositionSet
{
 private:
  uint64_t m_units;

 public:
  PositionSet(uint64_t units) : m_units(units) { }

  virtual char const* name() const { return "PositionSet"; }

  void shift_towards(Direction direction);

  PositionSet& operator|=(PositionSet position_set) { m_units |= position_set.m_units; return *this; }
  friend PositionSet operator|(PositionSet position_set1, PositionSet position_set2)
    { PositionSet result{position_set1.m_units | position_set2.m_units}; return result; }

 public:
  friend std::ostream& operator<<(std::ostream& os, PositionSet const& position_set);
};

extern std::array<PositionSet, 6> const wall;
