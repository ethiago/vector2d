#pragma once

namespace nstd
{

template<typename It>
struct jump_iterator : It
{
  using base = It;

  using iterator_type = typename base::iterator_type;
  using iterator_category = typename base::iterator_category;
  using value_type = typename base::value_type;
  using difference_type = typename base::difference_type;
  using reference = typename base::reference;
  using pointer = typename base::pointer;
  
  jump_iterator(base it, unsigned _jump_fator)
    : base(it), _jump_fator(_jump_fator)
  {}

  jump_iterator& operator++() noexcept
  { return (*this)+=1; }

  jump_iterator operator++(int) noexcept
  { 
    auto it = *this;
    (*this)+=1;
    return it;
  }

  jump_iterator& operator--() noexcept
  { return (*this)-=1; }

  jump_iterator operator--(int) noexcept
  { 
    auto it = *this;
    (*this)-=1;
    return it;
  }

  jump_iterator& operator+=(difference_type __n) noexcept
  { base::operator+=(__n * _jump_fator); return *this; }

  jump_iterator operator+(difference_type __n) const noexcept
  { return jump_iterator(base::operator+(__n * _jump_fator), _jump_fator); }

  jump_iterator& operator-=(difference_type __n) noexcept
  { base::operator-=(__n * _jump_fator); return *this; }

  jump_iterator operator-(difference_type __n) const noexcept
  { return jump_iterator(base::operator-(__n * _jump_fator), _jump_fator); }

  friend jump_iterator operator+(difference_type, const jump_iterator&) noexcept;
  friend difference_type operator-(const jump_iterator&, const jump_iterator&);
  

private:
  It& asBase() noexcept { return *this; }
  const It& asBase() const noexcept { return *this; }

  unsigned _jump_fator;
};

template<typename It>
inline jump_iterator<It> operator+(
  typename jump_iterator<It>::difference_type n,
  const jump_iterator<It>& it) noexcept
{ return  it + n; }

template<typename It>
inline typename jump_iterator<It>::difference_type operator-(
  const jump_iterator<It>& lhs, 
  const jump_iterator<It>& rhs) 
{ 
  if(lhs._jump_fator != rhs._jump_fator)
    throw std::invalid_argument("Jump factor must be the same");
  
  return (lhs.asBase() - rhs.asBase())/lhs._jump_fator;
}

}