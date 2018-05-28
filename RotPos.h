#pragma once

#include <iosfwd>
#include <cstdint>
#include <array>

extern std::array<char const*, 24> const rot_str;

class Rot
{
 private:
  uint8_t m_rotation;
  static uint8_t constexpr non_existent = 0xff;

 public:
  Rot() : m_rotation(non_existent) { }
  explicit Rot(uint8_t rotation) : m_rotation(rotation) { }

  bool exists() const { return m_rotation != non_existent; }

  friend std::ostream& operator<<(std::ostream& os, Rot const& rot);
};

class Pos
{
 private:
  uint8_t m_translation_x : 2;
  uint8_t m_translation_y : 2;
  uint8_t m_translation_z : 2;

 public:
  Pos() { }
  explicit Pos(uint8_t translation_x, uint8_t translation_y, uint8_t translation_z) :
    m_translation_x(translation_x), m_translation_y(m_translation_y), m_translation_z(translation_z) { }

  friend std::ostream& operator<<(std::ostream& os, Pos const& pos);
};

class RotPos
{
 private:
  Rot m_rot;
  Pos m_pos;

 public:
  RotPos() { }
  RotPos(Rot rot, Pos pos) : m_rot(rot), m_pos(pos) { }

  Rot rotation() const { return m_rot; }
  Pos position() const { return m_pos; }

  bool exists() const { return m_rot.exists(); }

  friend std::ostream& operator<<(std::ostream& os, RotPos const& rot_pos);
};
