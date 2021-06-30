/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 08:04:32 by mbani             #+#    #+#             */
/*   Updated: 2021/06/30 12:33:32 by mbani            ###   ########.fr       */
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
		}
		template <class InputIterator>
		void allocate_range(InputIterator first, InputIterator last)
		{
			this->_ptr = _alloc.allocate((last - first) + 2);
			_alloc.construct(_ptr);
			_ptr[(last - first) + 1] = *first;
			_ptr[0] = *first;
			if (!_ptr)
				fatal_error();
			int i = 1;
			for(; first < last ; first++)
			{
				_ptr[i] = *first;
				++i;
			}
		}
	public:
		/*	======================> iterators classes <============================  */
		// #include "iterators.hpp"

				// Dereferencing start from 1 to n (included) 0 && n+1 reserved for rbegin and end
		
		/*	======================> typedef <============================  */
		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		// typedef iterators<node, T>							iterator;
		// typedef iterators< node, const T>					const_iterator;
		// typedef rev_iter<node, T>		  					reverse_iterator;
		// typedef rev_iter<node, const T>						const_reverse_iterator;
		typedef  ptrdiff_t									difference_type;
		typedef  size_t										size_type;	

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


		// template <typename TY>static const bool is_int(TY){return false;}
		// template<>static const bool is_int<int>(int){return true;}
		// template<>static const bool is_int<bool> (bool){return true;};
		// template<>static const bool is_int<char> (char){return true;};
		// template<>static const bool is_int<signed char>(signed char) {return true;};
		// template<>static const bool is_int<short int> (short int){return true;};
		// template<>static const bool is_int<long int> (long int){return true;};
		// template<>static const bool is_int<long long int> (long long int){return true;};
		// template<>static const bool is_int<unsigned char> (unsigned char){return true;};
		// template<>static const bool is_int<unsigned short int> (unsigned short int){return true;};
		// template<>static const bool is_int<unsigned int> (unsigned int){return true;};
		// template<>static const bool is_int<unsigned long int> (unsigned long int){return true;};
		// template<>static const bool is_int<unsigned long long int> (unsigned long long int){return true;};
template<typename> struct is_int {
		static const bool value = false;
	};
	template<> struct is_int<bool> {static const bool value = true;};
	template<> struct is_int<char> {static const bool value = true;};
	template<> struct is_int<signed char> {static const bool value = true;};
	template<> struct is_int<short int> {static const bool value = true;};
	template<> struct is_int<int> {static const bool value = true;};
	template<> struct is_int<long int> {static const bool value = true;};
	template<> struct is_int<long long int> {static const bool value = true;};
	template<> struct is_int<unsigned char> {static const bool value = true;};
	template<> struct is_int<unsigned short int> {static const bool value = true;};
	template<> struct is_int<unsigned int> {static const bool value = true;};
	template<> struct is_int<unsigned long int> {static const bool value = true;};
	template<> struct is_int<unsigned long long int> {static const bool value = true;};
	// template<bool Cond, class T1 = void> struct enable_if {};
	// template<class T1> struct enable_if<true, T1> { typedef T1 type; };

		template<bool Condition, typename TC = void>
		struct enable_if
		{
		};
		template<typename TC>
		struct enable_if<true, TC>
		{
			typedef TC type;
		};
	
		template <class InputIterator>
         vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type(), 
				typename enable_if<!is_int<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			std::cout << "called" << std::endl;
			if (first == last)
			{
				_size = 0;
				_capacity = 0;
				_ptr = nullptr;
				return;
			}
			allocate_range(first, last);
			
		};







};

};