/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RB_Tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <sylvio.poliart@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:08:16 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/31 21:26:58 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <memory>
#include <functional>
#include <stdexcept>
#include <cstddef>
#include <traits.hpp>
#include <iterator.hpp>
#include <vector>

namespace ft
{
	enum node_color { BLACK = true, RED = false };

	template<typename _Tp>
	struct Node
	{
	public:
		typedef Node* _Base;

		_Tp			*data;
		node_color	color;
		_Base		parent;
		_Base		left;
		_Base		right;

		Node()
		: data(0),
		  color(BLACK)
		{ }

		Node(_Tp *x)
		: data(x),
		  color(BLACK)
		{ }

		Node(const Node& rhs)
		{
			if (this != &rhs)
			{
				this->data = rhs.data;
				this->color = rhs.color;
				this->parent = rhs.parent;
				this->left = rhs.left;
				this->right = rhs.right;
			}
		}

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

	template<typename _Tp>
	struct RB_Tree_iterator
	{
	public:
		typedef _Tp								value_type;
		typedef _Tp&							reference;
		typedef _Tp*							pointer;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t						difference_type;
		typedef Node<_Tp>*						_Base;

		_Base _node;

		RB_Tree_iterator()
		: _node(_Tp())
		{ }

		explicit RB_Tree_iterator(_Base x)	
		: _node(x)
		{ }

		reference operator*() const
		{ return *_node->data; }

		pointer operator->() const
		{ return _node->data; }

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

		friend bool operator==(const RB_Tree_iterator<_Tp>& lhs,
							   const RB_Tree_iterator<_Tp>& rhs)
		{ return lhs._node == rhs._node; }

		friend bool operator!=(const RB_Tree_iterator<_Tp>& lhs,
							   const RB_Tree_iterator<_Tp>& rhs)
		{ return lhs._node != rhs._node; }

		inline _Base	base()
		{ return _node; }


