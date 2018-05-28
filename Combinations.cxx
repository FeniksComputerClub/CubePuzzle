#include "Combinations.h"
#include <cassert>
#include <iostream>

Combinations& Combinations::operator+=(Combinations const& combinations)
{
  assert((m_position_set & combinations.m_position_set) == 0);
  m_position_set |= combinations.m_position_set;
  m_combo_positions->add(*combinations.m_combo_positions);
  return *this;
}

std::ostream& operator<<(std::ostream& os, Combinations const& combinations)
{
  return os << *combinations.m_combo_positions << ": " << combinations.m_position_set;
}
