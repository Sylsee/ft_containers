/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <sylvio.poliart@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:38:04 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/08 14:38:06 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include <utils.hpp>
#include <traits.hpp>
#include <RB_Tree.hpp>

namespace ft
{
	template<typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
			 typename _Alloc = std::allocator<ft::pair<const _Key, _Tp> > >
	class map
	{
	public:
		typedef _Key										key_type;
		typedef _Tp											mapped_type;
		typedef ft::pair<const _Key, _Tp>					value_type;
		typedef _Compare									key_compare;
		typedef _Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

		class value_compare
		{
			friend class map<_Key, _Tp, _Compare, _Alloc>;
		
		protected:
			_Compare comp;

			value_compare(_Compare __c)
			: comp(__c) { }

		public:
			bool operator()(const value_type& __x, const value_type& __y) const
			{ return comp(__x.first, __y.first); }
		};

	private:
		typedef ft::RB_Tree<value_type, value_compare, allocator_type>	_Rep_type;

		_Rep_type	_tree;

	public:
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type())
		: _tree()
		{ }

		~map()
		{ }
	};

} /* namespace ft */


#endif /* MAP_HPP */