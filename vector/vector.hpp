/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 08:04:32 by mbani             #+#    #+#             */
/*   Updated: 2021/07/06 16:13:46 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

namespace ft
{
template < class T, class Alloc = std::allocator<T> > 
class vector
{
	private:
		T *_ptr;
		size_t _size;
		size_t _capacity;
		Alloc  _alloc;
		/*	======================> private functions <============================  */
		void fatal_error()
		{
			std::cerr << "fatal error !" << std::endl;
			exit(1);
		}
		void allocate_arr(size_t n, const T& val)
		{
			this->_ptr = _alloc.allocate(n + 2);
			_alloc.construct(_ptr);
			_ptr[n + 1] = val;
			_ptr[0] = val;
			if (!_ptr)
				fatal_error();
			for(int i = 1 ; i <= n; i++)
				_ptr[i] = val;
			_size = n;
			_capacity = n;
		}
		template <class InputIterator>
		void allocate_range(InputIterator first, InputIterator last)
		{
			this->_ptr = _alloc.allocate(_size + 2);
			_alloc.construct(_ptr);
			_ptr[_size + 1] = *first;
			_ptr[0] = *first;
			if (!_ptr)
				fatal_error();
			int i = 1;
			for(; first != last ; first++)
			{
				_ptr[i] = *first;
				++i;
			}
		}
		void free_vect()
		{
			_alloc.deallocate(_ptr, _capacity + 2);
			_alloc.destroy(_ptr);
			_ptr = nullptr;
		}
	public:
		/*	======================> iterators classes <============================  */

				// Dereferencing start from 1 to n (included) 0 && n+1 reserved for rbegin and end
		
		/*	======================> typedef <============================  */
		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		#include "iterators.hpp"
		typedef iterators<T>							iterator;
		typedef iterators<const T>							const_iterator;
		// typedef rev_iter<node, T>		  					reverse_iterator;
		// typedef rev_iter<node, const T>						const_reverse_iterator;
		typedef  ptrdiff_t									difference_type;
		typedef  size_t										size_type;
		
		/*	======================> enable_if && is_integral implementation <============================  */
		template<typename> struct is_integral {static const bool value = false;};
		template<> struct is_integral<bool> {static const bool value = true;};
		template<> struct is_integral<char> {static const bool value = true;};
		template<> struct is_integral<signed char> {static const bool value = true;};
		template<> struct is_integral<short int> {static const bool value = true;};
		template<> struct is_integral<int> {static const bool value = true;};
		template<> struct is_integral<long int> {static const bool value = true;};
		template<> struct is_integral<long long int> {static const bool value = true;};
		template<> struct is_integral<unsigned char> {static const bool value = true;};
		template<> struct is_integral<unsigned short int> {static const bool value = true;};
		template<> struct is_integral<unsigned int> {static const bool value = true;};
		template<> struct is_integral<unsigned long int> {static const bool value = true;};
		template<> struct is_integral<unsigned long long int> {static const bool value = true;};

		template<bool Condition, typename TC = void>
		struct enable_if
		{
		};
		template<typename TC>
		struct enable_if<true, TC>
		{
			typedef TC type;
		};
		/*	======================> constructors  && descturtor <============================  */
		explicit vector (const allocator_type& alloc = allocator_type())
		{
			_size = 0;
			_capacity = 0;
			_ptr = nullptr;
		};
		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
		{
			_size = n;
			_capacity = n;
			allocate_arr(n, val);
		};
		template <class InputIterator>
         vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type(), 
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			if (first == last)
			{
				_size = 0;
				_capacity = 0;
				_ptr = nullptr;
				return;
			}
			_size = last - first;
			_capacity = _size;
			allocate_range(first, last);
		};

		vector (const vector& x)
		{
			//should allocate size of x not capacity ^_^
			if (x._capacity == 0)
			{
				_size = 0;
				_capacity = 0;
				_ptr = nullptr;
				return ;
			}
			allocate_range(x.begin(), x.end()); // should check if end index == capacity 
		}
		~vector()
		{
			if (this->_ptr)
				free_vect();
		}
		/*	======================> member functions <============================  */

		iterator begin(void)
		{
			if (_size != 0)
				return (iterator(&_ptr[1], _size, 1));
			return (iterator());
		}
		const_iterator begin(void) const
		{
			if (_size != 0)
				return (const_iterator(&_ptr[1], _size, 1));
			return (const_iterator());
		}
		iterator end(void)
		{
			if (_size != 0)
				return (iterator(&_ptr[_size + 1], _size, _size + 1));
			return (iterator());
		}
		// const_iterator end(void) const
		// {
		// 	if (this->_ptr)
		// 		return (const_iterator(_ptr, _size, _capacity));
		// 	return (const_iterator());
		// }
		size_type size() const
		{
			return (this->_size);
		}
		size_type max_size() const
		{
			return (_alloc.max_size());	
		}
		size_type capacity() const
		{
			return (this->_capacity);
		}
		bool empty() const
		{
			return (_size == 0);
		}
		void reserve (size_type n)
		{
			if (n > _capacity)
			{
				free_vect();
				std::cout << "entered\n";
				allocate_arr(n, T());
			}
		}
};

};