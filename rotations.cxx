#include "matrix.h"
#include "MultiLoop.h"
#include <iostream>
#include <array>
#include <string>
#include <set>
#include <map>
#include <algorithm>

struct MatrixCompare
{
  bool operator()(Matrix<int> const& m1, Matrix<int> const& m2) const
  {
    for (int row = 0; row < 3; ++row)
      for (int col = 0; col < 3; ++col)
      {
        if (m1.get(row, col) != m2.get(row, col))
          return m1.get(row, col) < m2.get(row, col);
      }
    return false;
  }
};

struct VersionsCompare
{
  bool operator()(std::string const& s1, std::string const& s2) const
  {
    if (s1.length() != s2.length())
      return s1.length() < s2.length();
    return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
  }
  bool operator()(std::set<std::string, VersionsCompare> const& a, std::set<std::string, VersionsCompare> const& b) const
  {
    std::string const& s1(*a.begin());
    std::string const& s2(*b.begin());
    return this->operator()(s1, s2);
  }
};

int main()
{
  std::array<Matrix<int>, 3> m = { Matrix<int>(3, 3), Matrix<int>(3, 3), Matrix<int>(3, 3) };
  enum a { X, Y, Z };
  m[X].put(0, 0, 1);
  m[X].put(1, 2, -1);
  m[X].put(2, 1, 1);
  m[Y].put(0, 2, 1);
  m[Y].put(1, 1, 1);
  m[Y].put(2, 0, -1);
  m[Z].put(0, 1, -1);
  m[Z].put(1, 0, 1);
  m[Z].put(2, 2, 1);

  std::map<Matrix<int>, std::set<std::string, VersionsCompare>, MatrixCompare> versions;
  versions[IdentityMatrix<int>(3, 3)].insert("I");
  for (int loops = 1; loops <= 5; ++loops)
  {
    for (MultiLoop ml(loops); !ml.finished(); ml.next_loop())
    {
      while (ml() < 2)
      {
        if (ml.inner_loop())
        {
          Matrix<int> p = IdentityMatrix<int>(3, 3);
          std::string str;
          for (int i = loops - 1; i >= 0 ; --i)
          {
            str += (char)('X' + ml[i]);
            p *= m[ml[i]];
          }
          std::set<std::string, VersionsCompare> ts;
          ts.insert(str);
          auto r = versions.emplace(p, ts);
          if (!r.second && str.find("XXXX") == std::string::npos && str.find("YYYY") == std::string::npos && str.find("ZZZZ") == std::string::npos)
            r.first->second.insert(str);
        }
        ml.start_next_loop_at(0);
      }
    }
  }
  int c = 0;
  std::vector<std::set<std::string, VersionsCompare>> vec_versions;
  for (auto e : versions)
  {
    //std::cout << e.first << "; det = " << e.first.determinant() << std::endl;
    vec_versions.push_back(e.second);
  }
  std::sort(vec_versions.begin(), vec_versions.end(), VersionsCompare());
  char const* sep = "\"";
  for (auto e : vec_versions)
  {
#if 0
    std::cout << "    " << ++c;
    char const* sep = c < 10 ? ".  " : ". ";
    for (auto s : e)
    {
      std::cout << sep << s;
      sep = " = ";
    }
    std::cout << std::endl;
#else
    std::cout << sep << *e.begin() << '"';
    sep = ", \"";
#endif
  }
  std::cout << std::endl;
}
