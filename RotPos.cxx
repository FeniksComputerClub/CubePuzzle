#include "RotPos.h"
#include <iostream>
#include <cassert>

// This array was generated with rotations.cxx.
std::array<char const*, 24> const rot_str = {
 "I", "X", "Y", "XX", "XY", "YX", "YY", "XXX", "XXY", "XYX", "XYY", "YXX",
 "YYX", "YYY", "XXXY", "XXYX", "XXYY", "XYXX", "XYYY", "YXXX", "YYYX",
 "XXXYX", "XYXXX", "XYYYX"
};

std::ostream& operator<<(std::ostream& os, RotPos const& rot_pos)
{
  os << rot_pos.rotation() << ' ' << rot_pos.position();
  return os;
}

std::ostream& operator<<(std::ostream& os, Rot const& rot)
{
  assert(rot.exists());
  os << rot_str[rot.m_rotation];
  return os;
}

std::ostream& operator<<(std::ostream& os, Pos const& pos)
{
  os << "offset:<" << pos.m_translation_x << "," << pos.m_translation_y << "," << pos.m_translation_z << ">";
  return os;
}
