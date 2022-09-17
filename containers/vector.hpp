/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:26:07 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/07 13:58:59 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "iterator.hpp"
#include "traits.hpp"
#include "utils.hpp"

namespace ft
{

	/**
	 * @brief This container store elements and auto manage memory usage
	 *
	 * @tparam T The type of the elements stores in the vector
	 * @tparam Alloc The allocator type, set by default to std::allocator<T>
	 */
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{

	public:
		/* Member types */
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef ft::random_access_iterator<pointer>			iterator;
		typedef ft::random_access_iterator<const_pointer>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		/* Attributes */
		allocator_type	_alloc;
		pointer			_data;
		size_type		_size;
		size_type		_capacity;

	public:
		/* Member functions */

		/**
		 * @brief Default constructor
		 *
		 * @param alloc The allocator to use
		 */
		explicit vector(const allocator_type &alloc = allocator_type())
		: _alloc(alloc),
		  _data(NULL),
		  _size(0),
		  _capacity(0)
		{ }

		/**
		 * @brief Size constructor
		 *
		 * @param n The size of the vector
		 * @param val The value to fill the vector with
		 * @param alloc The allocator to use
		 */
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
		: _alloc(alloc),
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
		template <class InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			   InputIterator last,
			   const allocator_type &alloc = allocator_type())
		: _alloc(alloc),
		  _size(0),
		  _capacity(0)
		{
			try
			{
				for (; first != last; first++)
					push_back(*first);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * @brief Copy constructor
		 *
		 * @param x Vector to copy
		 */
		vector(const vector& x) : _data(NULL)
		{ *this = x; }

		/**
		 * @brief Destroy the vector object
		 */
		~vector(void)
		{ this->_destroy(); }

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

				if (this->_capacity)
					this->_data = this->_alloc.allocate(this->_capacity);
				for (size_type n = 0; n < this->_size; n++)
					this->_alloc.construct(&this->_data[n], rhs[n]);
			}
			return *this;
		}

		/* Iterators */

		/**
		 * @brief Return an iterator to the beginning of the vector
		 *
		 * @return An iterator to the beginning of the vector
		 */
		iterator begin(void)
		{ return iterator(this->_data); }

		/**
		 * @brief Return a const iterator to the beginning of the vector
		 *
		 * @return A const iterator to the beginning of the vector
		 */
		const_iterator begin(void) const
		{ return const_iterator(this->_data); }

		/**
		 * @brief Return an iterator to the end of the vector
		 *
		 * @return An iterator to the end of the vector
		 */
		iterator end(void)
		{ return iterator(this->_data + this->_size); }

		/**
		 * @brief Return a const iterator to the end of the vector
		 *
		 * @return A const iterator to the end of the vector
		 */
		const_iterator end(void) const
		{ return const_iterator(this->_data + this->_size); }

		/**
		 * @brief Return a reverse iterator to the beginning of the vector
		 *
		 * @return A reverse iterator to the beginning of the vector
		 */
		reverse_iterator rbegin(void)
		{ return reverse_iterator(end()); }

		/**
		 * @brief Return a const reverse iterator to the beginning of the vector
		 *
		 * @return A const reverse iterator to the beginning of the vector
		 */
		const_reverse_iterator rbegin(void) const
		{ return const_reverse_iterator(end()); }

		/**
		 * @brief Return a reverse iterator to the end of the vector
		 *
		 * @return A reverse iterator to the end of the vector
		 */
		reverse_iterator rend(void)
		{ return reverse_iterator(begin()); }

		/**
		 * @brief Return a const reverse iterator to the end of the vector
		 *
		 * @return A const reverse iterator to the end of the vector
		 */
		const_reverse_iterator rend(void) const
		{ return const_reverse_iterator(begin()); }

		/* Capacity */

		/**
		 * @brief Returns the number of element in the vector
		 *
		 * @return The number of elements in the container.
		 **/
		size_type size(void) const
		{ return this->_size; }

		/**
		 * @brief Returns the maximum number of elements that the vector can hold.
		 *
		 * @return The maximum number of elements a vector container can hold as content.
		 **/
		size_type max_size(void) const
		{ return this->_alloc.max_size(); }

