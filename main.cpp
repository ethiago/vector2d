#include <iostream>

#include "vector2d.hpp"

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

  auto vec2d = hub::vector2d(std::move(v), hub::sizes_t<2>{3,3});

  print(vec2d);
  print(vec2d.dimension<0>(1));
  print(vec2d.dimension<0>(1).reverse());
  print(vec2d.dimension<1>(2));
  print(vec2d.dimension<1>(2).reverse());
}