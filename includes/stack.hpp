/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <sylvio.poliart@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:27:19 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/04 15:31:46 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template<typename _Tp, typename _Sequence = ft::vector<_Tp> >
	class stack
	{

		template<typename _Tp1, typename _Seq1>
		friend bool operator==(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

		template<typename _Tp1, typename _Seq1>
		friend bool operator<(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

	protected:

		_Sequence c;

	public:

		typedef typename _Sequence::size_type		size_type;
		typedef typename _Sequence::reference		reference;
		typedef typename _Sequence::value_type		value_type;
		typedef typename _Sequence::const_reference const_reference;
		typedef _Sequence							container_type;

		explicit stack(const _Sequence& __c = _Sequence())
		: c(__c) { }

		bool empty() const
		{ return c.empty(); }

		size_type size() const
		{ return c.size(); }

		reference top()
		{ return c.back(); }

		const_reference top() const
		{ return c.back(); }

		void push(const value_type& val)
		{ c.push_back(val); }

		void pop()
		{ c.pop_back(); }
	};

	template<typename _Tp1, typename _Seq1>
	inline bool operator==(const stack<_Tp1, _Seq1>& __lhs, const stack<_Tp1, _Seq1>& __rhs)
	{ return __lhs.c == __rhs.c; }
	
	template<typename _Tp1, typename _Seq1>
	inline bool operator!=(const stack<_Tp1, _Seq1>& __lhs, const stack<_Tp1, _Seq1>& __rhs)
	{ return !(__lhs == __rhs); }

	template<typename _Tp1, typename _Seq1>
	inline bool operator<(const stack<_Tp1, _Seq1>& __lhs, const stack<_Tp1, _Seq1>& __rhs)
	{ return __lhs.c < __rhs.c; }
	
	template<typename _Tp1, typename _Seq1>
	inline bool operator<=(const stack<_Tp1, _Seq1>& __lhs, const stack<_Tp1, _Seq1>& __rhs)
	{ return !(__rhs < __lhs); }
	
	template<typename _Tp1, typename _Seq1>
	inline bool operator>(const stack<_Tp1, _Seq1>& __lhs, const stack<_Tp1, _Seq1>& __rhs)
	{ return __rhs < __lhs; }
	
	template<typename _Tp1, typename _Seq1>
	inline bool operator>=(const stack<_Tp1, _Seq1>& __lhs, const stack<_Tp1, _Seq1>& __rhs)
	{ return !(__lhs < __rhs); }
}

#endif /* STACK_HPP */
