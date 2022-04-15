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
		 * @brief Default constructor
		 *
		 * @param alloc The allocator to use
		 */
		explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc),
																		  _size(0),
																		  _capacity(0),
																		  _data(NULL)
		{}

		/**
		 * @brief Size constructor
		 *
		 * @param n The size of the vector
		 * @param val The value to fill the vector with
		 * @param alloc The allocator to use
		 */
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) : _alloc(alloc),
																		  _size(n),
																		  _capacity(n)
		{
			this->_data = this->_alloc.allocate(n);
			while (n--)
				this->_alloc.construct(&this->_data[n], val);
		}

		/**
		 * @brief Range constructor
		 *
		 * @param first The first element of the range to copy
		 * @param last The last element of the range to copy
		 * @param alloc The allocator to use
		 */
		// template <class InputIterator>
			// vector(InputIterator first, InputIterator last,
				//    const allocator_type &alloc = allocator_type()) : _alloc(alloc)
		// {
			// if (static_cast<size_type>(last - first) > this->max_size())
				// throw std::length_error("cannot create ft::vector larger than max_size()");
// 
			// this->_size = last - first;
			// this->_capacity = this->_size;
			// this->_data = this->_alloc.allocate(this->_capacity);
			// for (InputIterator it = first; it != last; it++)
				// this->_alloc.construct(&this->_data[it - first], it);
		// }

		/**
		 * @brief Copy constructor
		 *
		 * @param x Vector to copy
		 */
		vector(const vector &x) : _data(NULL)
		{
			*this = x;
		}

		/**
		 * @brief Destroy the vector object
		 */
		~vector(void)
		{
			this->_destroy();
		}

		/**
		 * @brief Assignement operator
		 *
		 * @param rhs Vector to assign
		 * @return The vector after assignement
		 */
		vector &operator=(const vector &rhs)
		{
			if (this != &rhs)
			{
				if (this->_data)
					this->_destroy();

				this->_alloc = rhs._alloc;
				this->_size = rhs._size;
				this->_capacity = rhs._size;

				this->_data = this->_alloc.allocate(this->_capacity);
				for (size_type n = 0; n < this->_size; n++)
					this->_alloc.construct(&this->_data[n], rhs[n]);
			}
			return *this;
		}

		/* Iterators */

		/* Capacity */

		/**
		 * @brief Returns the number of element in the vector
		 *
		 * @return The number of elements in the container.
		 **/
		size_type size(void) const { return this->_size; }

		/**
		 * @brief Returns the maximum number of elements that the vector can hold.
		 *
		 * @return The maximum number of elements a vector container can hold as content.
		 **/
		size_type max_size(void) const { return this->_alloc.max_size(); }

		/**
		 * @brief Resizes the container so that it contains n elements.
		 * 
		 * @param n The new size of the container.
		 * @param val The value to fill the new elements with (default to value-initialized).;
		 */
		void resize (size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw std::length_error("vector::resize");

			if (n < this->_size)
			{
				for (size_type i = n; i < this->_size; i++)
					this->_alloc.destroy(&this->_data[i]);
			}
			else if (n > this->_size)
			{
				if (n > this->_capacity)
				{
					pointer tmp_data = this->_data;
					size_type tmp_capacity = this->_capacity;

					this->_capacity = (n > this->_capacity * 2) ? n : this->_capacity * 2;
					this->_data = this->_alloc.allocate(this->_capacity);

					for (size_type i = 0; i < this->_size; i++) {
						this->_alloc.construct(&this->_data[i], tmp_data[i]);
						this->_alloc.destroy(&tmp_data[i]);
					}
					this->_alloc.deallocate(tmp_data, tmp_capacity);

					for (size_type i = this->_size; i < this->_capacity; i++)
						this->_alloc.construct(&this->_data[i], val);
				}
				else
				{
					for (size_type i = this->_size; i < n; i++)
						this->_alloc.construct(&this->_data[i], val);
				}
				this->_size = n;
			}
		}

		/**
		 * @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		 *
		 * @return The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
		 **/
		size_type capacity(void) const { return this->_capacity; }

		/**
		 * @brief Returns whether the vector is empty (i.e. whether its size is 0).
		 *
		 * @return true if the vector is empty, false otherwise.
		 **/
		bool empty(void) const { return (this->_size == 0); }

		/**
		 * @brief Requests that the vector capacity be at least enough to contain n elements.
		 *
		 * @param n The minimum number of elements the vector should be able to hold.
		 */
		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("vector::reserve");

			else if (n > this->capacity())
			{
				pointer tmp_data = this->_data;

				this->_data = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(&this->_data[i], tmp_data[i]);
					this->_alloc.destroy(&tmp_data[i]);
				}
				this->_alloc.deallocate(tmp_data, this->_capacity);

				this->_capacity = n;
			}
		}

		/* Element access */

		/**
		 * @brief Returns a reference to the element at position n in the vector container.
		 *
		 * @param n The position of the element to return.
		 * @return A reference to the element at position n in the vector container.
		 **/
		reference operator[](size_type n) { return this->_data[n]; }

		/**
		 * @brief Returns a const reference to the element at position n in the vector container.
		 *
		 * @param n The position of the element to return.
		 * @return A const reference to the element at position n in the vector container.
		 **/
		const_reference operator[](size_type n) const { return this->_data[n]; }

		/**
		 * @brief Returns a reference to the element at position n in the vector container.
		 *
		 * @param n The position of the element to return.
		 * @return A reference to the element at position n in the vector container.
		 **/
		reference at(size_type n)
		{
			if (n >= this->_size)
				throw std::out_of_range("vector::at: n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(this->_size) + ")");
			return this->_data[n];
		}

		/**
		 * @brief Returns a const reference to the element at position n in the vector container.
		 *
		 * @param n The position of the element to return.
		 * @return A const reference to the element at position n in the vector container.
		 **/
		const_reference at(size_type n) const
		{
			if (n >= this->_size)
				throw std::out_of_range("vector::at: n (which is " + ft::to_string(n) + ") >= this->size() (which is " + ft::to_string(this->_size) + ")");
			return this->_data[n];
		}

		/**
		 * @brief Returns a reference to the first element in the vector container.
		 *
		 * @return A reference to the first element in the vector container.
		 **/
		reference front(void) { return *this->_data; }

		/**
		 * @brief Returns a const reference to the first element in the vector container.
		 *
		 * @return A const reference to the first element in the vector container.
		 **/
		const_reference front(void) const { return *this->_data; }

		/**
		 * @brief Returns a reference to the last element in the vector container.
		 *
		 * @return A reference to the last element in the vector container.
		 **/
		reference back(void) { return this->_data[this->_size - 1]; }

		/**
		 * @brief Returns a const reference to the last element in the vector container.
		 *
		 * @return A const reference to the last element in the vector container.
		 **/
		const_reference back(void) const { return this->_data[this->_size - 1]; }

		/* Modifiers */

		/**
		 * @brief Assigns new contents to the vector, replacing its current contents
		 * and modifying its size and capacity accordingly.
		 *
		 * @tparam InputIterator The type of the iterator used to read the input data.
		 * @param first The iterator to the first element in the range of elements to be copied.
		 * @param last The iterator to the lasr element in the range of elements to be copied.
		 */
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			if (last - first > this->max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");

			if (last - first > this->_capacity)
			{
				pointer tmp_data = this->_data;

				this->_data = this->_alloc.allocate(last - first);
				for (size_type i = 0; i < this->_size; i++) {
					this->_alloc.construct(&this->_data[i], *(first++));
					this->_alloc.destroy(&tmp_data[i]);
				}
				this->_alloc.deallocate(tmp_data, this->_capacity);
				for (InputIterator it = first; it != last; it++)
					this->_alloc.construct(&this->_data[it - first], *it);

				this->_size = last - first;
				this->_capacity = last - first;
			}
			else
			{
				for (InputIterator it = first; it != last; it++) {
					this->_alloc.destroy(&this->_data[it - first]);
					this->_alloc.construct(&this->_data[it - first], *it);
				}
				this->_size = last - first;
			}
		}

		/**
		 * @brief Assigns new contents to the vector, replacing its current contents
		 * and modifying its size and capacity accordingly.
		 *
		 * @param n The new size of the vector.
		 * @param val The value to fill the vector with.
		 */
		void assign(size_type n, const value_type &val)
		{
			if (n > this->max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");

			if (n > this->_capacity)
			{
				pointer tmp_data = this->_data;

				this->_data = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.destroy(&tmp_data[i]);
					this->_alloc.construct(&this->_data[i], val);
				}
				this->_alloc.deallocate(tmp_data, this->_capacity);
				for (size_type i = this->_size; i < n; i++)
					this->_alloc.construct(&this->_data[i], val);

				this->_size = n;
				this->_capacity = n;
			}
			else
			{
				for (size_type i = 0; i < n; i++)
				{
					this->_alloc.destroy(&this->_data[i]);
					this->_alloc.construct(&this->_data[i], val);
				}
				this->_size = n;
			}
		}

		/**
		 * @brief Insert new elements at the end of the vector,
		 * increasing its size accordingly.
		 *
		 * @param val The value to fill the vector with.
		 */
		void push_back(const value_type &val)
		{
			if (this->_size + 1 > this->max_size())
				throw std::length_error("cannot create ft::vector larger than max_size()");

			if (this->_size + 1 > this->_capacity)
				this->reserve(++this->_capacity);

			this->_alloc.construct(&this->_data[this->_size++], val);
		}

		/**
		 * @brief Removes the last element in the vector, reducing its size by one.
		 */
		void pop_back(void)
		{
			if (this->_size != 0)
				this->_alloc.destroy(&this->_data[--this->_size]);
		}

		/**
		 * @brief Swaps the contents of two vectors.
		 *
		 * @param x The vector to swap with.
		 */
		void swap(vector &x)
		{
			if (this == &x)
				return;

			ft::swap(this->_data, x._data);
			ft::swap(this->_size, x._size);
			ft::swap(this->_capacity, x._capacity);
			ft::swap(this->_alloc, x._alloc);
		}

		/**
		 * @brief Clears all elements from the vector.
		 */
		void clear(void)
		{
			for (size_type n = 0; n < this->_size; n++)
				this->_alloc.destroy(&this->_data[n]);
			this->_size = 0;
		}

		/* Allocator */

		/**
		 * @brief Returns a copy of the allocator object associated with the vector.
		 *
		 * @return The allocator.
		 **/
		allocator_type get_allocator(void) const { return this->_alloc; }

	private:
		/* Attributes */
		allocator_type _alloc;
		pointer _data;
		size_type _size;
		size_type _capacity;

		/* Private members functions */

		/**
		 * @brief Free all memory usage of the vector
		 */
		void _destroy(void)
		{
			this->clear();
			this->_alloc.deallocate(this->_data, this->_capacity);
			this->_size = 0;
			this->_capacity = 0;
			this->_data = NULL;
		}

	};

} /* namespace ft */

#endif /* VECTOR_HPP */