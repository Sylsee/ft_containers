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
#include <stdexcept>

namespace ft
{
	enum node_color { BLACK = true, RED = false };

	template<typename _Tp>
	struct	Node
	{
	public:
		_Tp  *data;
		bool color;
		Node *parent;
		Node *left;
		Node *right;

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
		typedef _Tp*									 pointer;
		typedef const _Tp*								 const_pointer;
		typedef _Tp&									 reference;
		typedef const _Tp&								 const_reference;
		typedef size_t									 size_type;
		typedef ptrdiff_t								 difference_type;

		typedef tree_iterator<_Tp>						 iterator;
		typedef tree_iterator<const _Tp>				 const_iterator;
		typedef ft::reverse_iterator<iterator>			 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	 const_reverse_iterator;

		typedef _Compare								 value_compare;
		typedef _Alloc									 allocator_type;
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

		void	_left_rotate(node_pointer node)
		{
			if (_is_nill(node) || _is_nill(node->parent))
				return ;

			node_pointer parent = node->parent;

			parent->right = node->left;
			node->parent = parent->parent;
			parent->parent = node;
			node->left = parent;
		}

		void	_right_rotate(node_pointer node)
		{
			if (_is_nill(node) || _is_nill(node->parent))
				return ;

			node_pointer parent = node->parent;

			parent->left = node->right;
			node->parent = parent->parent;
			parent->parent = node;
			node->right = parent;
		}

		void	_insert_value(pointer value)
		{
			node_pointer new_node(value);

			++this->_size;
			if (_is_nill(this->_root))
				this->_root = new_node;
			else
			{
				node_pointer __tmp = this->_root;
				while (!_is_nill(__tmp))
				{
					if (!_is_nill(__tmp->left) && _comp(value, *__tmp->value))
						__tmp = __tmp->left;
					if (!_is_nill(__tmp->right) && _comp(*__tmp->value, value))
						__tmp = __tmp->right;
					else
						throw(std::invalid_argument("ft::RB_Tree canno't insert two node as the same value"));
				}
				__tmp = __tmp->parent;

				if (!_is_nill(__tmp->left) && _comp(value, *__tmp->value))
					__tmp->left = new_node;
				if (!_is_nill(__tmp->right) && _comp(*__tmp->value, value))
					__tmp->right = new_node;

				new_node->parent = __tmp;
				new_node->color = RED;

				// _fix_height(new_node);
			}
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

		node_pointer min(node_pointer node = this->root) const
		{ return _min(node); }

		node_pointer max(node_pointer node = this->root) const
		{ return _max(node); }

		iterator find(const value_type& value, node_pointer node = this->_root) const
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

		node_pointer get_node(const value_type& value, node_pointer node = this->_root) const
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

		size_type count(node_pointer node = this->root) const
		{
			if (_is_nill(node))
				return 0;

			size_type nb_node = 0;
			nb_node += count(node->left);
			nb_node += count(node->right);

			return nb_node;
		}

	};
	
	
} /* namespace ft */


#endif /* RB_TREE_HPP */