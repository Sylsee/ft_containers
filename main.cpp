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

#ifndef STD
	#include <map>
	#include <stack>
	#include <vector>
	#include <iterator>
	// #include <type_traits>
	namespace ft = std;
#else
	#include "includes/vector.hpp"
	#include "includes/stack.hpp"
	#include "includes/iterator.hpp"
	#include "includes/traits.hpp"
	#include "includes/utils.hpp"
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
		ft::map<int, std::string> m;

		for (int i = 0; i < 20; i++)
			m.insert(std::make_pair(i, std::to_string(i) + 'a'));

		typedef ft::map<int, std::string>::iterator iterator;
		for (iterator it = m.begin(); it != m.end(); it++)
			std::cout << "key: " << it->first << " second: " << it->second << std::endl;
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}