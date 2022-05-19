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

#ifdef STD
	#include <map>
	#include <stack>
	#include <vector>
	#include <iterator>
	// #include <type_traits>
	namespace ft = std;
#else
	#include <vector.hpp>
	#include <stack.hpp>
	#include <iterator.hpp>
	#include <traits.hpp>
	#include <utils.hpp>
	#include <RB_Tree.hpp>
	#include <RB_Tree_iterator.hpp>
#endif
// #include <typeinfo>

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

#define SIZE 11

int main(void)
{
	try
	{
		ft::RB_Tree<int> t;

		t.insert(40);
		t.insert(2);
		t.insert(4);
		// t.insert(6);
		// t.insert(5);
		// t.insert(6);
		t.display();
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}