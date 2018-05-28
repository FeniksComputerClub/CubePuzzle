#include "Piece.h"
#include "Direction.h"
#include "MultiLoop.h"
#include "RotPos.h"
#include <iostream>
#include <array>
#include <set>
#include <vector>

int main()
{
  // Generate all possible unique positions for each piece.
  std::array<std::vector<Combinations>, 13> all_positions;

  // The cross (R1) has only two unique positions, since all other positions are equivalent under rotation of the cube.
  Piece piece0 = Pieces::instance().get(0);
  all_positions[0].emplace_back(piece0, 0, RotPos());
  piece0.shift(z_positive);
  all_positions[0].emplace_back(piece0, 0, RotPos());

  // Do all other pieces.
  std::array<std::set<PositionSet>, 13> all_rotations;
  for (int piece_n = 1; piece_n < 13; ++ piece_n)
  {
    for (int rot = 0; rot < 24; ++rot)
    {
      Piece piece = Pieces::instance().get(piece_n);
      if (rot > 0)
        for (char const* p = rot_str[rot]; *p; ++p)
          piece.rotate_around(*p == 'X' ? x_positive : y_positive);
      all_rotations[piece_n].insert(piece);
    }
    for (PositionSet piece_x : all_rotations[piece_n])
    {
      do
      {
        PositionSet piece_y = piece_x;
        do
        {
          PositionSet piece_z = piece_y;
          do
          {
            all_positions[piece_n].push_back(piece_z);
          }
          while (piece_z.shift(z_positive));
        }
        while (piece_y.shift(y_positive));
      }
      while (piece_x.shift(x_positive));
    }
  }

  std::cout << "The two positions of piece #0 that are considered are:\n";
  for (auto ps : all_positions[0])
    std::cout << ps;

  // box[n] is the cube after putting in piece #n.
  std::array<PositionSet, 13> box;
  for (int p0n = 0; p0n < 2; ++p0n)
  {
    int piece_nr = 0;
    int position_nr[13] = { p0n, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    box[0] = all_positions[piece_nr][position_nr[piece_nr]];
    for (MultiLoop ml(12); !ml.finished(); ml.next_loop())
      while (ml() < all_positions[piece_nr = *ml + 1].size())
      {
        position_nr[piece_nr] = ml();
        if (piece_nr <= 3)
          std::cout << piece_nr << std::flush;
        PositionSet current_piece = all_positions[piece_nr][ml()];
        if ((box[piece_nr - 1] & current_piece))
        {
          ml.breaks(0);
          break;
        }
        box[piece_nr] = box[piece_nr - 1] | current_piece;
        if (ml.inner_loop())
        {
          std::cout << "Found solution! " << box[piece_nr] << std::endl;
          for (int p = 0; p <= 12; ++p)
            std::cout << "Piece #" << p << "; pos_nr = " << position_nr[p] << "; " << all_positions[p][position_nr[p]] << std::endl;
        }
        ml.start_next_loop_at(0);
      }
  }
}
