/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RB_Tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <sylvio.poliart@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 20:36:44 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/08 20:36:47 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_HPP
#define RB_TREE_ITERATOR_HPP

#include <memory>
#include <functional>
#include <traits.hpp>

namespace ft
{
	template<typename _Tp>
	class RB_Tree_iterator
	{
	public:
		typedef _Tp  value_type;
		typedef _Tp& reference;
		typedef _Tp* pointer;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t						difference_type;

	private:
		_Tp _current;

		typedef iterator_traits<_Tp> traits_type;

	public:
		RB_Tree_iterator()
		: _current(_Tp())
		{ }

		explicit RB_Tree_iterator(value_type x)	
		: _current(x)
		{ }

		value_type base() const
		{ return this->_current; }

		reference operator*() const
		{ return *_current; }

		pointer operator->() const
		{ return _current; }

		/* TODO */
		RB_Tree_iterator& operator++()
		{ }

		RB_Tree_iterator operator++(int)
		{ }

		RB_Tree_iterator& operator--()
		{ }

		RB_Tree_iterator operator--(int)
		{ }
		/********/

		friend inline bool operator==(const RB_Tree_iterator& lhs, const RB_Tree_iterator& rhs)
		{ return lhs.base() == rhs.base(); }

		friend inline bool operator!=(const RB_Tree_iterator& lhs, const RB_Tree_iterator& rhs)
		{ return lhs.base() != rhs.base(); }
	};

} /* namespace ft */


#endif /* RB_TREE_ITERATOR_HPP */