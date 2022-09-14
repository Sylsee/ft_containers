/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
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
	template<typename _Key, typename _Compare = std::less<_Key>,
			 typename _Alloc = std::allocator<_Key> > >
	class set
	{
	public:
		typedef _Key									 key_type;
		typedef _Key									 value_type;
		typedef _Compare								 key_compare;
		typedef _Alloc									 allocator_type;
		typedef typename allocator_type::reference		 reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer		 pointer;
		typedef typename allocator_type::const_pointer	 const_pointer;
		typedef ptrdiff_t								 difference_type;
		typedef size_t									 size_type;

		class value_compare
		: public std::binary_function<value_type, value_type, bool>
		{
			friend class set<_Key, _Compare, _Alloc>;

		protected:
			key_compare comp;

			value_compare(key_compare __c)
			: comp(__c) { }

		public:
			bool operator()(const value_type& __x, const value_type& __y) const
			{ return comp(__x, __y); }
		};

	private:
		typedef RB_Tree<value_type, value_compare, allocator_type>	_RB_Tree;

		_RB_Tree _tree;

	public:
		typedef typename _RB_Tree::iterator					 iterator;
		typedef typename _RB_Tree::const_iterator			 const_iterator;
		typedef typename _RB_Tree::reverse_iterator			 reverse_iterator;
		typedef typename _RB_Tree::const_reverse_iterator	 const_reverse_iterator;

		explicit set(const key_compare& comp = key_compare(),
					 const allocator_type& alloc = allocator_type())
		: _tree(comp, alloc)
		{ }

		set(const set& x)
		: _tree(x._tree)
		{ }

		template<typename _InputIterator>
		set(_InputIterator first, _InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: _tree(comp, alloc)
		{ _tree.insert_range(first, last); }

		~set()
		{ }

		set& operator=(const set& x)
		{
			_tree = x._tree;
			return *this;
		}

		allocator_type get_allocator() const
		{ return allocator_type(_tree.get_allocator()); }

		key_compare key_comp() const
		{ return key_compare(); }

		value_compare value_comp() const
		{ return value_compare(_tree.key_comp()); }

		inline iterator begin()
		{ return _tree.begin(); }

		inline const_iterator begin() const
		{ return _tree.begin(); }

		inline iterator end()
		{ return _tree.end(); }

		inline const_iterator end() const
		{ return _tree.end(); }

		inline reverse_iterator rbegin()
		{ return _tree.rbegin(); }

		inline const_reverse_iterator rbegin() const
		{ return _tree.rbegin(); }

		inline reverse_iterator rend()
		{ return _tree.rend(); }

		inline const_reverse_iterator rend() const
		{ return _tree.rend(); }

		inline bool empty() const
		{ return _tree.empty(); }

		inline size_type size() const
		{ return _tree.size(); }

		inline size_type max_size() const
		{ return _tree.max_size(); }

		mapped_type& operator[](const key_type& k)
		{
			iterator it = lower_bound(k);
			if (it == end() || key_comp()(k, *it))
				it = insert(it, k);
			return *it;
		}

		mapped_type& at(const key_type& k)
		{
			iterator it = lower_bound(k);
			if (it == end() || key_comp()(k, *it))
				throw std::out_of_range("set::at out of range");
			return *it;
		}

		const mapped_type& at(const key_type& k) const
		{
			const_iterator it = lower_bound(k);
			if (it == end() || key_comp()(k, *it))
				throw std::out_of_range("set::at out of range");
			return *it;
		}

		void erase(iterator pos)
		{ _tree.erase(pos); }

		size_type erase(const key_type& k)
		{ return (_tree.erase(k)); }

		void erase(iterator first, iterator last)
		{ _tree.erase(first, last); }

		void clear()
		{ _tree.clear(); }

		iterator lower_bound(const key_type& k)
		{ return _tree.lower_bound(k); }

		const_iterator lower_bound(const key_type& k) const
		{ return _tree.lower_bound(k); }

		iterator upper_bound(const key_type& k)
		{ return _tree.upper_bound(k); }

		const_iterator upper_bound(const key_type& k) const
		{ return _tree.upper_bound(k); }

		void swap(set& x)
		{ _tree.swap(x._tree); }

		ft::pair<iterator, bool> insert(const value_type& value)
		{ return _tree.insert(value); }

		iterator insert(iterator pos, const value_type& value)
		{ return _tree.insert(pos, value); }

		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last)
		{ _tree.insert_range(first, last); }

		size_type count(const key_type& k) const
		{ return _tree.find(k) != _tree.end(); }

		iterator find(const key_type& k)
		{ return _tree.find(k); }

		const_iterator find(const key_type& k) const
		{ return _tree.find(k); }

		ft::pair<iterator, iterator> equal_range(const key_type& k)
		{ return _tree.equal_range(k); }

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{ return _tree.equal_range(k); }

		template<typename Key, typename Compare, typename Alloc>
		friend bool operator==(const set<Key, Compare, Alloc>&,
							   const set<Key, Compare, Alloc>&);

		template<typename Key, typename Compare, typename Alloc>
		friend bool operator<(const set<Key, Compare, Alloc>& lhs,
							  const set<Key, Compare, Alloc>& rhs);

	};

	template<typename Key, typename Compare, typename Alloc>
	inline void swap(set<Key, Compare, Alloc>& lhs,
					 set<Key, Compare, Alloc>& rhs)
	{ lhs.swap(rhs); }

	template<typename Key, typename Compare, typename Alloc>
	inline bool operator==(const set<Key, Compare, Alloc>& lhs,
						   const set<Key, Compare, Alloc>& rhs)
	{ return lhs._tree == rhs._tree; }

	template<typename Key, typename Compare, typename Alloc>
	inline bool operator<(const set<Key, Compare, Alloc>& lhs,
						  const set<Key, Compare, Alloc>& rhs)
	{ return lhs._tree < rhs._tree; }

	template<typename Key, typename Compare, typename Alloc>
	inline bool operator!=(const set<Key, Compare, Alloc>& lhs,
						   const set<Key, Compare, Alloc>& rhs)
	{ return !(lhs == rhs); }

	template<typename Key, typename Compare, typename Alloc>
	inline bool operator>(const set<Key, Compare, Alloc>& lhs,
						  const set<Key, Compare, Alloc>& rhs)
	{ return rhs < lhs; }

	template<typename Key, typename Compare, typename Alloc>
	inline bool operator<=(const set<Key, Compare, Alloc>& lhs,
						   const set<Key, Compare, Alloc>& rhs)
	{ return !(rhs < lhs); }

	template<typename Key, typename Compare, typename Alloc>
	inline bool operator>=(const set<Key, Compare, Alloc>& lhs,
						   const set<Key, Compare, Alloc>& rhs)
	{ return !(lhs < rhs); }


} /* namespace ft */


#endif /* MAP_HPP */