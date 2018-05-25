#include "Direction.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, Direction const& direction)
{
  switch (direction.direction)
  {
    case 0:
      os << "x_positive";
      break;
    case 1:
      os << "x_negative";
      break;
    case 2:
      os << "y_positive";
      break;
    case 3:
      os << "y_negative";
      break;
    case 4:
      os << "z_positive";
      break;
    case 5:
      os << "z_negative";
      break;
    case 6:
      os << "direction_end";
      break;
  }
  return os;
}

PositionSet const wall[6];

