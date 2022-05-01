#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "traits.hpp"

namespace ft
{

	/**
	 * @brief Iterator class for 
	 *
	 * @tparam T The type of the iterator
	 */
	template <typename _Iterator>
	struct random_access_iterator
	{
	protected:

		_Iterator _ptr;

		typedef iterator_traits<_Iterator>			traits_type;

	public:
		typedef _Iterator								iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::reference			reference;
		typedef typename traits_type::pointer			pointer;

		/**
		 * @brief Default constructor
		 */
		random_access_iterator(void) : _ptr(_Iterator()){};

		/**
		 * @brief Assignment operator
		 *
		 * @param ptr The pointer to assign
		 */
		explicit random_access_iterator(const _Iterator& _i) : _ptr(_i){};

		/**
		 * @brief Dereference operator
		 *
		 * @return _Iterator& The value
		 */
		reference operator*() const
		{ return *_ptr; }

		/**
		 * @brief Arrow operator
		 *
		 * @return _Iterator* The pointer
		 */
		pointer operator->() const
		{ return _ptr; }

		/**
		 * @brief Pre-increment operator
		 *
		 * @return iterator& The iterator
		 */
		random_access_iterator& operator++()
		{
			++_ptr;
			return *this;
		}

		/**
		 * @brief Post-increment operator
		 *
		 * @return iterator& The iterator
		 */
		random_access_iterator operator++(int)
		{ return random_access_iterator(_ptr++); }

		/**
		 * @brief Pre-decrement operator
		 *
		 * @return iterator& The iterator
		 */
		random_access_iterator& operator--()
		{
			--_ptr;
			return *this;
		}

		/**
		 * @brief Post-decrement operator
		 *
		 * @return iterator& The iterator
		 */
		random_access_iterator operator--(int)
		{ return random_access_iterator(_ptr--); }

		/**
		 * @brief Dereference operator
		 *
		 * @param i The index
		 * @return _Iterator& The value at the index
		 */
		reference operator[](difference_type i) const
		{ return _ptr[i]; }

		/**
		 * @brief Give a reference to this random access iterator
		 * where the element pointed is at the actual pointer memory
		 * plus "n".
		 *
		 * @param n The number of elements to add
		 * @return random_access_iterator& The iterator
		 */
		random_access_iterator& operator+=(difference_type n)
		{
			_ptr += n;
			return *this;
		}

		/**
		 * @brief Give a iterator where the element
		 * is pointed at this + "n" in memory.
		 *
		 * @param n The number of elements to add
		 * @return iterator& The iterator
		 */
		random_access_iterator operator+(difference_type n) const
		{ return random_access_iterator(_ptr + n); }

		/**
		 * @brief Give a reference to this random access iterator
		 * where the element pointed is at the actual pointer memory
		 * minus "n".
		 *
		 * @param n The number of elements to subtract
		 * @return random_access_iterator& The iterator
		 */
		random_access_iterator& operator-=(difference_type n)
		{
			_ptr -= n;
			return *this;
		}

		/**
		 * @brief Give a iterator where the element
		 * is pointed at this - "n" in memory.
		 *
		 * @param n The number of elements to subtract
		 * @return random_access_iterator The iterator
		 */
		random_access_iterator operator-(difference_type n) const
		{
			return random_access_iterator(_ptr - n);
		}

		const _Iterator& base() const
		{ return _ptr; }
	};

