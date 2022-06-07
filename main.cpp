/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:17 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/07 14:00:24 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>
#include <bits/stl_tree.h>

#ifdef STD
	#include <map>
	#include <stack>
	#include <vector>
	#include <iterator>
	namespace ft = std;
#else
	#include <vector.hpp>
	#include <stack.hpp>
	#include <iterator.hpp>
	#include <traits.hpp>
	#include <utils.hpp>
	#include <RB_Tree.hpp>
#endif

class Test
{
public:
	int i;
	Test(void) : i(10) {};
	Test(int i) : i(i) {};
	~Test(void) {};
};

std::ostream&	operator<<(std::ostream& o, const Test& t)
{
	o << t.i;
	return o;
}

#define SIZE 5

int main(void)
{
	try
	{


		// typedef std::pair<const int, u_int8_t> pair;
		// typedef std::_Rb_tree<int, pair, std::_Select1st<pair>, std::less<int> > tree;
		// tree t;
		// srand(time(NULL));
		// for (size_t i = 0; i < SIZE; ++i) {
		// 	int x = rand() % 100000000;
		// 	t._M_insert_unique(pair(i, x));
		// }

		// tree t1;
		// for (size_t i = 0; i < SIZE; ++i) {
		// 	int x = rand() % 100000000;
		// 	t1._M_insert_unique(pair(i, x));
		// }

		// t1 = t;

		typedef ft::RB_Tree<int> tree;
		ft::RB_Tree<int> t;
		srand(time(NULL));
		for (int i = 0; i < SIZE; ++i) {
			// int x = rand() % 100000000;
			// std::cout << x << " ";
			t.insert(i);
		}
		// std::cout << std::endl;
		// t.print_tree();
		// std::cout << std::endl;

		ft::RB_Tree<int> t1;
		t1 = t;
		// t1.print_tree();

		std::cout << "t: [";
		for (tree::iterator it = t.begin(); it != t.end(); ++it)
			std::cout << *it << ", ";
		std::cout << "]" << std::endl;

		std::cout << "t1: [";
		for (tree::iterator it = t1.begin(); it != t1.end(); ++it)
			std::cout << *it << ", ";
		std::cout << "]" << std::endl;
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
/**
 * header == root->parent
 * header->right == right_most
 * header->left == left_most
 * header->parent == root
 * 
 */
		/*
		typedef std::pair<const int, u_int8_t> pair;
		typedef std::_Rb_tree<int, pair, std::_Select1st<pair>, std::less<int> > tree;

		tree t;

		srand(time(NULL));
		for (size_t i = 0; i < SIZE; ++i) {
			t._M_insert_unique(pair(rand() % 50, rand() % 25 + 'a'));
		}
		tree::iterator it = t.begin();
		while (it != t.end()) {
			std::cout << it._M_node << ": " << (*it).first << std::endl;
			++it;
		}
		*/