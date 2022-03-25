/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:06:17 by spoliart          #+#    #+#             */
/*   Updated: 2022/03/25 20:01:44 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>

int main( void )
{
	std::vector<int> v(2305, 10);

	std::cout << "v.size(): " << v.size() << std::endl;
	std::cout << "v.capacity(): " << v.capacity() << std::endl << std::endl;

	v.clear();

	std::cout << "v.size(): " << v.size() << std::endl;
	std::cout << "v.capacity(): " << v.capacity() << std::endl << std::endl;

	return 0;
}
