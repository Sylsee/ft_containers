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
	#include <set>
	#include <map>
	#include <stack>
	#include <vector>
	#include <iterator>
	namespace ft = std;
#else
	#include <map.hpp>
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
typedef ft::map<int, std::string>::value_type val_type;
typedef ft::map<int, std::string>::iterator iterator;

int main(void)
{
	try
	{
		// std::cout << "Hello" << std::endl;

		ft::map<int, std::string> m;

		m.insert(ft::pair<int, std::string>(1, "salut"));
		m.insert(ft::pair<int, std::string>(2, "salut"));
		m.insert(ft::pair<int, std::string>(3, "salut"));
		m.insert(ft::pair<int, std::string>(4, "salut"));

		ft::map<int, std::string>::iterator s = m.find(2);

		for (; s != m.end(); ++s)
			std::cout << (*s).first << " " << (*s).second << std::endl;

		std::cout << std::endl << std::endl;

		for (iterator it = m.begin(); it != m.end(); ++it)
			std::cout << (*it).first << " " << (*it).second << std::endl;
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