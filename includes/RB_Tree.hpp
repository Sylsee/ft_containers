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
		typedef typename allocator_type::template
							rebind<Node<_Tp> >::other	 node_allocator;
		typedef Node*									 node_pointer;

	private:
		typedef typename Node<_Tp>	Node;

		allocator_type	_val_alloc;
		node_allocator	_node_alloc;
		value_compare	_comp;
		node_pointer	_root;
		node_pointer	_head;
		node_pointer	_nill;
		size_type		_size;

		node_pointer	_min(node_pointer node) const
		{
			while (is_nill(node->left))
				node = node->left;
			return node;
		}

		node_pointer	_max(node_pointer node) const
		{
			while (is_nill(node->right))
				node = node->right;
			return node;
		}

		inline bool _is_nill(const node_pointer node) const
		{ return (node == NULL || node == this->_nill || node == this->_head); }

		void	_destroy(node_pointer node)
		{
			if (is_nill(node))
				return ;

			_destroy(node->left);
			_destroy(node->right);
			this->_node_alloc.destroy(node);
			this->_node_alloc.deallocate(node, 1);
		}

	public:

		RB_Tree()
		: _root()
		{
			this->_nill = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(this->_nill, Node<value_type>());
			this->_head = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(this->_head, Node<value_type>());
			// this->_head->data = this->_node_alloc.allocate(1);
			// this->_node_alloc.construct(this->_head->data, value_type())
		}

		~RB_Tree()
		{
			_destroy(this->_root);
			this->_node_alloc.destroy(this->_nill);
			this->_node_alloc.deallocate(this->_nill, 1);
			// this->_node_alloc.destroy(this->_head->data);
			// this->_node_alloc.deallocate(this->_head->data, 1);
			this->_node_alloc.destroy(this->_head);
			this->_node_alloc.deallocate(this->_head, 1);
		}

		node_pointer min() const
		{ return _min(this->_root); }

		node_pointer max() const
		{ return _max(this->_root); }

		iterator find(const value_type& value, node_pointer node) const
		{
			while (!is_nill(node))
			{
				if (!is_nill(node->left) && _comp(value, *node->value))
					node = node->left;
				else if (!is_nill(node->right) && _comp(*node->value, value))
					node = node->right;
				else
					break;
			}
			return iterator(node);
		}

	};
	
	
} /* namespace ft */


#endif /* RB_TREE_HPP */