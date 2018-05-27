#pragma once

#include <iosfwd>

enum direction_nt
{
  x_positive_int,
  x_negative_int,
  y_positive_int,
  y_negative_int,
  z_positive_int,
  z_negative_int
};

struct DirectionPOD
{
  int direction;
};

static constexpr DirectionPOD direction_begin{x_positive_int};
static constexpr DirectionPOD x_positive{x_positive_int};
static constexpr DirectionPOD x_negative{x_negative_int};
static constexpr DirectionPOD y_positive{y_positive_int};
static constexpr DirectionPOD y_negative{y_negative_int};
static constexpr DirectionPOD z_positive{z_positive_int};
static constexpr DirectionPOD z_negative{z_negative_int};
static constexpr DirectionPOD direction_end{z_negative_int + 1};

class Direction : protected DirectionPOD
{
 public:
  Direction(DirectionPOD direction) : DirectionPOD(direction) { }

  static DirectionPOD begin() { return direction_begin; }
  static DirectionPOD end() { return direction_end; }

  bool operator!=(DirectionPOD d) const { return direction != d.direction; }

  void operator++() { ++direction; }

  int get_index() const { return direction; }
  int step() const { return (1 << ((direction >> 1) << 1)) * (1 - 2 * (direction % 2)); }

  Direction operator~() const { return DirectionPOD{ direction + 1 - 2 * (direction % 2) }; }
  Direction next() const { return DirectionPOD{ (direction + ((direction & 1) ? 4 : 2)) % 6 }; }

  friend std::ostream& operator<<(std::ostream& os, Direction const& direction);
};

//direction nd = (direction)((d + 1) % 6);
