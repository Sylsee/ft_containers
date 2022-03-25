/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:26:07 by spoliart          #+#    #+#             */
/*   Updated: 2022/03/25 19:51:53 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

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
			explicit vector (const allocator_type& alloc = allocator_type()) :
				_alloc(alloc),
				_size(0),
				_capacity(0),
				_data(NULL)
			{}

			explicit vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) :
				_alloc(alloc),
				_size(n),
				_capacity(n)
			{
				_data = allocator_type().allocate(n);
				while (n--)
					allocator_type().construct(_data[n], val);
			}

//			template <class InputIterator>
//			vector (InputIterator first, InputIterator last,
//					const allocator_type& alloc = allocator_type())
//			{}

			vector (const vector& x)
			{
				*this = x;
			}

			~vector()
			{
				this->clear();
			}

			vector& operator= (const vector& rhs)
			{
				if (this != &rhs)
				{
					this->clear();
					_alloc = rhs._alloc;
					_size = rhs._size;
					_capacity = rhs._capacity;

				}
				return *this;
			}

		/* Iterators */

		/* Capacity */

			/**
			 * @brief Returns the number of element in the vector
			 * @return The number of elements in the container.
			**/
			size_type	size( void ) const { return _size; }

			/**
			 * @brief Returns the maximum number of elements that the vector can hold.
			 * @return The maximum number of elements a vector container can hold as content.
			**/
			size_type	max_size( void ) const { return allocator_type().max_size(); }

			/**
			 * @brief Returns the 
			 * @return 
			**/
			size_type	capacity( void ) const { return _capacity; }
		/* Element access */

		/* Modifiers */

			template < class InputIterator >
			void	assign( InputIterator first, InputIterator last )
			{
				if (last - first > max_size())
					throw std::length_error("cannot create ft::vector larger than max_size()");
			}

			void	assign( size_type n, const value_type &val)
			{
				if (n > max_size() || )
					throw std::length_error("cannot create ft::vector larger than max_size()");
			}

			void	clear( void )
			{
				for (int n = 0; n < _size; n++)
					allocator_type().destroy(_data[n]);
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

	};

	/**
	 * @brief Overload of swap (vector).
	 * The content of container are swaped.
	 *
	 * @param x,y the containers to swap.
	**/
	template < class T, class Alloc >
	void	swap( vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }

} /* namespace ft */


#endif /* VECTOR_HPP */