#pragma once

#include <array>
#include "PositionSet.h"

using piece_type = uint64_t;
piece_type constexpr R1 = 2 + 16 + 32 + 64 + 512;
piece_type constexpr R2 = 1 + 2 + 4 + 16 + (1 << 16);
piece_type constexpr R3 = 1 + 2 + 32 + 64 + (1 << 16);
piece_type constexpr R4 = 1 + 2 + 32 + 64 + (2 << 16);
piece_type constexpr Y1 = 2 + 4 + 16 + 32 + 256;
piece_type constexpr Y2 = 1 + 16 + 32 + (1 << 16);
piece_type constexpr Y3 = 1 + 2 + 4 + 64 + (1 << 16);
piece_type constexpr Y4 = 1 + 2 + 32 + 512 + (1 << 16);
piece_type constexpr Y5 = 1 + 2 + 4 + 32 + (2 << 16);
piece_type constexpr B1 = 2 + 16 + 32 + 64 + 256;
piece_type constexpr B2 = 1 + 2 + 4 + 32 + (1 << 16);
piece_type constexpr B3 = 2 + 16 + 32 + 64 + (2 << 16);
piece_type constexpr B4 = 2 + 32 + 64 + (1 + 2 << 16);

class Piece : public PositionSet
{
 public:
  Piece(piece_type piece) : PositionSet(piece) { }
  Piece(int nr);

  char const* name() const override { return "Piece"; }

  friend std::ostream& operator<<(std::ostream& os, Piece const& piece);
};

class Pieces
{
 private:
  using s_pieces_type = std::array<Piece, 13>;
  static s_pieces_type const s_pieces;
  static Pieces* s_pieces_instance;

 public:
  ~Pieces() { delete s_pieces_instance; }

  s_pieces_type::const_iterator begin() const { return s_pieces.begin(); }
  s_pieces_type::const_iterator end() const { return s_pieces.end(); }
  Piece get(int nr) const { return s_pieces[nr]; }
  static Pieces& instance();
};
