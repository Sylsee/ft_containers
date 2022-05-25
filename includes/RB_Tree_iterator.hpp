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
#include <RB_Tree.hpp>

namespace ft
{
	template<typename _Tp>
	struct RB_Tree_iterator
	{
	public:
		typedef _Tp								value_type;
		typedef _Tp&							reference;
		typedef _Tp*							pointer;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t						difference_type;
		typedef Node::_Base						_Base;

		_Base _node;

		RB_Tree_iterator()
		: _node(_Tp())
		{ }

		explicit RB_Tree_iterator(_Base x)	
		: _node(Node(x))
		{ }

		reference operator*() const
		{ return *_node; }

		pointer operator->() const
		{ return _node; }

		RB_Tree_iterator& operator++()
		{
			_node = _increment(_node);
			return (*this);
		}

		RB_Tree_iterator operator++(int)
		{
			RB_Tree_iterator<value_type> tmp = *this;
			_node = _increment(_node);
			return tmp;
		}

		RB_Tree_iterator& operator--()
		{
			_node = _decrement(_node);
			return (*this);
		}

		RB_Tree_iterator operator--(int)
		{
			RB_Tree_iterator<value_type> tmp = *this;
			_node = _decrement(_node);
			return tmp;
		}

		friend inline bool operator==(const RB_Tree_iterator& lhs,
									  const RB_Tree_iterator& rhs)
		{ return lhs.base() == rhs.base(); }

		friend inline bool operator!=(const RB_Tree_iterator& lhs,
									  const RB_Tree_iterator& rhs)
		{ return lhs.base() != rhs.base(); }


	private:
		_Base _increment(_Base *node)
		{
			if (node->right != 0)
			{
				node = node->right;
				while (node->left != 0)
					node = node->left;
			}
			else
			{
				_Base *tmp = node->parent;
				while (node == tmp->right)
				{
					node = tmp;
					tmp = tmp->parent;
				}
				if (node->right != tmp)
					node = tmp;
				
			}
			return node;
		}

		_Base _decrement(_Base *node)
		{
			if (node->color == RED && node->parent->parent == node)
				node = node->right;
			else if (node->left != 0)
			{
				_Base *tmp = node->left;
				while (tmp->right != 0)
					tmp = tmp->right;
				node = tmp;
			}
			else
			{
				value_type *tmp = node->parent;
				while (node == tmp->left)
				{
					node = tmp;
					tmp = tmp->parent;
				}
				node = tmp;
			}
			return node;
		}
	};

} /* namespace ft */


#endif /* RB_TREE_ITERATOR_HPP */