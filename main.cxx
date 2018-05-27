#include "Piece.h"
#include "Direction.h"
#include "MultiLoop.h"
#include <iostream>
#include <array>
#include <set>
#include <vector>

std::array<char const*, 24> rot_str = {
 "", "X", "Y", "XX", "XY", "YX", "YY", "XXX", "XXY", "XYX", "XYY", "YXX",
 "YYX", "YYY", "XXXY", "XXYX", "XXYY", "XYXX", "XYYY", "YXXX", "YYYX",
 "XXXYX", "XYXXX", "XYYYX"
};

int main()
{
  std::array<std::vector<PositionSet>, 13> all_positions;
  std::array<std::set<PositionSet>, 13> all_rotations;
  for (int piece_n = 0; piece_n < 13; ++ piece_n)
  {
    for (int rot = 0; rot < 24; ++rot)
    {
      Piece piece = Pieces::instance().get(piece_n);
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
  int nr_pieces = 0;
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
