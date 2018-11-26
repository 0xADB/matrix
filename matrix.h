#pragma once

#include <utility>
#include <map>
#include <array>

namespace gof
{


  template<typename T>
  class flyweight_matrix
  {
    public:
      /**
       * @brief A flyweight matrix cell
       *
       */

      template<typename IndexValueT, size_t N>
	struct cell
	{
	  using index_value_type = IndexValueT;
	  std::array<index_value_type, N> index;
	  flyweight_matrix * matrix;
	};

      using key_type = index_type;
      using value_type = T;
      using size_type = std::size_t;
      using difference_type = std::ptrdiff_t;
      using key_compare = std::less<index_type>;
      using reference = value_type&;
      using const_reference = const value_type&;
      using allocator_type = std::allocator<const index_type, T>;
      using storage_type = std::map<index_type, value_type, std::less<index_compare>, allocator_type>;
      using pointer = std::allocator_traits<allocator_type>::pointer;
      using const_pointer = std::allocator_traits<allocator_type>::const_pointer;

    private:

    public:
      class iterator
      {
	private:
	  using storage_iterator_type = storage_type::iterator;

	public:
	  using self_type = iterator;
	  using reference = T&;
	  using pointer = T*;

	public:
	  iterator()
	    : _storage_iterator()
	  {}

	  iterator(const self_type& other)
	    : _storage_iterator(other._storage_iterator)
	  {}

	  iterator(self_type&& other)
	    : _storage_iterator(std::move(other._storage_iterator))
	  {}

	  self_type& operator=(const self_type& other)
	  {
	    _storage_iterator = other._storage_iterator;
	    return *this;
	  }

	  self_type& operator=(self_type&& other)
	  {
	    _storage_iterator = std::move(other._storage_iterator);
	    return *this;
	  }

	  self_type& operator++()
	  {
	    ++_storage_iterator;
	    return *this;
	  }

	  self_type operator++(int)
	  {
	    self_type prev(*this);
	    ++_storage_iterator;
	    return prev;
	  }

	  self_type& operator--()
	  {
	    --_storage_iterator;
	    return *this;
	  }

	  self_type operator--(int)
	  {
	    self_type prev(*this);
	    --_storage_iterator;
	    return prev;
	  }

	  bool operator==(const self_type& other)
	  {
	    return (other._storage_iterator == this->_storage_iterator);
	  }

	  friend bool operator==(const iterator& lhs, const iterator& rhs)
	  {
	    return (lhs._storage_iterator == rhs._storage_iterator);
	  }

	  //bool operator!=(const self_type& other) const
	  //{
	  //  return (other._storage_iterator != this->_storage_iterator);
	  //}

	  friend bool operator!=(const iterator& lhs, const iterator& rhs)
	  {
	    return (lhs._storage_iterator != rhs._storage_iterator);
	  }

	  reference operator*() const
	  {
	    return _storage_iterator->second;
	  }

	  pointer operator->() const
	  {
	    return &_storage_iterator->second;
	  }

	private:
	  storage_iterator_type _storage_iterator;
      };

      class const_iterator
      {
	private:
	  using storage_iterator_type = storage_type::const_iterator;

	public:
	  using self_type = const_iterator;
	  using reference = const T&;
	  using pointer = const T*;

	public:
	  const_iterator()
	    : _storage_iterator()
	  {}

	  const_iterator(const self_type& other)
	    : _storage_iterator(other._storage_iterator)
	  {}

	  const_iterator(self_type&& other)
	    : _storage_iterator(std::move(other._storage_iterator))
	  {}

	  self_type& operator=(const self_type& other)
	  {
	    _storage_iterator = other._storage_iterator;
	    return *this;
	  }

	  self_type& operator=(self_type&& other)
	  {
	    _storage_iterator = std::move(other._storage_iterator);
	    return *this;
	  }

	  self_type& operator++()
	  {
	    ++_storage_iterator;
	    return *this;
	  }

	  self_type operator++(int)
	  {
	    self_type prev(*this);
	    ++_storage_iterator;
	    return prev;
	  }

	  self_type& operator--()
	  {
	    --_storage_iterator;
	    return *this;
	  }

	  self_type operator--(int)
	  {
	    self_type prev(*this);
	    --_storage_iterator;
	    return prev;
	  }

	  bool operator==(const self_type& other)
	  {
	    return (other._storage_iterator == this->_storage_iterator);
	  }

	  friend bool operator==(const const_iterator& lhs, const const_iterator& rhs)
	  {
	    return (lhs._storage_iterator == rhs._storage_iterator);
	  }

	  // bool operator!=(const self_type& other) const
	  // {
	  //   return (other._storage_iterator != this->_storage_iterator);
	  // }

	  friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs)
	  {
	    return (lhs._storage_iterator != rhs._storage_iterator);
	  }

	  reference operator*() const
	  {
	    return _storage_iterator->second;
	  }

	  pointer operator->() const
	  {
	    return &_storage_iterator->second;
	  
	private:
	  storage_iterator_type _storage_iterator;
      };

      flyweight_matrix()
	: _storage()
      {}

      flyweight_matrix(const flyweight_matrix& other)
	: _storage(other._storage)
      {}

      flyweight_matrix(flyweight_matrix&& other)
	: _storage(std::move(other._storage))
      {}

      flyweight_matrix& operator=(const flyweight_matrix& other)
      {
	_storage = other._storage;
	return *this;
      }

      flyweight_matrix& operator=(flyweight_matrix&& other)
      {
	_storage = std::move(other._storage);
	return *this;
      }

      value_type operator[](const key_type& key) const
      {
	auto it = _storage.find(key);
	if (it != std::end(_storage))
	  return it->second;
	return std::move(value_type());
      }

    private:
      _storage_type _storage;
  };
} // namespace gof
