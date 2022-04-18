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
	namespace ft = std;
#else
	#include "includes/vector.hpp"
	#include "ft_containers/containers/vector.hpp"
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
	std::cout
			//   << "front: " << v.front() << std::endl
			//   << "back: " << v.back() << std::endl
			  << "size: " << v.size() << std::endl
			  << "capacity: " << v.capacity() << std::endl
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
	ft::vector<int> v(10, 8);
	print(v);

	try
	{
		ft::vector<int>::iterator it = v.begin() + 1;
		v.insert(it, 42);
		print(v);
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}