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

namespace ft
{
	enum node_color { BLACK = true, RED = false }

	template<typename _Tp>
	typedef struct	node
	{
		typedef typename _Tp	value_type;

		value_type	value;
		bool		color;
		node		*parent;
		node		*left;
		node		*right;
	}				node;
	

	template<typename _Tp>
	class RB_Tree
	{
	private:
		typedef typename node<_Tp>

		__node	_root;
		__node	

	public:

		RB_Tree()
		: _root(),
		  _
		{
		}

		~RB_Tree()
		{
		}

	};
	
	
} /* namespace ft */


#endif /* RB_TREE_HPP */