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
#include <traits.hpp>

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
		: data(NULL),
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

	template<typename _Tp, typename _Compare = std::less<_Tp>,
			 typename _Alloc = std::allocator<_Tp> >
	class RB_Tree
	{
	protected:
		typedef Node<_Tp>	_Node;

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

		RB_Tree(const value_compare &comp = value_compare(),
				const allocator_type &a = allocator_type())
		: _val_alloc(a),
		  _node_alloc(node_allocator()),
		  _comp(comp),
		  _size(0)
		{
			this->_root = 0;
			this->_header = this->_node_alloc.allocate(1);
			this->_node_alloc.construct(this->_header, _Node());
		}

		~RB_Tree()
		{
			_destroy(this->_root);
			_delete_node(this->_header);
		}

		void	insert(const value_type &x)
		{
			pair<node_pointer, node_pointer> pos = 
				_insert_unique_pos(x);
			node_pointer new_node = _new_node(x);

			if (_is_nill(this->_root))
				this->_root = new_node;
			else
			{
				node_pointer __tmp = _insert_unique_pos(x);
				if (__tmp == NULL)
				{
					_delete_node(new_node);
					return ;
				}

				new_node->parent = __tmp;
				if (_comp(*__tmp->data, *new_node->data))
					__tmp->right = new_node;
				else if (_comp(*new_node->data, *__tmp->data))
					__tmp->left = new_node; 
				new_node->color = RED;

				// _rebalance_insertion(new_node);
			}
		}

		/**
		 * @brief Get the minimum node from a node
		 * 
		 * @param node The node where to start the search
		 * @return node_pointer the minimum node
		 */
		node_pointer min(node_pointer node = NULL) const
		{ return _min(node == NULL ? this->_root : node); }

		/**
		 * @brief Get the maximum node from a node
		 * 
		 * @param node The node where to start the search
		 * @return node_pointer the maximum node
		 */
		node_pointer max(node_pointer node = NULL) const
		{ return _max(node == NULL ? this->_root : node); }

		/**
		 * @brief Get node from a value
		 * 
		 * @param value The value to search
		 * @param node The node where to start the search
		 * @return iterator the iterator of the node
		 */
		iterator find(const value_type& value, node_pointer node = NULL) const
		{
			if (node == NULL)
				node = this->_root;
			while (!_is_nill(node))
			{
				if (_comp(value, *node->data))
					node = node->left;
				else if (_comp(*node->data, value))
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
			while (node != 0)
			{
				if (_comp(value, *node->data))
					node = node->left;
				else if (_comp(*node->data, value))
					node = node->right;
				else
					break;
			}
			if (node == 0)
				return NULL;
			return iterator(node);
		}

		size_type count(node_pointer node = NULL) const
		{
			if (node == NULL)
				node = this->_root;
			if (node == 0)
				return 0;

			size_type nb_node = 1;
			nb_node += count(node->left);
			nb_node += count(node->right);

			return nb_node;
		}

		void	display() const
		{ _display(this->_root, "", true); }

	protected:
		allocator_type	_val_alloc;
		node_allocator	_node_alloc;
		value_compare	_comp;
		node_pointer	_root;
		node_pointer	_header;
		size_type		_size;

		/**
		 * @brief Fix the height of the tree after an insertion
		 * 
		 * @param node The node inserted
		 */
		void	_rebalance_insertion(node_pointer node)
		{ (void)node; }

		/**
		 * @brief Find the position to insert a node
		 * 
		 * @param new_val The value of the node to insert
		 * @return node_pointer the position to insert
		 */
		node_pointer	_insert_unique_pos(const value_type& new_val)
		{
			typedef ft::pair<node_pointer, node_pointer> res;
			node_pointer __x = this->_root;
			node_pointer __y;
			bool comp = true;

			while (__x != 0)
			{
				__y = __x;
				comp = _comp(new_val, *__x->data);
				__x = comp ? __x->left : __x->right;
			}
			iterator __it = iterator(__y);
			if (comp)
			{
				if (it == begin())
					return res(__x, __y);
				else
					--it;
			}
			if (_comp(*it, new_val))
				return res(__x, __y);
			return res(it.node, 0);
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
		 * @brief Check if the node is nill
		 * 
		 * @param node The node to check
		 * @return true if the node is nill, else false
		 */
		inline bool _is_nill(const node_pointer node) const
		{ return (node == NULL || node == this->_header); }

		/**
		 * @brief Destroy and deallocate the node
		 * 
		 * @param node The node to delete
		 */
		inline void _delete_node(node_pointer node)
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
			if (_is_nill(node))
				return ;

			_destroy(node->left);
			_destroy(node->right);
			_delete_node(node);
		}

		void	_rotate_left(node_pointer node)
		{
			if (_is_nill(node) || _is_nill(node->parent))
				return ;

			node_pointer parent = node->parent;

			parent->right = node->left;
			node->parent = parent->parent;
			parent->parent = node;
			node->left = parent;
		}

		void	_rotate_right(node_pointer node)
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
				std::cout << *root->data << "(" << sColor << ")" << std::endl;
				_display(root->left, indent, false);
				_display(root->right, indent, true);
			}
		}

		inline pointer _new_value(const value_type &x)
		{
			pointer new_val = this->_val_alloc.allocate(1);
			this->_val_alloc.construct(new_val, x);
			return new_val;
		}

		inline node_pointer	_new_node(const value_type &x)
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