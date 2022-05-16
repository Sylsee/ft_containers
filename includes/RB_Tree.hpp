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
#include <RB_Tree_iterator.hpp>

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
		  color(BLACK),
		  parent(NULL),
		  left(NULL),
		  right(NULL)
		{ }

		Node(_Tp *x)
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

		_Tp	*base() const
		{ return this->data; }
	};

	template<typename _Tp, typename _Compare = std::less<_Tp>,
			 typename _Alloc = std::allocator<_Tp> >
	class RB_Tree
	{
	public:
		typedef _Tp										 value_type;
		typedef value_type*								 pointer;
		typedef const value_type*						 const_pointer;
		typedef value_type&								 reference;
		typedef const value_type&						 const_reference;
		typedef size_t									 size_type;
		typedef ptrdiff_t								 difference_type;

		typedef RB_Tree_iterator<value_type>			 iterator;
		typedef RB_Tree_iterator<const value_type>		 const_iterator;
		typedef ft::reverse_iterator<iterator>			 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	 const_reverse_iterator;

		typedef _Compare								 value_compare;
		typedef _Alloc									 allocator_type;
		typedef typename allocator_type::template
					rebind<Node<value_type> >::other	 node_allocator;
		typedef Node<value_type>*						 node_pointer;

		RB_Tree()
		: _root()
		{
			this->_nill = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(this->_nill, Node());
			this->_head = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(this->_head, Node());
			// this->_head->data = this->_node_alloc.allocate(1);
			// this->_node_alloc.construct(this->_head->data, value_type())
		}

		RB_Tree(const _Compare* comp,
				const allocator_type* a = allocator_type())
		: 

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

		void	insert(value_type value)
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
					if (!_is_nill(__tmp->left) && _comp(value, *__tmp->base()))
						__tmp = __tmp->left;
					if (!_is_nill(__tmp->right) && _comp(*__tmp->base(), value))
						__tmp = __tmp->right;
					else
						throw(std::invalid_argument("ft::RB_Tree canno't insert two node as the same value"));
				}
				__tmp = __tmp->parent;

				if (!_is_nill(__tmp->left) && _comp(value, *__tmp->base()))
					__tmp->left = new_node;
				if (!_is_nill(__tmp->right) && _comp(*__tmp->base(), value))
					__tmp->right = new_node;

				new_node->parent = __tmp;
				new_node->color = RED;

				// _fix_height(new_node);
			}
		}

		node_pointer min(node_pointer node = NULL) const
		{ return _min(node == NULL ? this->_root : node); }

		node_pointer max(node_pointer node = NULL) const
		{ return _max(node == NULL ? this->_root : node); }

		iterator find(const value_type& value, node_pointer node = NULL) const
		{
			if (node == NULL)
				node = this->_root;
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

		node_pointer get_node(const value_type& value, node_pointer node = NULL) const
		{
			if (node == NULL)
				node = this->_root;
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

		size_type count(node_pointer node = NULL) const
		{
			if (node == NULL)
				node = this->_root;
			if (_is_nill(node))
				return 0;

			size_type nb_node = 0;
			nb_node += count(node->left);
			nb_node += count(node->right);

			return nb_node;
		}

		void	display() const
		{
			_display(this->_root, "", true);
		}

	private:
		typedef Node<_Tp>	Node;

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
			if (_is_nill(node))
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

		void _display(node_pointer root, std::string indent, bool last) const
		{
			if (!_is_nill(root)) {
				std::cout << indent;
				if (last) {
					std::cout << "R----";
					indent += "   ";
				} else {
					std::cout << "L----";
					indent += "|  ";
				}

				std::string sColor = root->color ? "BLACK" : "RED";
				std::cout << root->base() << "(" << sColor << ")" << std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
		}

	};
	
	
} /* namespace ft */


#endif /* RB_TREE_HPP */