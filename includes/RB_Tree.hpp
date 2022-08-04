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

		_Tp			data;
		node_color	color;
		_Base		parent;
		_Base		left;
		_Base		right;

		Node()
		: color(RED)
		{ }

		Node(_Tp x)
		: data(x),
		  color(RED)
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
		{ return _node->data; }

		pointer operator->() const
		{ return &_node->data; }

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

	template<typename _Tp, typename _Compare,
			 typename _Alloc = std::allocator<_Tp> >
	class RB_Tree
	{
	protected:
		typedef Node<_Tp>	_Node;

#include <../visualizer/map_display.hpp>

	public:

		/**
		 * Helper who print the tree with color
		 */
		void print_tree()
		{ print_tree(_header.parent); }

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
		typedef ft::reverse_iterator<iterator>		 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef _Compare							 value_compare;
		typedef _Alloc								 allocator_type;
		typedef typename allocator_type::template
					rebind<_Node>::other			 node_allocator;
		typedef _Node*								 node_pointer;
		typedef const _Node*						 const_node_pointer;
		typedef _Node&								 node_reference;

		RB_Tree(const value_compare &comp = value_compare(),
				const allocator_type &a = allocator_type())
		: _node_alloc(node_allocator(a)),
		  _compare(comp)
		{
			_header.parent = 0;
			_header.right = &_header;
			_header.left = &_header;
			_header.color = RED;
			_size = 0;
		}

		RB_Tree(const RB_Tree& x)
		{
			if (x._root() != 0)
				_root() = _copy(x);
		}

		~RB_Tree()
		{ _erase(_header.parent); }

		RB_Tree operator=(const RB_Tree& rhs)
		{
			if (this != &rhs)
			{
				_reset();
				_compare = rhs._compare;
				if (rhs._root() != 0)
					_root() = _copy(rhs);
			}
			return *this;
		}

		inline bool empty() const
		{ return this->_size == 0; }

		size_type size() const
		{ return this->_size; }

		size_type max_size() const
		{ return _node_alloc.max_size(); }

		allocator_type get_allocator() const
		{ return allocator_type(_node_alloc); }

		_Compare key_comp() const
		{ return _compare; }

		/**
		 * @brief Get the minimum node from a node
		 * 
		 * @param node The node where to start the search
		 * @return node_pointer the minimum node
		 */
		inline node_pointer min(node_pointer node) const
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
		inline node_pointer max(node_pointer node) const
		{
			while (node->right != 0)
				node = node->right;
			return node;
		}

		/**
		 * @brief Get node from a value
		 * 
		 * @param value The value to search
		 * @param node The node where to start the search
		 * @return iterator the iterator of the node
		 */
		// iterator find(const value_type& value)
		// {
		// 	node_pointer tmp = _header.parent;

		// 	while (tmp != 0)
		// 	{
		// 		if (_compare(value, tmp->data))
		// 			tmp = tmp->left;
		// 		else if (_compare(tmp->data, value))
		// 			tmp = tmp->right;
		// 		else
		// 			return iterator(tmp);
		// 	}
		// 	if (tmp == 0)
		// 		return iterator();
		// 	return iterator(tmp);
		// }

		// node_pointer get_node(const value_type& value)
		// {
		// 	node_pointer node = _header.parent;

		// 	while (node != 0)
		// 	{
		// 		if (_compare(value, node->data))
		// 			node = node->left;
		// 		else if (_compare(node->data, value))
		// 			node = node->right;
		// 		else
		// 			break;
		// 	}
		// 	if (node == 0)
		// 		return 0;
		// 	return node;
		// }

		// size_type count() const
		// {
		// 	node_pointer node = _header.parent;
		// 	if (node == 0)
		// 		return 0;

		// 	size_type nb_node = 1;
		// 	nb_node += count(node->left);
		// 	nb_node += count(node->right);

		// 	return nb_node;
		// }

		inline iterator begin()
		{ return iterator(_header.left); }

		inline const_iterator begin() const
		{ return const_iterator(_header.left); }

		inline iterator end()
		{ return iterator(&_header); }

		inline const_iterator end() const
		{ return const_iterator(&_header); }

		inline reverse_iterator rbegin()
		{ return reverse_iterator(_header.right); }

		inline const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(_header.right); }

		inline reverse_iterator rend()
		{ return reverse_iterator(_header.left); }

		inline const_reverse_iterator rend() const
		{ return const_reverse_iterator(_header.left); }

		iterator lower_bound(const value_type& value)
		{ return _lower_bound(begin(), end(), value); }

		const_iterator lower_bound(const value_type& value) const
		{ return _lower_bound(begin(), end(), value); }

		iterator upper_bound(const value_type& value)
		{ return _upper_bound(begin(), end(), value); }

		const_iterator upper_bound(const value_type& value) const
		{ return _upper_bound(begin(), end(), value); }

		pair<iterator, bool>	insert(const value_type& value)
		{
			pair<node_pointer, node_pointer> pos = 
				_get_insert_pos(value);

			if (pos.second)
			{
				_insert(pos.first, pos.second, _new_node(value));
				return pair<iterator, bool>(iterator(pos.first), true);
			}
			return pair<iterator, bool>(iterator(pos.first), false);
		}

		/**
		 * @brief Insert 
		 * 
		 * @param pos 
		 * @param data 
		 * @return iterator 
		 */
		iterator insert(iterator pos, const value_type& data)
		{
			pair<node_pointer, node_pointer> new_pos =
				_get_insert_pos(pos, data);

			if (new_pos.second)
				return _insert(new_pos.first, new_pos.second, _new_node(data));
			return iterator(new_pos.first);
		}

		template<typename InputIterator>
		void insert_range(InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				insert(end(), *first);
		}

	protected:
		node_allocator	_node_alloc;
		value_compare	_compare;
		size_type		_size;
		_Node			_header;

		const_node_pointer _root() const
		{ return _header.parent; }

		/**
		 * @brief Get the root of the tree
		 * 
		 * @return node_pointer& the root
		 */
		node_pointer& _root()
		{ return _header.parent; }

		/**
		 * @brief Reset the tree
		 */
		void _reset()
		{
			_header.data = 0;
			_header.color = RED;
			_header.parent = 0;
			_header.left = &_header;
			_header.right = &_header;
			this->_size = 0;
		}

		iterator _lower_bound(node_pointer x, node_pointer y,
							  const value_type& value)
		{
			while (x != 0)
			{
				if (!_compare(x->data, value))
					y = x, x = x->left;
				else
					x = x->right;
			}
			return iterator(y);
		}

		const_iterator _lower_bound(node_pointer x, node_pointer y,
							  const value_type& value) const
		{
			while (x != 0)
			{
				if (!_compare(x->data, value))
					y = x, x = x->left;
				else
					x = x->right;
			}
			return const_iterator(y);
		}

		iterator _upper_bound(node_pointer x, node_pointer y,
							  const value_type& value)
		{
			while (x != 0)
			{
				if (_compare(value, x->data))
					y = x, x = x->left;
				else
					x = x->right;
			}
			return iterator(y);
		}

		const_iterator _upper_bound(node_pointer x, node_pointer y,
							  const value_type& value) const
		{
			while (x != 0)
			{
				if (_compare(value, x->data))
					y = x, x = x->left;
				else
					x = x->right;
			}
			return const_iterator(y);
		}

		/**
		 * @brief Insert a new node on the tree
		 * 
		 * @param pos The position where to place the new node
		 * @param parent The parent of the new node
		 * @param new_node The new node
		 * @return iterator on the new node
		 */
		iterator _insert(node_pointer pos, node_pointer parent, node_pointer new_node)
		{
			bool insert_left = (pos != 0 || parent == &_header
								|| _compare(new_node->data, parent->data));

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
			node_pointer& root = _header.parent;

			while (new_node != root && new_node->parent->color == RED)
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
			root->color = BLACK;
		}

		void _erase(const_iterator pos)
		{
			node_pointer to_delete = _rebalance_for_erase(pos._node);

			_delete_node(to_delete);
			--this->_size;
		}

		/**
		 * @brief Rebalance tree for erase one node
		 * 
		 * @param pos The position of the node to erase
		 * @return The node to delete
		 */
		node_pointer _rebalance_for_erase(node_pointer const pos)
		{
			node_pointer &root = _header.parent;
			node_pointer &leftmost = _header.left;
			node_pointer &rightmost = _header.right;
			node_pointer tmp = pos;
			node_pointer x = 0;
			node_pointer x_parent = 0;

			if (tmp->left == 0)
				x = tmp->right;
			else if (tmp->right == 0)
				x = tmp->left;
			else
			{
				tmp = tmp->right;
				while (tmp->left != 0)
					tmp = tmp->left;
				x = tmp->right;
			}
			if (tmp != pos)
			{
				pos->left->parent = tmp;
				tmp->left = pos->left;
				if (tmp != pos->right)
				{
					x_parent = tmp->parent;
					if (x)
						x->parent = tmp->parent;
					tmp->parent->left = x;
					tmp->right = pos->right;
					pos->right->parent = tmp;
				}
				else
					x_parent = tmp;
				if (root == pos)
					root = tmp;
				else if (pos->parent->left == pos)
					pos->parent->left = tmp;
				else
					pos->parent->right = tmp;
				tmp->parent = pos->parent;
				ft::swap(tmp->color, pos->color);
				tmp = pos;
			}
			else
			{
				x_parent = tmp->parent;
				if (x)
					x->parent = tmp->parent;
				if (root == pos)
					root = x;
				else if (pos->parent->left == pos)
					pos->parent->left = x;
				else
					pos->parent->right = x;
				if (leftmost == pos)
				{
					if (pos->right == 0)
						leftmost = pos->parent;
					else
						leftmost = min(x);
				}
				if (rightmost == pos)
				{
					if (pos->left == 0)
						rightmost = pos->parent;
					else
						rightmost = max(x);
				}
			}
			if (tmp->color != RED)
			{
				while (x != root && (x == 0 || x->color == BLACK))
					if (x == x_parent->left)
					{
						node_pointer y = x_parent->right;
						if (y->color == RED)
						{
							y->color = BLACK;
							x_parent->color = RED;
							_rotate_left(x_parent, root);
							y = x_parent->right;
						}
						if ((y->left == 0 ||
							y->left->color == BLACK) &&
							(y->right == 0 ||
							y->right->color == BLACK))
						{
							y->color = RED;
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else
						{
							if (y->right == 0 || y->right->color == BLACK)
							{
								y->left->color = BLACK;
								y->color = RED;
								_rotate_right(y, root);
								y = x_parent->right;
							}
							y->color = x_parent->color;
							x_parent->color = BLACK;
							if (y->right)
								y->right->color = BLACK;
							_rotate_left(x_parent, root);
							break;
						}
					}
					else
					{
						node_pointer y = x_parent->left;
						if (y->color == RED)
						{
							y->color = BLACK;
							x_parent->color = RED;
							_rotate_right(x_parent, root);
							y = x_parent->left;
						}
						if ((y->right == 0 ||
							y->right->color == BLACK) &&
							(y->left == 0 ||
							y->left->color == BLACK))
						{
							y->color = RED;
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else
						{
							if (y->left == 0 || y->left->color == BLACK)
							{
								y->right->color = BLACK;
								y->color = RED;
								_rotate_left(y, root);
								y = x_parent->left;
							}
							y->color = x_parent->color;
							x_parent->color = BLACK;
							if (y->left)
								y->left->color = BLACK;
							_rotate_right(x_parent, root);
							break;
						}
					}
				if (x)
					x->color = BLACK;
			}
			return tmp;
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

		/**
		 * @brief Get the maximum of the tree
		 * 
		 * @return node_pointer the maximum of the tree
		 */
		inline node_pointer	_right_most()
		{ return this->_header.right; }

		/**
		 * @brief Get the minimum of the tree
		 * 
		 * @return node_pointer the minimum of the tree
		 */
		inline node_pointer	_left_most()
		{ return this->_header.left; }

		/**
		 * @brief Find the position to insert a node
		 * 
		 * @param new_val The value of the node to insert
		 * @return node_pointer the position to insert
		 */
		pair<node_pointer, node_pointer>
		_get_insert_pos(const value_type& new_val)
		{
			typedef ft::pair<node_pointer, node_pointer> res;
			node_pointer new_pos = _header.parent;
			node_pointer parent = &_header;
			bool comp = true;

			while (new_pos != 0)
			{
				parent = new_pos;
				comp = _compare(new_val, new_pos->data);
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

		pair<node_pointer, node_pointer>
		_get_insert_pos(iterator position, const value_type& new_val)
		{
			iterator pos = position;
			typedef pair<node_pointer, node_pointer> res;

			if (pos._node == &_header)
			{
				if (size() > 0 && _compare(_right_most()->data, new_val))
					return res(0, _right_most());
				else
					return _get_insert_pos(new_val);
			}
			else if (_compare(new_val, pos._node->data))
			{
				iterator before = pos;
				if (pos._node == _left_most())
					return res(_left_most(), _left_most());
				else if (_compare((--before)._node->data, new_val))
				{
					if (before._node->right == 0)
						return res(0, before._node);
					else
						return res(pos._node, pos._node);
				}
				else
					return _get_insert_pos(new_val);
			}
			else if (_compare(pos._node->data, new_val))
			{
				iterator after = pos;
				if (pos._node == _right_most())
					return res(0, _right_most());
				else if (_compare(new_val, (++after)._node->data))
				{
					if (pos._node->right == 0)
						return res(0, pos._node);
					else
						return res(after._node, after._node);
				}
				else
					return _get_insert_pos(new_val);
			}
			else
				return res(pos._node, 0);
		}

		/**
		 * @brief Clone a node
		 * 
		 * @param src The node to clone
		 * @return node_pointer the new node
		 */
		node_pointer	_clone_node(node_pointer src)
		{
			node_pointer tmp = _new_node(src->data);
			tmp->color = src->color;
			return tmp;
		}

		node_pointer _begin() const
		{ return _header.parent; }

		/**
		 * @brief Copy a RB_Tree
		 * 
		 * @param src The tree to copy
		 * @return node_pointer the new root
		 */
		node_pointer _copy(const RB_Tree& src)
		{
			node_pointer root = _copy(src._begin(), &_header);
			_header.left = min(root);
			_header.right = max(root);
			this->_size = src.size();
			return root;
		}

		/**
		 * @brief Copy all the tree from src to dst
		 * 
		 * @param src The tree to copy
		 * @param dst The destination for copy
		 * @return node_pointer the root of the new tree
		 */
		node_pointer _copy(node_pointer src, node_pointer dst)
		{
			node_pointer tmp = _clone_node(src);
			tmp->parent = dst;

			try
			{
				if (src->right)
					tmp->right = _copy(src->right, tmp);
				dst = tmp;
				src = src->left;

				while (src != 0)
				{
					node_pointer tmp2 = _clone_node(src);
					dst->left = tmp2;
					tmp2->parent = dst;
					if (src->right)
						tmp2->right = _copy(src->right, tmp2);
					dst = tmp2;
					src = src->left;
				}
			}
			catch (...)
			{
				_erase(tmp);
				throw ;
			}
			return tmp;
		}

		/**
		 * @brief Erase a tree from this node
		 * 
		 * @param x The node where to start erasing
		 */
		void	_erase(node_pointer x)
		{
			while (x != 0)
			{
				_erase(x->right);
				node_pointer tmp = x->left;
				_delete_node(x);
				x = tmp;
			}
		}

		/**
		 * @brief Destroy and deallocate a node
		 * 
		 * @param node The node to delete
		 */
		void _delete_node(node_pointer node)
		{
			this->_node_alloc.destroy(node);
			this->_node_alloc.deallocate(node, 1);
		}

		/**
		 * @brief Create a new node with data
		 * 
		 * @param x The data of the new node
		 * @return node_pointer the new node
		 */
		node_pointer	_new_node(const value_type &x)
		{
			node_pointer new_node = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(new_node, x);
			new_node->left = 0;
			new_node->right = 0;
			new_node->parent = 0;
			return new_node;
		}
	};

} /* namespace ft */


#endif /* RB_TREE_HPP */