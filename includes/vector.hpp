/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:26:07 by spoliart          #+#    #+#             */
/*   Updated: 2022/04/11 18:37:39 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "utils.hpp"

namespace ft
{

	/**
	 * @brief This container store elements and auto manage memory usage
	 *
	 * @tparam T The type of the elements stores in the vector
	 * @tparam Alloc The allocator type, set by default to std::allocator<T>
	 */
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{

	public:
	/* Member types */
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;
		// typedef ft::random_access_iterator<value_type> iterator;
		// typedef ft::random_access_iterator<const value_type> const_iterator;
		// typedef ft::reverse_iterator<iterator> reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	/* Member functions */
		/**
		 * @brief Default constructor.
		 * Constructs an empty container, with no elements.
		 * 
		 * @param alloc The allocator type, set  by default to std::allocator<T>
		 */
		explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc),
																		  _size(0),
																		  _capacity(0),
																		  _data(NULL)
		{
		}

		/**
		 * @brief Fill constructor
		 * 
		 * @param n 
		 * @param val 
		 * @param alloc 
		 */
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) : _alloc(alloc),
																		  _size(n),
																		  _capacity(n)
		{
			_data = _alloc.allocate(n);
			while (n--)
				_alloc.construct(&_data[n], val);
		}

		/**
		 * @brief Construct a new vector object
		 *
		 * @tparam InputIterator
		 * @param first
		 * @param last
		 * @param alloc
		 */
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last,
		// 	   const allocator_type &alloc = allocator_type())
		// {
		// }

		/**
		 * @brief Construct a new vector object
		 *
		 * @param x
		 */
		vector(const vector &x) : _data(NULL)
		{
			*this = x;
		}

		~vector(void)
		{
			this->destroy();
		}

		vector &operator=(const vector &rhs)
		{
			if (this != &rhs)
			{
				if (this->_data)
					this->destroy();
				this->_alloc = rhs._alloc;
				this->_size = rhs._size;
				this->_capacity = rhs._size;
				this->_data = _alloc.allocate(this->_capacity);
				for (size_type n = 0; n < this->_size; n++)
					_alloc.construct(&this->_data[n], rhs[n]);
			}
			return *this;
		}

		/* Iterators */

		/* Capacity */

		/**
		 * @brief Returns the number of element in the vector
		 * @return The number of elements in the container.
		 **/
		size_type size(void) const { return _size; }

		/**
		 * @brief Returns the maximum number of elements that the vector can hold.
		 * @return The maximum number of elements a vector container can hold as content.
		 **/
		size_type max_size(void) const { return _alloc.max_size(); }

		/**
		 * @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		 * @return The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
		 **/
		size_type capacity(void) const { return _capacity; }

		/**
		 * @brief Returns whether the vector is empty (i.e. whether its size is 0).
		 * @return true if the container size is 0, false otherwise.
		 **/
		bool empty(void) const
		{
			return _size == 0;
		}

		/**
		 * @brief 
		 * 
		 * @param n 
		 */
		void reserve (size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("ft::reserve");
			else if (n > this->capacity())
			{
				;
			}
		}

		/* Element access */

		reference operator[](size_type n) { return _data[n]; }

		const_reference operator[](size_type n) const { return _data[n]; }

		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
			return _data[n];
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("vector::_M_range_check: __n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(_size) + ")");
			return _data[n];
		}

		reference front(void) { return *_data; }

		const_reference front(void) const { return *_data; }

		reference back(void) { return _data[_size - 1]; }

		const_reference back(void) const { return _data[_size - 1]; }

		/* Modifiers */

		/*
			bad_alloc: no realloc
			decrease capacity and size: no realloc
			increase capacity and size: realloc
		*/

		/**
		 * @brief
		 *
		 * @param n
		 * @param val
		 */
		void assign(size_type n, const value_type &val)
		{
			if (n > this->max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");

			if (n > this->_capacity) {
				for (size_type i = 0; i < this->_size; i++)
					_alloc.destroy(&_data[i]);
				_alloc.deallocate(_data, this->_capacity);

				this->_capacity = n;
				this->_data = _alloc.allocate(n);
			}
			else {
				for (size_type i = 0; i < n; i++) {
					_alloc.destroy(&_data[i]);
					_alloc.construct(&_data[i], val);
				}
				this->_size = n;
			}
		}

		void push_back (const value_type& val)
		{
			if (this->_size + 1 > this->max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");

			if ( this->_size + 1 > this->_capacity) {
				value_type *tmp_data = this->_data;

				this->_capacity++;
				this->_data = _alloc.allocate(this->_capacity);

				for (size_type i = 0; i < this->_size; i++) {
					_alloc.construct(&this->_data[i], tmp_data[i]);
					_alloc.destroy(tmp_data[i]);
				}

				_alloc.construct(&this->_data[this->_size], val);
				this->_size++;

				_alloc.deallocate(tmp_data, this->_capacity - 1);
			}
			else {
				_alloc.construct(&this->_data[this->_size], val);
				this->_size++;
			}
		}

		void swap(vector &x)
		{
			if (*this == x)
				return;

			value_type *tmp_data = this->_data;
			allocator_type tmp_alloc = this->_alloc;
			size_type tmp_size = this->_size;
			size_type tmp_capacity = this->_capacity;

			this->_data = x._data;
			this->_alloc = x._alloc;
			this->_size = x._size;
			this->_capacity = x._capacity;

			x._data = tmp_data;
			x._alloc = tmp_alloc;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
		}

		void clear(void)
		{
			for (size_type n = 0; n < _size; n++)
				_alloc.destroy(&_data[n]);
			_size = 0;
		}

		/* Allocator */

		/**
		 * @brief Returns a copy of the allocator object associated with the vector.
		 * @return The allocator.
		 **/
		allocator_type get_allocator(void) const { return _alloc; }

	private:
	/* Attributes */
		allocator_type _alloc;
		value_type *_data;
		size_type _size;
		size_type _capacity;

	/* Private members functions */

		/**
		 * @brief Free all memory usage of the vector
		 */
		void destroy(void)
		{
			this->clear();
			_alloc.deallocate(_data, _capacity);
			this->_size = 0;
			this->_capacity = 0;
		}
	};

} /* namespace ft */

#endif /* VECTOR_HPP */