		/**
		 * @brief Resizes the container so that it contains n elements.
		 *
		 * @param n The new size of the container.
		 * @param val The value to fill the new elements with (default to value-initialized).;
		 */
		void resize(size_type n, value_type val = value_type())
		{
			if (n > max_size())
				throw std::length_error("vector::resize");

			if (n < this->_size)
			{
				for (size_type i = n; i < size(); ++i)
					this->_alloc.destroy(&this->_data[i]);
			}
			else if (n > size())
			{
				if (n > this->_capacity)
				{
					pointer tmp_data = this->_data;
					size_type tmp_capacity = this->_capacity;

					this->_capacity = (n > this->_capacity * 2) ? n : this->_capacity * 2;
					this->_data = this->_alloc.allocate(this->_capacity);

					for (size_type i = 0; i < size(); i++)
					{
						this->_alloc.construct(&this->_data[i], tmp_data[i]);
						this->_alloc.destroy(&tmp_data[i]);
					}
					this->_alloc.deallocate(tmp_data, tmp_capacity);

					for (size_type i = size(); i < this->_capacity; i++)
						this->_alloc.construct(&this->_data[i], val);
				}
				else
				{
					for (size_type i = size(); i < n; i++)
						this->_alloc.construct(&this->_data[i], val);
				}
			}
			this->_size = n;
		}

		/**
		 * @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		 *
		 * @return The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
		 **/
		size_type capacity(void) const
		{ return this->_capacity; }

		/**
		 * @brief Returns whether the vector is empty (i.e. whether its size is 0).
		 *
		 * @return true if the vector is empty, false otherwise.
		 **/
		bool empty(void) const
		{ return this->_size == 0; }

		/**
		 * @brief Requests that the vector capacity be at least enough to contain n elements.
		 *
		 * @param n The minimum number of elements the vector should be able to hold.
		 */
		void reserve(size_type __n)
		{
			if (__n > max_size())
				throw std::length_error("vector::reserve");

			if (__n > capacity())
			{
				pointer tmp_data = this->_data;

				this->_data = this->_alloc.allocate(__n);
				for (size_type i = 0; i < size(); ++i)
				{
					this->_alloc.construct(this->_data + i, tmp_data[i]);
					this->_alloc.destroy(tmp_data + i);
				}
				if (capacity())
					this->_alloc.deallocate(tmp_data, capacity());

				this->_capacity = __n;
			}
		}

		/* Element access */

		/**
		 * @brief Returns a reference to the element at position n in the vector container.
		 *
		 * @param n The position of the element to return.
		 * @return A reference to the element at position n in the vector container.
		 **/
		reference operator[](size_type n)
		{ return this->_data[n]; }

		/**
		 * @brief Returns a const reference to the element at position n in the vector container.
		 *
		 * @param n The position of the element to return.
		 * @return A const reference to the element at position n in the vector container.
		 **/
		const_reference operator[](size_type n) const
		{ return this->_data[n]; }

