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
	template<typename Iterator, typename _Compare = std::less<Iterator> >
	class RB_Tree_iterator
	{
	private:
		Iterator _current;

		typedef iterator_traits<Iterator> traits_type;

	public:
		typedef Iterator								iterator_type;
		typedef typename traits_type::iterator_category	iterator_category;
		typedef typename traits_type::value_type		value_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;

		RB_Tree_iterator()
		: _current(Iterator())
		{ }

		explicit RB_Tree_iterator(iterator_type x)
		: _current(x)
		{ }

		template<typename Iter>
		RB_Tree_iterator(const RB_Tree_iterator<Iter>& x)
		: _current(x.base())
		{ }

		~RB_Tree_iterator()
		{ }

		iterator_type base() const
		{ return this->_current; }

		reference operator*() const
		{ return *_current; }

		pointer operator->() const
		{ return _current; }
	};

} /* namespace ft */


#endif /* RB_TREE_ITERATOR_HPP */