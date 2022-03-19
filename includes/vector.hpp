/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoliart <spoliart@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:26:07 by spoliart          #+#    #+#             */
/*   Updated: 2022/03/19 18:48:29 by spoliart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft
{

    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
 
    private:

	/* Attributes */
		T				*_array;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_alloc;
 
    public:

    /* Member types */
        typedef T                                            value_type;
        typedef Alloc                                        allocator_type;
        typedef typename allocator_type::reference           reference;
        typedef typename allocator_type::const_reference     const_reference;
        typedef typename allocator_type::pointer             pointer;
        typedef typename allocator_type::const_pointer       const_pointer;
        typedef typename allocator_type::difference_type     difference_type;
        typedef typename allocator_type::size_type           size_type;
        typedef ft::random_access_iterator<value_type>       iterator;
        typedef ft::random_access_iterator<const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator>               reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;

    /* Constructor */
        explicit vector (const allocator_type& alloc = allocator_type()) :
			_alloc(alloc),
			_size(0),
			_capacity(0),
			_array(NULL)
        {}

        explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
        {}

        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type())
        {}

        vector (const vector& x)
        {}
 
    /* Destructor */
    
        vector::~vector()
        {
            ;
        }

    };
    
} // namespace ft


#endif /* VECTOR_HPP */