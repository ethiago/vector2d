#include <iostream>

#include "vector2D.hpp"

template<typename Rng>
inline void print(Rng&& rng)
{
  for(const auto& v : rng)
    std::cout << v << ",";

  std::cout << std::endl;
}

int main() {

  std::vector<int> v(9);

  for(std::size_t i = 0; i < v.size(); ++i)
    v[i] = i+1;

  auto vec2d = nstd::vector2D(std::move(v), nstd::sizes_t<2>{3,3});

  print(vec2d);
  print(vec2d.slice<0>(1));
  print(vec2d.slice<0>(1).reverse());
  print(vec2d.slice<1>(2));
  print(vec2d.slice<1>(2).reverse());
}