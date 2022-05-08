/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RB_Tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <sylvio.poliart@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:08:16 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/07 14:08:19 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <memory>
#include <functional>

namespace ft
{
	enum node_color { BLACK = true, RED = false };

	template<typename _Tp>
	struct	Node
	{
	public:
		_Tp		*data;
		bool	color;
		Node	*parent;
		Node	*left;
		Node	*right;

		Node()
		: data(NULL),
		  left(NULL),
		  right(NULL),
		  parent(NULL),
		  color(BLACK)
		{ }

		Node(_Tp& x)
		: data(x),
		  color(BLACK),
		  parent(NULL),
		  left(NULL),
		  right(NULL)
		{ }

		Node(const Node& rhs)
		{ *this = rhs; }

		virtual ~Node()
		{ }

		Node operator=(const Node& rhs)
		{
			if (this != &rhs)
			{
				this->data = rhs.data;
				this->color = rhs.color;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
			}
			return *this;
		}
	};

	template<typename _Tp, typename _Compare = std::less<_Tp>,
			 typename _Alloc = std::allocator<_Tp> >
	class RB_Tree
	{
	public:
		typedef _Tp										 value_type;
		typedef _Compare								 value_compare;
		typedef _Alloc									 allocator_type;
		typedef typename allocator_type::pointer		 pointer;
		typedef typename allocator_type::const_pointer	 const_pointer;
		typedef typename allocator_type::reference		 reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef size_t									 size_type;
		typedef ptrdiff_t								 difference_type;
		typedef tree_iterator<_Tp>						 iterator;
		typedef tree_iterator<const _Tp>				 iterator;
		typedef ft::reverse_iterator<iterator>			 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	 const_reverse_iterator;
		typedef Node*									 node_pointer;

	private:
		typedef typename Node<_Tp>	Node;

		allocator_type	_alloc;
		value_compare	_comp;
		node_pointer	_root;
		node_pointer	_header;
		node_pointer	_nill;

		node_pointer	_min(node_pointer node)
		{
			while (node->left != _nill)
				node = node->left;
			return node;
		}

	public:

		RB_Tree()
		: _root()
		{
			this->_nill = this->_alloc.allocate(1);
			this->_alloc.construct(this->_nill);
		}

		~RB_Tree()
		{ }

		node_pointer min() const
		{ return _min(this->_root); }

		node_pointer max() const
		{ return _max(this->_root); }

		iterator find(const value_type& value, node_pointer node) const
		{
			if (node == NULL || node == this->_nill)
				return NULL;
			while (node != this->_nill)
			{
				if (_comp(value, *node->value))
					node = node->left;
				else if (_comp(*node->value, value))
					node = node->right;
				else
					break;
			}
			return iterator(node);
		}

	};
	
	
} /* namespace ft */


#endif /* RB_TREE_HPP */