#pragma once

#include <iterator>

namespace nstd
{

template<typename It, typename RIt = std::reverse_iterator<It>>
struct range
{
  range() = default;

  range(It bg, It end)
    : _begin(bg), _end(end)
  {}

  auto begin() const noexcept { return _begin; }
  auto end() const noexcept { return _end; }

  template<std::enable_if_t<!std::is_same_v<RIt,void>, bool> = true>
  auto rbegin() const noexcept { return RIt(_end()); }

  template<std::enable_if_t<!std::is_same_v<RIt,void>, bool> = true>
  auto rend() const noexcept { return RIt(_begin()); }

  template<std::enable_if_t<!std::is_same_v<RIt,void>, bool> = true>
  auto reverse() const noexcept
  { return range<RIt>(RIt(_end),RIt(_begin)); }

private:
  It _begin;
  It _end;
};

}
