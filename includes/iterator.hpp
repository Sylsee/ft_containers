#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{

	/**
	 * @brief Iterator class for 
	 *
	 * @tparam T The type of the iterator
	 */
	template <typename T>
	struct random_access_iterator
	{
	public:
		/**
		 * @brief Default constructor
		 */
		random_access_iterator(void) : _ptr(NULL){};

		/**
		 * @brief Assignment operator
		 *
		 * @param ptr The pointer to assign
		 */
		random_access_iterator(T *ptr) : _ptr(ptr){};

		/**
		 * @brief Copy constructor
		 *
		 * @param other The iterator to copy
		 */
		random_access_iterator(const random_access_iterator &other) : _ptr(other._ptr){};

		/**
		 * @brief Destructor
		 */
		~random_access_iterator(void){};

		/**
		 * @brief Assignment operator
		 *
		 * @param rhs The iterator to assign
		 * @return iterator& The iterator
		 */
		random_access_iterator &operator=(const random_access_iterator &rhs)
		{
			if (this != &rhs)
				this->_ptr = rhs._ptr;
			return (*this);
		}

		/**
		 * @brief Equality operator
		 *
		 * @param rhs The iterator to compare
		 * @return bool True if the iterators are equal
		 */
		bool operator==(const random_access_iterator &rhs) const
		{
			return (this->_ptr == rhs._ptr);
		}

		/**
		 * @brief Inequality operator
		 *
		 * @param rhs The iterator to compare
		 * @return bool True if the iterators are not equal
		 */
		bool operator!=(const random_access_iterator &rhs) const
		{
			return (this->_ptr != rhs._ptr);
		}

		/**
		 * @brief Dereference operator
		 *
		 * @return T& The value
		 */
		T &operator*(void) const
		{
			return (*this->_ptr);
		}

		/**
		 * @brief Arrow operator
		 *
		 * @return T* The pointer
		 */
		T *operator->(void) const
		{
			return (this->_ptr);
		}

		/**
		 * @brief Assignment operator
		 *
		 * @param rhs The value to assign
		 * @return T& The value
		 */
		T &operator=(T &rhs)
		{
			*this->_ptr = rhs;
			return (*this);
		}

		/**
		 * @brief Pre-increment operator
		 *
		 * @return iterator& The iterator
		 */
		random_access_iterator &operator++(void)
		{
			this->_ptr++;
			return (*this);
		}

		/**
		 * @brief Post-increment operator
		 *
		 * @return iterator& The iterator
		 */
		random_access_iterator operator++(int)
		{
			random_access_iterator tmp = *this;
			this->_ptr++;
			return (tmp);
		}

		/**
		 * @brief Pre-decrement operator
		 *
		 * @return iterator& The iterator
		 */
		random_access_iterator &operator--(void)
		{
			this->_ptr--;
			return (*this);
		}

		/**
		 * @brief Post-decrement operator
		 *
		 * @return iterator& The iterator
		 */
		random_access_iterator operator--(int)
		{
			random_access_iterator tmp = *this;
			this->_ptr--;
			return (tmp);
		}

		/**
		 * @brief Give a iterator where the element
		 * is pointed at this + "n" in memory.
		 *
		 * @param n The number of elements to add
		 * @return iterator& The iterator
		 */
		random_access_iterator operator+(const int &n) const
		{
			return (this->_ptr + n);
		}

		/**
		 * @brief Give a iterator where the element
		 * is pointed at this - "n" in memory.
		 *
		 * @param n The number of elements to subtract
		 * @return random_access_iterator The iterator
		 */
		random_access_iterator operator-(const int &n) const
		{
			return (this->_ptr - n);
		}

		unsigned long operator-(const random_access_iterator &rhs) const
		{
			return (this->_ptr - rhs._ptr);
		}
	
		unsigned long operator+(const random_access_iterator &rhs) const
		{
			return (this->_ptr + rhs._ptr);
		}

		/**
		 * @brief Inferior operator
		 *
		 * @param rhs The operator to compare
		 * @return true if the iterator is inferior
		 * @return false if the iterator is superior
		 */
		bool operator<(const random_access_iterator &rhs) const
		{
			return (this->_ptr < rhs._ptr);
		}

		/**
		 * @brief Superior operator
		 *
		 * @param rhs The operator to compare
		 * @return true if the iterator is superior
		 * @return false if the iterator is inferior
		 */
		bool operator>(const random_access_iterator &rhs) const
		{
			return (this->_ptr > rhs._ptr);
		}

		/**
		 * @brief Inferior or equal operator
		 *
		 * @param rhs The operator to compare
		 * @return true if the iterator is inferior or equal
		 * @return false if the iterator is superior
		 */
		bool operator<=(const random_access_iterator &rhs) const
		{
			return (this->_ptr <= rhs._ptr);
		}

		/**
		 * @brief Superior or equal operator
		 *
		 * @param rhs The operator to compare
		 * @return true if the iterator is superior or equal
		 * @return false if the iterator is inferior
		 */
		bool operator>=(const random_access_iterator &rhs) const
		{
			return (this->_ptr >= rhs._ptr);
		}

		/**
		 * @brief Give a reference to this random access iterator
		 * where the element pointed is at the actual pointer memory
		 * plus "n".
		 *
		 * @param n The number of elements to add
		 * @return random_access_iterator& The iterator
		 */
		random_access_iterator &operator+=(const int &n)
		{
			this->_ptr += n;
			return (*this);
		}

		/**
		 * @brief Give a reference to this random access iterator
		 * where the element pointed is at the actual pointer memory
		 * minus "n".
		 *
		 * @param n The number of elements to subtract
		 * @return random_access_iterator& The iterator
		 */
		random_access_iterator &operator-=(const int &n)
		{
			this->_ptr -= n;
			return (*this);
		}

		/**
		 * @brief Dereference operator
		 *
		 * @param i The index
		 * @return T& The value at the index
		 */
		T &operator[](const int &i) const
		{
			return (this->_ptr[i]);
		}

	private:
		template <typename T_L, typename T_R>
		friend bool operator==(const random_access_iterator<T_L> &, const random_access_iterator<T_R> &);

		template <typename T_L, typename T_R>
		friend bool operator!=(const random_access_iterator<T_L> &, const random_access_iterator<T_R> &);

		template <typename T_L, typename T_R>
		friend bool operator<(const random_access_iterator<T_L> &, const random_access_iterator<T_R> &);

		template <typename T_L, typename T_R>
		friend bool operator>(const random_access_iterator<T_L> &, const random_access_iterator<T_R> &);

		template <typename T_L, typename T_R>
		friend bool operator<=(const random_access_iterator<T_L> &, const random_access_iterator<T_R> &);

		template <typename T_L, typename T_R>
		friend bool operator>=(const random_access_iterator<T_L> &, const random_access_iterator<T_R> &);

		friend random_access_iterator operator+(const int &, const random_access_iterator &);

		friend random_access_iterator operator-(const int &, const random_access_iterator &);

		T *_ptr;
	};

	template <typename T_L, typename T_R>
	bool operator==(const ft::random_access_iterator<T_L> &lhs, const ft::random_access_iterator<T_R> &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template <typename T_L, typename T_R>
	bool operator!=(const ft::random_access_iterator<T_L> &lhs, const ft::random_access_iterator<T_R> &rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}

	template <typename T_L, typename T_R>
	bool operator<(const ft::random_access_iterator<T_L> &lhs, const ft::random_access_iterator<T_R> &rhs)
	{
		return (lhs._ptr < rhs._ptr);
	}

	template <typename T_L, typename T_R>
	bool operator<=(const ft::random_access_iterator<T_L> &lhs, const ft::random_access_iterator<T_R> &rhs)
	{
		return (lhs._ptr <= rhs._ptr);
	}

	template <typename T_L, typename T_R>
	bool operator>(const ft::random_access_iterator<T_L> &lhs, const ft::random_access_iterator<T_R> &rhs)
	{
		return (lhs._ptr > rhs._ptr);
	}

	template <typename T_L, typename T_R>
	bool operator>=(const ft::random_access_iterator<T_L> &lhs, const ft::random_access_iterator<T_R> &rhs)
	{
		return (lhs._ptr >= rhs._ptr);
	}

	template <typename T>
	ft::random_access_iterator<T> operator+(const int &lhs, const ft::random_access_iterator<T> &rhs)
	{
		return (ft::random_access_iterator<T>(lhs + rhs._ptr));
	}

	template <typename T>
	ft::random_access_iterator<T> operator-(const int &lhs, const ft::random_access_iterator<T> &rhs)
	{
		return (ft::random_access_iterator<T>(lhs - rhs._ptr));
	}

	/* Reverse iterator */

	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator iterator_type;
		typedef iterator_traits<Iterator>::iterator_category iterator_category;
		typedef iterator_traits<Iterator>::value_type value_type;
		typedef iterator_traits<Iterator>::difference_type difference_type;
		typedef iterator_traits<Iterator>::pointer pointer;
		typedef iterator_traits<Iterator>::reference reference;

		reverse_iterator() : _ptn()
		{}

		explicit reverse_iterator(iterator_type it) : _ptn(it)
		{}

		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) : _ptn(rev_it._ptn)
		{}

		iterator_type base() const
		{
			return this->_ptn;
		}

		reference operator*() const
		{
			iterator_type tmp(*this);
			return *(--tmp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->_ptn - n);
		}

		reverse_iterator& operator++(void)
		{
			--this->_ptn;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			iterator_type tmp(*this);
			++(*this);
			return tmp;
		}

		reverse_iterator& operator+=(difference_type n)
		{
			this->_ptn -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->_ptn + n);
		}

		reverse_iterator& operator--(void)
		{
			++this->_ptn;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			iterator_type tmp(*this);
			--(*this);
			return tmp;
		}

		reverse_iterator& operator-=(difference_type n)
		{
			this->_ptn += n;
			return *this;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return this->base()[-n - 1];
		}

	private:
		iterator_type _ptn;
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs,
				    const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs,
				    const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs,
				   const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs,
				   const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs,
				   const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs,
				   const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() - rhs.base());
	}

}

#endif /* ITERATOR_HPP */