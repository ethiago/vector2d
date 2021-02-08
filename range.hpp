#pragma once

#include <iterator>

namespace hub
{

template<typename It, typename RIt = std::reverse_iterator<It>>
class range
{
  It _begin;
  It _end;

public:
  range() = default;

  range(It bg, It end)
    : _begin(bg), _end(end)
  {}

  auto begin() const noexcept { return _begin; }
  auto end() const noexcept { return _end; }

  auto rbegin() const noexcept { return RIt(_end()); }
  auto rend() const noexcept { return RIt(_begin()); }

  auto reverse() const noexcept
  { return range<RIt>(RIt(_end),RIt(_begin)); }
};

}
