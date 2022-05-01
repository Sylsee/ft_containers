/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:17 by spoliart          #+#    #+#             */
/*   Updated: 2022/04/18 15:39:04 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef STD
	#include <map>
	#include <stack>
	#include <vector>
	#include <iterator>
	#include <type_traits>
	namespace ft = std;
#else
	#include "includes/vector.hpp"
	#include "includes/iterator.hpp"
	#include "includes/traits.hpp"
	#include "includes/utils.hpp"
#endif
#include <typeinfo>

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

template < typename T >
void print(ft::vector< T >& v)
{
	std::cout
			//   << "front: " << v.front() << std::endl
			//   << "back: " << v.back() << std::endl
			  << "size: " << v.size() << std::endl
			  << "capacity: " << v.capacity() << std::endl
			  << "max_size: " << v.max_size() << std::endl
			  << "empty: " << v.empty() << std::endl;
#ifndef NO_DISPLAY_ADDRESS
	std::cout << "address: " << &v[0] << std::endl;
#endif

	std::cout << "content: [";
	for (typename ft::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << *it;
		if (it != v.end() - 1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl << std::endl;
}

int main(void)
{
	try
	{
		ft::vector<int> v(10, 8);
		print(v);

		ft::vector<int>::iterator it = v.begin() + 2;
		ft::vector<int>::iterator it2(it);

		// std::cout << it.base() << std::endl;
		it = v.erase(it, it2);
		while (it != v.end()){
			std::cout << *it << std::endl;
			it++;
		}
		print(v);
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}