#pragma once

#include <cstdint>
#include <iosfwd>

class PositionSet
{
 private:
  uint64_t m_units;

 public:
  std::ostream& operator<<(std::ostream& os, PositionSet const& position_set);
};
