/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:17 by spoliart          #+#    #+#             */
/*   Updated: 2022/04/15 23:27:17 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef FT // CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "includes/vector.hpp"
	// #include "ft_containers/containers/vector.hpp"
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

#define SIZE 11

template < typename T >
void print(ft::vector< T >& v)
{
	std::cout << "front: " << v.front() << std::endl
			  << "back: " << v.back() << std::endl
			  << "size: " << v.size() << std::endl
			  << "capacity: " << v.capacity() << std::endl
			  << "empty: " << v.empty() << std::endl
			  << "max_size: " << v.max_size() << std::endl;
#ifndef NO_DISPLAY_ADDRESS
	std::cout << "address: " << &v << std::endl;
#endif

	std::cout << "content: [";
	size_t max = v.size();
	for (size_t i = 0; i < max; i++) {
		std::cout << v[i];
		if (i < max - 1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl << std::endl;
}

int main(void)
{
	ft::vector<int> v(2, 8);
	print(v);

	try
	{
		v.pop_back();
		print(v);
		v.pop_back();
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}
	print(v);
 
	for (int i = 0; i < 1; i++)
		v.push_back(i);
	print(v);

	return 0;
}