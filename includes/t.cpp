/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:17 by spoliart          #+#    #+#             */
/*   Updated: 2022/04/09 17:23:01 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

#define SIZE 10

void	print(ft::vector<int> v)
{
	void	*ptr = &v[0];
	std::cout << ptr << std::endl
		<< "v.back(): " << v.back() << std::endl
		<< "v.front(): " << v.front() << std::endl
		<< "v.size(): " << v.size() << std::endl
		<< "v.capacity(): " << v.capacity() << std::endl
		<< "v.max_size(): " << v.max_size() << std::endl;

	size_t	max = v.size();
	for (size_t i = 0; i < max && i < 30; i++)
		std::cout << v[i] << std::endl;
	std::cout << std::endl;
}

int main(void)
{
	ft::vector<int> v(SIZE, 10);
	print(v);

	try
	{
		v.assign(5, 2);
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
