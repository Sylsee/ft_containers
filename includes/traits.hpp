/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 02:36:58 by spoliart          #+#    #+#             */
/*   Updated: 2022/04/17 02:37:10 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
# define TRAITS_HPP

namespace ft
{

    /* ENABLE_IF */

	template < bool B, class T = void >
	struct enable_if {};

	template < class T >
	struct enable_if<true, T> { typedef T type; };

    /* IS_INTEGRAL */

    template <class T>
    struct is_integral {
        enum { value = false };
    };

    template <>
    struct is_integral<bool> {
        enum { value = true };
    };

    template <>
    struct is_integral<char> {
        enum { value = true };
    };

} // namespace ft


#endif /* TRAITS_HPP */