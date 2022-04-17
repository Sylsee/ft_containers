/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:18:16 by spoliart          #+#    #+#             */
/*   Updated: 2022/04/06 20:21:56 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <sstream>

namespace ft
{
	template < typename T >
	std::string to_string(T n)
	{
		std::ostringstream ss;
		ss << n;
		return ss.str();
	}

	/**
	 * @brief Swap two elements
	 *
	 * @param a The first element
	 * @param b The second element
	 */
	template < typename T >
	void swap(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

}

#endif /* UTILS_HPP */