	template <typename _IteratorL, typename _IteratorR>
	inline bool operator==(const random_access_iterator<_IteratorL>& lhs,
						   const random_access_iterator<_IteratorR>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename _Iterator>
	inline bool operator==(const random_access_iterator<_Iterator>& lhs,
						   const random_access_iterator<_Iterator>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool operator!=(const random_access_iterator<_IteratorL>& lhs,
						   const random_access_iterator<_IteratorR>& rhs)
	{ return lhs.base() != rhs.base(); }

	template <typename _Iterator>
	inline bool operator!=(const random_access_iterator<_Iterator>& lhs,
						   const random_access_iterator<_Iterator>& rhs)
	{ return lhs.base() != rhs.base(); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool operator<(const random_access_iterator<_IteratorL>& lhs,
						   const random_access_iterator<_IteratorR>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename _Iterator>
	inline bool operator<(const random_access_iterator<_Iterator>& lhs,
						   const random_access_iterator<_Iterator>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool operator>(const random_access_iterator<_IteratorL>& lhs,
						   const random_access_iterator<_IteratorR>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <typename _Iterator>
	inline bool operator>(const random_access_iterator<_Iterator>& lhs,
						   const random_access_iterator<_Iterator>& rhs)
	{ return lhs.base() > rhs.base(); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool operator<=(const random_access_iterator<_IteratorL>& lhs,
						   const random_access_iterator<_IteratorR>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <typename _Iterator>
	inline bool operator<=(const random_access_iterator<_Iterator>& lhs,
						   const random_access_iterator<_Iterator>& rhs)
	{ return lhs.base() <= rhs.base(); }

	template <typename _IteratorL, typename _IteratorR>
	inline bool operator>=(const random_access_iterator<_IteratorL>& lhs,
						   const random_access_iterator<_IteratorR>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template <typename _Iterator>
	inline bool operator>=(const random_access_iterator<_Iterator>& lhs,
						   const random_access_iterator<_Iterator>& rhs)
	{ return lhs.base() >= rhs.base(); }

	template<typename _IteratorL, typename _IteratorR> 
	inline typename random_access_iterator<_IteratorL>::difference_type
	operator-(const random_access_iterator<_IteratorL>& lhs,
			  const random_access_iterator<_IteratorR>& rhs)
	{ return lhs.base() - rhs.base(); }

	template<typename _Iterator> 
	inline typename random_access_iterator<_Iterator>::difference_type
	operator-(const random_access_iterator<_Iterator>& lhs,
			  const random_access_iterator<_Iterator>& rhs)
	{ return lhs.base() - rhs.base(); }

	template<typename _Iterator>
	inline random_access_iterator<_Iterator>
	operator+(typename random_access_iterator<_Iterator>::difference_type n,
			  const random_access_iterator<_Iterator>& i)
	{ return random_access_iterator<_Iterator>(i.base() + n); }





	/* Reverse iterator */

	template <typename Iterator>
	class reverse_iterator
	{
	protected:
		Iterator current;

		typedef iterator_traits<Iterator>				traits_type;

	public:
		typedef Iterator								iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;

		reverse_iterator() : current() { }

		explicit reverse_iterator(iterator_type x) : current(x) { }

		reverse_iterator(const reverse_iterator& x) : current(x.current) { }

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& x) : current(x.base()) { }

		iterator_type base() const
		{ return current; }

		reference operator*() const
		{
			iterator_type tmp = current;
			return *--tmp;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reverse_iterator& operator++()
		{
			--current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			iterator_type tmp = *this;
			--current;
			return tmp;
		}

		reverse_iterator& operator--()
		{
			++current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			iterator_type tmp = *this;
			--current;
			return tmp;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(current - n);
		}

		reverse_iterator& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current + n);
		}

		reverse_iterator& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference operator[](difference_type n) const
		{ return *(*this + n); }
	};

	template <typename Iterator>
	inline bool operator==(const reverse_iterator<Iterator>& lhs,
						   const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename Iterator>
	inline bool operator<(const reverse_iterator<Iterator>& lhs,
						  const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename Iterator>
	inline bool operator!=(const reverse_iterator<Iterator>& lhs,
						   const reverse_iterator<Iterator>& rhs)
	{ return !(lhs == rhs); }

	template <typename Iterator>
	inline bool operator>(const reverse_iterator<Iterator>& lhs,
						  const reverse_iterator<Iterator>& rhs)
	{ return lhs < rhs; }

	template <typename Iterator>
	inline bool operator<=(const reverse_iterator<Iterator>& lhs,
						   const reverse_iterator<Iterator>& rhs)
	{ return !(lhs < rhs); }

	template <typename Iterator>
	inline bool operator>=(const reverse_iterator<Iterator>& lhs,
						   const reverse_iterator<Iterator>& rhs)
	{ return !(lhs < rhs); }

	// Comparison of reverse_iterator to const reverse_iterator.
	template <typename IteratorL, typename IteratorR>
	inline bool operator==(const reverse_iterator<IteratorL>& lhs,
						   const reverse_iterator<IteratorR>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename IteratorL, typename IteratorR>
	inline bool operator<(const reverse_iterator<IteratorL>& lhs,
						  const reverse_iterator<IteratorR>& rhs)
	{ return lhs.base() < rhs.base(); }

	template <typename IteratorL, typename IteratorR>
	inline bool operator!=(const reverse_iterator<IteratorL>& lhs,
						   const reverse_iterator<IteratorR>& rhs)
	{ return !(lhs == rhs); }

	template <typename IteratorL, typename IteratorR>
	inline bool operator>(const reverse_iterator<IteratorL>& lhs,
						  const reverse_iterator<IteratorR>& rhs)
	{ return lhs < rhs; }

	template <typename IteratorL, typename IteratorR>
	inline bool operator<=(const reverse_iterator<IteratorL>& lhs,
						   const reverse_iterator<IteratorR>& rhs)
	{ return !(lhs < rhs); }

	template <typename IteratorL, typename IteratorR>
	inline bool operator>=(const reverse_iterator<IteratorL>& lhs,
						   const reverse_iterator<IteratorR>& rhs)
	{ return !(lhs < rhs); }

	template<typename Iterator>
	inline typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs,
			  const reverse_iterator<Iterator>& rhs)
	{ return rhs.base() - lhs.base(); }

	template<typename IteratorL, typename IteratorR>
	inline typename reverse_iterator<IteratorL>::difference_type
	operator-(const reverse_iterator<IteratorL>& lhs,
			  const reverse_iterator<IteratorR>& rhs)
	{ return rhs.base() - lhs.base(); }

	template<typename Iterator>
	inline reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n,
			  const reverse_iterator<Iterator>& x)
	{ return reverse_iterator<Iterator> (x.base() - n); }

}

#endif /* ITERATOR_HPP */