/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:18:16 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/06 17:39:35 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sstream>
#include <traits.hpp>

namespace ft
{

	template < typename T >
	std::string to_string(T n)
	{
		std::ostringstream ss;
		ss << n;
		return ss.str();
	}

	/**
	 * @brief Swap two elements
	 *
	 * @param a The first element
	 * @param b The second element
	 */
	template < typename T >
	void swap(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	/**
	 * @brief Returns the largest of a and b.
	 *
	 * @param a The first element
	 * @param b The second element
	 * @return The max of a and b
	 */
	template<typename T>
	T max(T a, T b)
	{ return (a > b) ? a : b; }

	/* Equal */

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	/* Lexicographical_compare */

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare
		(typename ft::enable_if<!ft::is_integral<InputIterator1>::value, InputIterator1>::type first1, InputIterator1 last1,
		 typename ft::enable_if<!ft::is_integral<InputIterator2>::value, InputIterator2>::type first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare
		(typename ft::enable_if<!ft::is_integral<InputIterator1>::value, InputIterator1>::type first1, InputIterator1 last1,
		 typename ft::enable_if<!ft::is_integral<InputIterator2>::value, InputIterator2>::type first2, InputIterator2 last2,
		 Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	/* Pair */

	template <class T1, class T2>
	struct pair
	{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second()
		{}

		template <class U, class V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second)
		{}

		pair(const first_type& a, const second_type& b) : first(a), second(b)
		{}

		pair& operator=(const pair& pr)
		{
			if (this != &pr)
			{
				this->first = pr.first;
				this->second = pr.second;
			}
			return *this;
		}

	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ft::pair<T1, T2>(x, y);
	}

}

#endif /* UTILS_HPP */