		/**
		 * @brief Returns a reference to the element at position n in the vector container.
		 *
		 * @param n The position of the element to return.
		 * @return A reference to the element at position n in the vector container.
		 **/
		reference at(size_type n)
		{
			if (n >= size())
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
		reference front(void)
		{ return *this->_data; }

		/**
		 * @brief Returns a const reference to the first element in the vector container.
		 *
		 * @return A const reference to the first element in the vector container.
		 **/
		const_reference front(void) const
		{ return *this->_data; }

		/**
		 * @brief Returns a reference to the last element in the vector container.
		 *
		 * @return A reference to the last element in the vector container.
		 **/
		reference back(void)
		{ return *(this->_data + this->_size - 1); }

		/**
		 * @brief Returns a const reference to the last element in the vector container.
		 *
		 * @return A const reference to the last element in the vector container.
		 **/
		const_reference back(void) const
		{ return *(this->_data + this->_size - 1); }

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
		void assign(
			typename ft::enable_if<
			!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
		{
			const size_type __len = std::distance(first, last);

			if (__len > capacity())
			{
				pointer __tmp;
				__tmp = this->_alloc.allocate(__len);
				for (size_type i = 0; first != last; ++i, ++first)
					this->_alloc.construct(__tmp + i, *first);
				this->_destroy();

				this->_data = __tmp;
				this->_size = __len;
				this->_capacity = __len;
			}
			else
			{
				for (size_type i = 0; i < size(); ++i)
					this->_alloc.destroy(this->_data + i);
				for (size_type i = 0; first != last; ++i, ++first)
					this->_alloc.construct(this->_data + i, *first);
				this->_size = __len;
			}
		}

		/**
		 * @brief Assigns new contents to the vector, replacing its current contents
		 * and modifying its size and capacity accordingly.
		 *
		 * @param n The new size of the vector.
		 * @param val The value to fill the vector with.
		 */
		void assign(size_type __len, const value_type &val)
		{
			if (__len > capacity())
			{
				pointer __tmp = this->_data;

				__tmp = this->_alloc.allocate(__len);
				for (size_type i = 0; i < __len; ++i)
					this->_alloc.construct(__tmp + i, val);
				this->_destroy();

				this->_data = __tmp;
				this->_size = __len;
				this->_capacity = __len;
			}
			else
			{
				for (size_type i = 0; i < size(); ++i)
					this->_alloc.destroy(this->_data + i);
				for (size_type i = 0; i < __len; i++)
					this->_alloc.construct(this->_data + i, val);
				this->_size = __len;
			}
		}

		/**
		 * @brief Insert new elements at the end of the vector,
		 * increasing its size accordingly.
		 *
		 * @param val The value to fill the vector with.
		 */
		void push_back(const value_type& val)
		{
			if (size() + 1 > capacity())
				reserve(capacity() ? capacity() * 2 : 1);

			this->_alloc.construct(this->_data + this->_size++, val);
		}

		/**
		 * @brief Removes the last element in the vector, effectively reducing its size by one.
		 */
		void pop_back(void)
		{ this->_alloc.destroy(this->_data + --this->_size); }

		/**
		 * @brief The vector is extended by inserting new elements before the element at the specified position,
		 * effectively increasing the container size by the number of elements inserted.
		 *
		 * @param position Position in the vector where the new elements are inserted.
		 * @param val Value to be copied (or moved) to the inserted elements.
		 * @return iterator An iterator that points to the first of the newly inserted elements.
		 */
		iterator insert(iterator position, const value_type &val)
		{
			difference_type pos = position - begin();

			if (size() + 1 > capacity())
			{
				const size_type new_capacity = capacity() ? capacity() * 2 : 1;

				pointer __start = this->_alloc.allocate(new_capacity);
				pointer __current = __start;

				for (iterator it = begin(); it != position; ++it, ++__current)
					this->_alloc.construct(__current, *it);
				this->_alloc.construct(__current++, val);
				for (size_type i = position - begin(); i < size(); ++i, ++__current)
					this->_alloc.construct(__current, this->_data[i]);

				const size_type __size = size() + 1;
				this->_destroy();
				this->_data = __start;
				this->_size = __size;
				this->_capacity = new_capacity;
			}
			else
			{
				for (difference_type i = end() - begin() + 1; i > position - begin(); --i)
				{
					this->_alloc.construct(&this->_data[i], this->_data[i - 1]);
					this->_alloc.destroy(&this->_data[i - 1]);
				}
				this->_alloc.construct(&this->_data[position - begin()], val);

				this->_size++;
			}
			return begin() + pos;
		}

		/**
		 * @brief The vector is extended by inserting new elements before the element at the specified position,
		 * increasing the container size by the number of elements inserted.
		 *
		 * @param position Position in the vector where the new elements are inserted.
		 * @param n Number of elements to be inserted.
		 * @param val Value to be copied (or moved) to the inserted elements.
		 * @return iterator An iterator that points to the first of the newly inserted elements.
		 */
		void insert(iterator position, size_type n, const value_type& val)
		{
			if (size() + n > capacity())
			{
				const size_type new_capacity = ft::max(capacity() * 2, size() + n);

				pointer __start = this->_alloc.allocate(new_capacity);
				pointer __current = __start;

				for (iterator it = begin(); it != position; ++it, ++__current)
					this->_alloc.construct(__current, *it);
				for (size_type i = 0; i < n; ++i, ++__current)
					this->_alloc.construct(__current, val);
				for (iterator it = position; it != end(); ++it, ++__current)
					this->_alloc.construct(__current, *it);

				const size_type __size = size() + n;
				this->_destroy();
				this->_data = __start;
				this->_size = __size;
				this->_capacity = new_capacity;
			}
			else
			{
				for (size_type i = end() - begin() + n; i >= position - begin() + n; i--)
				{
					this->_alloc.construct(&this->_data[i], this->_data[i - n]);
					this->_alloc.destroy(&this->_data[i - n]);
				}
				for (size_type i = position - begin(); i < position - begin() + n; i++)
					this->_alloc.construct(&this->_data[i], val);

				this->_size += n;
			}
		}

		/**
		 * @brief The vector is extended by inserting new elements before the element at the specified position,
		 * effectively increasing the container size by the number of elements inserted.
		 *
		 * @param position Position in the vector where the new elements are inserted.
		 * @param first Iterator pointing to the first element to be inserted.
		 * @param last Iterator pointing to the element after the last element to be inserted.
		 * @return iterator An iterator that points to the first of the newly inserted elements.
		 */
		template <class InputIterator>
		void insert(iterator position,
					 typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					 InputIterator last)
		{
			size_type __len = std::distance(first, last);

			if (size() + __len > capacity())
			{
				size_type __new_capacity = ft::max(capacity() * 2, size() + __len);

				pointer __start = this->_alloc.allocate(__new_capacity);
				pointer __current = __start;
				for (iterator it = begin(); it != position; ++it, ++__current)
					this->_alloc.construct(__current, *it);
				for (; first != last; ++first, ++__current)
					this->_alloc.construct(__current, *first);
				for (size_type i = position - begin() + __len; i < size() + __len; ++i, ++__current)
					this->_alloc.construct(__current, this->_data[i - __len]);

				size_type __size = size() + __len;
				this->_destroy();
				this->_data = __start;
				this->_size = __size;
				this->_capacity = __new_capacity;
			}
			else
			{
				for (size_type i = end() - begin() + __len; i > position - begin() + __len; i--) {
					this->_alloc.construct(this->_data + i, this->_data[i - __len]);
					this->_alloc.destroy(&this->_data[i - __len]);
				}
				for (size_type i = position - begin(); first != last; i++) {
					this->_alloc.construct(this->_data + i, *first);
					first++;
				}

				this->_size += __len;
			}
		}

		/**
		 * @brief Removes one element from the vector.
		 * 
		 * @param position Position of the element to be removed.
		 * @return iterator An iterator that points to the next element in the vector.
		 */
		iterator erase(iterator position)
		{
			this->_alloc.destroy(&this->_data[position - begin()]);
			for (size_type i = position - begin(); i + 1 < size(); i++) {
				this->_alloc.construct(&this->_data[i], this->_data[i + 1]);
				this->_alloc.destroy(&this->_data[i + 1]);
			}

			this->_size--;
			return position;
		}

		/**
		 * @brief Removes a range of elements from the vector.
		 * 
		 * @param first Iterator pointing to the first element to be removed.
		 * @param last Iterator pointing to the element after the last element to be removed.
		 * @return iterator An iterator that points to the next element in the vector.
		 */
		iterator erase(iterator first, iterator last)
		{
			size_type n = last - first;
			for (difference_type i = first - begin(); i < last - begin(); i++) {
				this->_alloc.destroy(&this->_data[i]);
				if (i + n < this->_size) {
					this->_alloc.construct(&this->_data[i], this->_data[i + n]);
					this->_alloc.destroy(&this->_data[i + n]);
				}
			}
			for (difference_type i = last - begin(); i + n < this->_size; i++) {
				this->_alloc.construct(&this->_data[i], this->_data[i + n]);
				this->_alloc.destroy(&this->_data[i + n]);
			}

			this->_size -= n;
			return first;
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
			for (size_type n = 0; n < size(); n++)
				this->_alloc.destroy(this->_data + n);
			this->_size = 0;
		}

		/* Allocator */

		/**
		 * @brief Returns a copy of the allocator object associated with the vector.
		 *
		 * @return The allocator.
		 **/
		allocator_type get_allocator(void) const
		{ return this->_alloc; }

	private:

		/**
		 * @brief Free all memory usage of the vector
		 */
		void _destroy(void)
		{
			this->clear();
			if (capacity())
				this->_alloc.deallocate(this->_data, capacity());
			this->_capacity = 0;
			this->_data = NULL;
		}
	};

	/* Non-member function overloads */

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		typename ft::vector<T, Alloc>::const_iterator it = lhs.begin(), it2 = rhs.begin();
		while (it != lhs.end())
		{
			if (*it != *it2)
				return false;
			it++;
			it2++;
		}

		return true;
	}

	template <class T, class Alloc>
	inline bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template<class T, class Alloc>
	inline bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template<class T, class Alloc>
	inline bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return !(rhs < lhs); }

	template<class T, class Alloc>
	inline bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return rhs < lhs; }

	template<class T, class Alloc>
	inline bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{ return !(lhs < rhs); }

	template <class T, class Alloc>
	inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{ x.swap(y); }

} /* namespace ft */

#endif /* VECTOR_HPP */