	private:
		_Base _increment(_Base node)
		{
			if (node->right != 0)
			{
				node = node->right;
				while (node->left != 0)
					node = node->left;
			}
			else
			{
				_Base tmp = node->parent;
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

		_Base _decrement(_Base node)
		{
			if (node->color == RED && node->parent->parent == node)
				node = node->right;
			else if (node->left != 0)
			{
				_Base tmp = node->left;
				while (tmp->right != 0)
					tmp = tmp->right;
				node = tmp;
			}
			else
			{
				_Base tmp = node->parent;
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

	template<typename _Tp, typename _Compare = std::less<_Tp>,
			 typename _Alloc = std::allocator<_Tp> >
	class RB_Tree
	{
	protected:
		typedef Node<_Tp>	_Node;

#include <../visualizer/map_display.hpp>


	public:
		typedef _Tp									 value_type;
		typedef value_type*							 pointer;
		typedef const value_type*					 const_pointer;
		typedef value_type&							 reference;
		typedef const value_type&					 const_reference;
		typedef size_t								 size_type;
		typedef ptrdiff_t							 difference_type;

		typedef RB_Tree_iterator<value_type>		 iterator;
		typedef RB_Tree_iterator<const value_type>	 const_iterator;
		typedef ft::reverse_iterator<iterator>			 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	 const_reverse_iterator;

		typedef _Compare							 value_compare;
		typedef _Alloc								 allocator_type;
		typedef typename allocator_type::template
					rebind<_Node>::other			 node_allocator;
		typedef _Node*								 node_pointer;

		RB_Tree(const value_compare &comp = value_compare(),
				const allocator_type &a = allocator_type())
		: _val_alloc(a),
		  _node_alloc(node_allocator()),
		  _compare(comp)
		{
			_header.parent = 0;
			_header.right = &_header;
			_header.left = &_header;
			_header.color = RED;
			_size = 0;
		}

		~RB_Tree()
		{ _destroy(_header.parent); }

		/**
		 * @brief Get the minimum node from a node
		 * 
		 * @param node The node where to start the search
		 * @return node_pointer the minimum node
		 */
		node_pointer min(node_pointer node = 0) const
		{ return _min(node == 0 ? _header.parent : node); }

		/**
		 * @brief Get the maximum node from a node
		 * 
		 * @param node The node where to start the search
		 * @return node_pointer the maximum node
		 */
		node_pointer max(node_pointer node = 0) const
		{ return _max(node == 0 ? _header.parent : node); }

		/**
		 * @brief Get node from a value
		 * 
		 * @param value The value to search
		 * @param node The node where to start the search
		 * @return iterator the iterator of the node
		 */
		iterator find(const value_type& value, node_pointer node = 0)
		{
			if (node == 0)
				node = _header.parent;
			while (node != 0)
			{
				if (_compare(value, *node->data))
					node = node->left;
				else if (_compare(*node->data, value))
					node = node->right;
				else
					break;
			}
			if (node == 0)
				return iterator();
			return iterator(node);
		}

		node_pointer get_node(const value_type& value, node_pointer node = 0)
		{
			if (node == 0)
				node = _header.parent;
			while (node != 0)
			{
				if (_compare(value, *node->data))
					node = node->left;
				else if (_compare(*node->data, value))
					node = node->right;
				else
					break;
			}
			if (node == 0)
				return 0;
			return node;
		}

		size_type count(node_pointer node = 0) const
		{
			if (node == 0)
				node = _header.parent;
			if (node == 0)
				return 0;

			size_type nb_node = 1;
			nb_node += count(node->left);
			nb_node += count(node->right);

			return nb_node;
		}

		inline iterator begin()
		{ return iterator(_header.left); }

		inline const_iterator begin() const
		{ return const_iterator(_header.left); }

		inline iterator end()
		{ return iterator(_header.right); }

		inline const_iterator end() const
		{ return const_iterator(_header.right); }

		inline reverse_iterator rbegin()
		{ return reverse_iterator(_header.right); }

		inline const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(_header.right); }

		inline reverse_iterator rend()
		{ return reverse_iterator(_header.left); }

		inline const_reverse_iterator rend() const
		{ return const_reverse_iterator(_header.left); }

		pair<iterator, bool>	insert(const value_type& value)
		{
			pair<node_pointer, node_pointer> pos = 
				_insert_unique_pos(value);

			if (pos.second)
			{
				_insert(pos.first, pos.second, _new_node(value));
				return pair<iterator, bool>(iterator(pos.first), true);
			}
			return pair<iterator, bool>(iterator(pos.first), false);
		}

		_Node			_header;
	protected:
		allocator_type	_val_alloc;
		node_allocator	_node_alloc;
		value_compare	_compare;
		size_type		_size;

		iterator _insert(node_pointer pos, node_pointer parent, node_pointer new_node)
		{
			bool insert_left = (pos != 0 || parent == &_header
								|| _compare(*new_node->data, *parent->data));

			new_node->parent = parent;
			new_node->left = 0;
			new_node->right = 0;
			new_node->color = RED;

			if (insert_left)
			{
				parent->left = new_node;
				if (parent == &_header)
				{
					_header.parent = new_node;
					_header.right = new_node;
				}
				else if (parent == _header.left)
					_header.left = new_node;
			}
			else
			{
				parent->right = new_node;
				if (parent == _header.right)
					_header.right = new_node;
			}
			_rebalance_insertion(new_node);
			++this->_size;
			return iterator(new_node);
		}

		/**
		 * @brief Fix the height of the tree after an insertion
		 * 
		 * @param node The node inserted
		 */
		void	_rebalance_insertion(node_pointer new_node)
		{
			node_pointer& _root = _header.parent;

			while (new_node != _root && new_node->parent->color == RED)
			{
				node_pointer const gp = new_node->parent->parent;

				if (new_node->parent == gp->left)
				{
					node_pointer const tmp = gp->right;
					if (tmp && tmp->color == RED)
					{
						new_node->parent->color = BLACK;
						tmp->color = BLACK;
						gp->color = RED;
						new_node = gp;
					}
					else
					{
						if (new_node == new_node->parent->right)
						{
							new_node = new_node->parent;
							_rotate_left(new_node);
						}
						new_node->parent->color = BLACK;
						gp->color = RED;
						_rotate_right(gp);
					}
				}
				else
				{
					node_pointer const tmp = gp->left;
					if (tmp && tmp->color == RED)
					{
						new_node->parent->color = BLACK;
						tmp->color = BLACK;
						gp->color = RED;
						new_node = gp;
					}
					else
					{
						if (new_node == new_node->parent->left)
						{
							new_node = new_node->parent;
							_rotate_right(new_node);
						}
						new_node->parent->color = BLACK;
						gp->color = RED;
						_rotate_left(gp);
					}
				}
			}
			_root->color = BLACK;
		}

		void	_rotate_left(node_pointer const x)
		{
			node_pointer const tmp = x->right;

			x->right = tmp->left;
			if (tmp->left != 0)
				tmp->left->parent = x;
			tmp->parent = x->parent;

			if (x == _header.parent)
				_header.parent = tmp;
			else if (x == x->parent->left)
				x->parent->left = tmp;
			else
				x->parent->right = tmp;
			tmp->left = x;
			x->parent = tmp;
		}

		void	_rotate_right(node_pointer const x)
		{
			node_pointer const tmp = x->left;

			x->left = tmp->right;
			if (tmp->right != 0)
				tmp->right->parent = x;
			tmp->parent = x->parent;

			if (x == _header.parent)
				_header.parent = tmp;
			else if (x == x->parent->right)
				x->parent->right = tmp;
			else
				x->parent->left = tmp;
			tmp->right = x;
			x->parent = tmp;
		}

		inline node_pointer	_right_most()
		{ return this->_header.right; }

		inline node_pointer	_left_most()
		{ return this->_header.left; }

		/**
		 * @brief Find the position to insert a node
		 * 
		 * @param new_val The value of the node to insert
		 * @return node_pointer the position to insert
		 */
		ft::pair<node_pointer, node_pointer>
		_insert_unique_pos(const value_type& new_val)
		{
			typedef ft::pair<node_pointer, node_pointer> res;
			node_pointer new_pos = _header.parent;
			node_pointer parent = &_header;
			bool comp = true;

			while (new_pos != 0)
			{
				parent = new_pos;
				comp = _compare(new_val, *new_pos->data);
				new_pos = comp ? new_pos->left : new_pos->right;
			}
			iterator it = iterator(parent);
			if (comp)
			{
				if (it == begin())
					return res(new_pos, parent);
				else
					--it;
			}
			if (_compare(*it, new_val))
				return res(new_pos, parent);
			return res(it._node, 0);
		}

		/**
		 * @brief Get the minimum node from a node
		 * 
		 * @param node The node where to start the search
		 * @return node_pointer the minimum node
		 */
		inline node_pointer _min(node_pointer node) const
		{
			while (node->left != 0)
				node = node->left;
			return node;
		}

		/**
		 * @brief Get the maximum node from a node
		 * 
		 * @param node The node where to start the search
		 * @return node_pointer the maximum node
		 */
		inline node_pointer _max(node_pointer node) const
		{
			while (node->right != 0)
				node = node->right;
			return node;
		}

		/**
		 * @brief Destroy and deallocate the node
		 * 
		 * @param node The node to delete
		 */
		void _delete_node(node_pointer node)
		{
			if (node->data)
			{
				this->_val_alloc.destroy(node->data);
				this->_val_alloc.deallocate(node->data, 1);
			}
			this->_node_alloc.destroy(node);
			this->_node_alloc.deallocate(node, 1);
		}

		/**
		 * @brief Destroy and deallocate the tree from the specify node
		 * 
		 * @param node The start to delete
		 */
		void	_destroy(node_pointer node)
		{
			if (node == 0)
				return ;

			_destroy(node->left);
			_destroy(node->right);
			_delete_node(node);
		}

		inline pointer _new_value(const value_type &x)
		{
			pointer new_val = this->_val_alloc.allocate(1);
			this->_val_alloc.construct(new_val, x);
			return new_val;
		}

		node_pointer	_new_node(const value_type &x)
		{
			node_pointer new_node = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(new_node, _Node(_new_value(x)));
			new_node->left = 0;
			new_node->right = 0;
			new_node->parent = 0;
			return new_node;
		}
	};

} /* namespace ft */


#endif /* RB_TREE_HPP */