#pragma once

#include <cstdint>
#include <iosfwd>

class PositionSet
{
 private:
  uint64_t m_units;

 public:
  PositionSet(uint64_t units) : m_units(units) { }

  virtual char const* name() const { return "PositionSet"; }

 public:
  friend std::ostream& operator<<(std::ostream& os, PositionSet const& position_set);
};
