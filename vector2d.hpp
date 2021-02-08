#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <vector>
#include <stdexcept>

#include "jump_iterator.hpp"
#include "range.hpp"

namespace hub
{
  template<std::size_t N>
  using sizes_t = std::array<std::size_t, N>;

  namespace detail
  {
    template<typename T, typename A = std::allocator<T>>
    using container_t = std::vector<T,A>;

    template<std::size_t N>
    inline std::size_t product(sizes_t<N> sizes)
    { return std::accumulate(sizes.begin(), sizes.end(), 1.0, std::multiplies{}); }
  }


/**
*  vector2D its a wrapper over std::vector that packs a 2d array data
*  in a way that one can iterate the entire data, or a specific indexed dimesion
*/
template<typename T, typename Allocator = std::allocator<T>>
class vector2d
{
public:
  constexpr static std::size_t dimensions = 2;
  using sizes_t = sizes_t<dimensions>;
  using container_type = detail::container_t<T, Allocator>;

private:
  sizes_t _n;
  container_type _container;

public:
  using value_type = typename container_type::value_type;
  using allocator_type = typename container_type::allocator_type;
  using size_type = typename container_type::size_type;
  using difference_type = typename container_type::difference_type;
  using reference = typename container_type::reference;
  using const_reference = typename container_type::const_reference;
  using pointer = typename container_type::pointer;
  using const_pointer = typename container_type::const_pointer;
  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator = typename container_type::const_reverse_iterator;

  using jump_iterator = hub::jump_iterator<iterator>;
  using const_jump_iterator = hub::jump_iterator<const_iterator>;


  vector2d() noexcept = default;

  explicit vector2d(sizes_t sizes)
      : _n(std::move(sizes))
      , _container(detail::product(_n))
  { }

  vector2d(container_type cont, sizes_t sizes)
      : _n(std::move(sizes))
      , _container(std::move(cont))
  { 
    if(std::size(_container) != detail::product(_n))
      throw std::invalid_argument("products of n must be equal of rng size");
  }

  auto& at(std::size_t i, std::size_t j)
  { return _container.at( i * _n[1] + j ); }

  const auto& at(std::size_t i, std::size_t j) const
  { return _container.at( i *_n[1] + j); }

  auto empty() const noexcept
  { return _container.empty(); }

  auto cbegin() const noexcept
  { return _container.cbegin(); }
  auto cend() const noexcept
  { return _container.cend(); }
  auto begin() const noexcept
  { return _container.cbegin(); }
  auto end() const noexcept
  { return _container.cend(); }
  auto rbegin() const noexcept
  { return _container.crbegin(); }
  auto rend() const noexcept
  { return _container.crend(); }
  auto crbegin() const noexcept
  { return _container.crbegin(); }
  auto crend() const noexcept
  { return _container.crend(); }
  

  template<std::size_t dim>
  auto dimension(std::size_t idx) const noexcept
  {
    static_assert(dim < dimensions, "vector2D only have two dimensions");

    if constexpr (dim == 0)
    {
      auto bg = _container.cbegin() + idx*_n[1];
      return range{bg, bg+_n[1]};
    }else
    {
      auto bg = const_jump_iterator(_container.cbegin() + idx, _n[1]);
      return range{bg, bg+_n[0]};
    }          
  }

  container_type&& release() noexcept
  { return std::move(_container); }

  pointer data() noexcept
  { return _container.data(); }

  const_pointer data() const noexcept
  { return _container.data(); }

  const sizes_t& n() const noexcept
  { return _n; }
};

}