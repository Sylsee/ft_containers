/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 02:36:58 by spoliart          #+#    #+#             */
/*   Updated: 2022/05/06 17:38:45 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAITS_HPP
#define TRAITS_HPP

namespace ft
{

	/* ITERATORS_TRAITS */

	template<typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef T*								pointer;
		typedef T&								reference;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t					difference_type;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

	/* ENABLE_IF */

	template <bool B, class T = void>
	struct enable_if
	{};

	template <class T>
	struct enable_if<true, T>
	{ typedef T type; };

	/* IS_INTEGRAL */

	template <class T>
	struct is_integral
	{ enum { value = false }; };

	template <> struct is_integral<bool> { enum { value = true }; };

	template <> struct is_integral<char> { enum { value = true }; };

	template <> struct is_integral<wchar_t> { enum { value = true }; };

	template <> struct is_integral<signed char> { enum { value = true }; };

	template <> struct is_integral<short int> { enum { value = true }; };

	template <> struct is_integral<int> { enum { value = true }; };

	template <> struct is_integral<long int> { enum { value = true }; };

	template <> struct is_integral<long long int> { enum { value = true }; };

	template <> struct is_integral<unsigned char> { enum { value = true }; };

	template <> struct is_integral<unsigned short int> { enum { value = true }; };

	template <> struct is_integral<unsigned int> { enum { value = true }; };

	template <> struct is_integral<unsigned long int> { enum { value = true }; };

	template <> struct is_integral<unsigned long long int> { enum { value = true }; };

	/*  */

} // namespace ft

#endif /* TRAITS_HPP */