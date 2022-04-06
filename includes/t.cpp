/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:17 by spoliart          #+#    #+#             */
/*   Updated: 2022/04/06 20:48:14 by spoliart         ###   ########.fr       */
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

int main( void )
{
	ft::vector<int> v(SIZE, 10);

	std::cout << "v.back(): " << v.back() << std::endl;
	std::cout << "v.front(): " << v.front() << std::endl;
	std::cout << "v.size(): " << v.size() << std::endl;
	std::cout << "v.capacity(): " << v.capacity() << std::endl;
	std::cout << "v.max_size(): " << v.max_size() << std::endl;

	for (int i = 0; i < SIZE; i++)
		std::cout << v[i] << std::endl;

	std::cout << std::endl;

	v.clear();

	std::cout << "v.back(): " << v.back() << std::endl;
	std::cout << "v.front(): " << v.front() << std::endl;
	std::cout << "v.size(): " << v.size() << std::endl;
	std::cout << "v.capacity(): " << v.capacity() << std::endl;
	std::cout << "v.max_size(): " << v.max_size() << std::endl;
	
	for (int i = 0; i < SIZE + 1; i++)
		std::cout << v[i] << std::endl;

	return 0;
}
