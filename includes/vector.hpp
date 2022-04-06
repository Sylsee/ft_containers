/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:26:07 by spoliart          #+#    #+#             */
/*   Updated: 2022/04/06 21:02:54 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "utils.hpp"

namespace ft
{

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{

		public:

		/* Member types */
			typedef T                                            value_type;
			typedef Alloc                                        allocator_type;
			typedef typename allocator_type::reference           reference;
			typedef typename allocator_type::const_reference     const_reference;
			typedef typename allocator_type::pointer             pointer;
			typedef typename allocator_type::const_pointer       const_pointer;
			typedef typename allocator_type::difference_type     difference_type;
			typedef typename allocator_type::size_type           size_type;
//			typedef ft::random_access_iterator<value_type>       iterator;
//			typedef ft::random_access_iterator<const value_type> const_iterator;
//			typedef ft::reverse_iterator<iterator>               reverse_iterator;
//			typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;

	/* MEMBER FUNCTIONS */
			explicit vector(const allocator_type& alloc = allocator_type()) :
				_alloc(alloc),
				_size(0),
				_capacity(0),
				_data(NULL)
			{}

			explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) :
				_alloc(alloc),
				_size(n),
				_capacity(n)
			{
				_data = allocator_type().allocate(n);
				while (n--)
					allocator_type().construct(&_data[n], val);
			}

//			template <class InputIterator>
//			vector (InputIterator first, InputIterator last,
//					const allocator_type& alloc = allocator_type())
//			{}

			vector(const vector& x)
			{
				*this = x;
			}

			~vector(void)
			{
				this->destroy();
			}

			vector& operator=(const vector& rhs)
			{
				if (this != &rhs)
				{
					this->destroy();
					_alloc = rhs._alloc;
					_size = rhs._size;
					_capacity = rhs._capacity;
					_data = allocator_type().allocate(_capacity);
					for (size_type n = 0; n < _size; n++)
						allocator_type().construct(_data[n], rhs[n]);
				}
				return *this;
			}

		/* Iterators */

		/* Capacity */

			/**
			 * @brief Returns the number of element in the vector
			 * @return The number of elements in the container.
			**/
			size_type	size(void) const { return _size; }

			/**
			 * @brief Returns the maximum number of elements that the vector can hold.
			 * @return The maximum number of elements a vector container can hold as content.
			**/
			size_type	max_size(void) const { return allocator_type().max_size(); }

			/**
			 * @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
			 * @return The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
			**/
			size_type	capacity(void) const { return _capacity; }

			/**
			 * @brief Returns whether the vector is empty (i.e. whether its size is 0).
			 * @return true if the container size is 0, false otherwise.
			**/
			bool	empty(void) const
			{
				return _size == 0;
			}

		/* Element access */

			reference	operator[](size_type n) { return _data[n]; }

			const_reference	operator[](size_type n) const { return _data[n]; }

			reference	at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector::_M_range_check: __n (which is "
							+ ft::to_string(n) + ") >= this->size() (which is "
							+ ft::to_string(_size) + ")");
				return _data[n];
			}

			const_reference	at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector::_M_range_check: __n (which is "
							+ ft::to_string(n) + ") >= this->size() (which is "
							+ ft::to_string(_size) + ")");
				return _data[n];
			}

			reference front(void) { return *_data; }

			const_reference front(void) const { return *_data; }

			reference back(void) { return _data[_size - 1]; }

			const_reference back(void) const { return _data[_size - 1]; }

		/* Modifiers */

			void	swap(vector& x)
			{
				if (*this == x)
					return ;

				value_type		*tmp_data = this->_data;
				allocator_type	tmp_alloc = this->_alloc;
				size_type		tmp_size = this->_size;
				size_type		tmp_capacity = this->_capacity;

				this->_data = x._data;
				this->_alloc = x._alloc;
				this->_size = x._size;
				this->_capacity = x._capacity;

				x._data = tmp_data;
				x._alloc = tmp_alloc;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}

			void	clear(void)
			{
				for (size_type n = 0; n < _size; n++)
					allocator_type().destroy(&_data[n]);
				_size = 0;
			}

		/* Allocator */

			/**
			 * @brief Returns a copy of the allocator object associated with the vector.
			 * @return The allocator.
			**/
			allocator_type	get_allocator( void ) const { return _alloc; }

		private:

		/* Attributes */
			allocator_type	_alloc;
			value_type		*_data;
			size_type		_size;
			size_type		_capacity;

			void	destroy( void )
			{
				this->clear();
				allocator_type().deallocate(_data, _capacity);
			}

	};

} /* namespace ft */


#endif /* VECTOR_HPP */