/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 08:04:32 by mbani             #+#    #+#             */
/*   Updated: 2021/07/10 19:48:38 by mbani            ###   ########.fr       */
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
			/* 
						DOES NOT SET SIZE && CAPACITY 

			*/
			
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
			if (_capacity != 0)
				return (iterator(&_ptr[1], _size, 1));
			return (iterator());
		}
		const_iterator begin(void) const
		{
			if (_capacity != 0)
				return (const_iterator(&_ptr[1], _size, 1));
			return (const_iterator());
		}
		iterator end(void)
		{
			if (_capacity != 0)
				return (iterator(&_ptr[_size + 1], _size, _size + 1));
			return (iterator());
		}
		const_iterator end(void) const
		{
			if (_capacity != 0)
				return (const_iterator(_ptr, _size, _capacity));
			return (const_iterator());
		}
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
				vector<T> tmp(this->begin(), this->end());
				int size = tmp.size();
				free_vect();
				allocate_arr(n, T());
				this->_size = size;
				for(int i = 1; i <= _size; ++i)
				{
					this->_ptr[i] = tmp[i - 1];
				}
			}
		}
		reference operator[] (size_type n)
		{
			return _ptr[n + 1];
		}
		const_reference operator[] (size_type n) const
		{
			return _ptr[n + 1];
		}
		reference at (size_type n)
		{
			if (n >= _size)
				throw  std::out_of_range("vector");
			return _ptr[n + 1];
		}
		const_reference at (size_type n) const
		{
			if (n >= _size)
				throw  std::out_of_range("vector");
			return _ptr[n + 1];
		}
		reference front()
		{
			return _ptr[1];
		}
		const_reference front() const
		{
			return _ptr[1];
		}
		reference back()
		{
			return _ptr[_size];
		}
		const_reference back() const
		{
			return _ptr[_size];
		}
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last, 
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
				{
					if (last - first > _capacity)
					{
						free_vect();
						this->_size = last - first;
						this->_capacity = _size;
						allocate_range(first, last);
						return ;
					}
					_size = last - first;
					for(int i = 1;first != last; first++)
					{
						_ptr[i] = *first;
						i++;
					}
				}
		void assign (size_type n, const value_type& val)
		{
			if (n > _capacity)
			{
				free_vect();
				_size = n;
				_capacity = n;
				allocate_arr(n, val);
				return ;
			}
			_size = n;
			for (int i = 1; i <= n; i++)
				_ptr[i] = val;
		}
		void push_back (const value_type& val)
		{
	
			if (_size == _capacity)
			{
				if (_capacity == 0)
				{
					reserve(1);
					_capacity = 1;
				}
				else 
				{
					reserve(_capacity * 2);
					_capacity = _size * 2;
				}
				_size++;
				_ptr[_size] = val;
				return ;
			}
			_size++;
			_ptr[_size] = val;
		}
		void pop_back()
		{
			_size--;
		}
		void reserve_and_insert (size_type n, iterator postion, const value_type& val)
		{
			if (n > _capacity)
			{
				vector<T> tmp(this->begin(), this->end());
				int size = tmp.size();
				free_vect();
				allocate_arr(n, T());
				this->_size = size;
				int j = 1;
				for(int i = 1; i <= _size; ++i)
				{
					if (j == postion.get_pos())
						this->_ptr[j++] = val;
					this->_ptr[j] = tmp[i - 1];
					++j;
				}
			}
		}
		void reserve_and_insert (size_type n, iterator position, size_type nbr, const value_type& val)
		{
			if (n > _capacity)
			{
				vector<T> tmp(this->begin(), this->end());
				int size = tmp.size();
				free_vect();
				allocate_arr(n, val);
				_size = size + nbr;
				int j = 0;
				for(int i = 1; i <= _size; ++i)
				{
					if (i == position.get_pos())
						i += nbr;
					_ptr[i] = tmp[j];
					++j;
				}
			}
		}
		iterator insert (iterator position, const value_type& val)
		{
			if (position == this->end())
			{
				this->push_back(val);
				return iterator(&_ptr[_size], _size, position.get_pos());
			}
			if (_capacity > _size)
			{
				int i = _size + 1;
				while(i-- > position.get_pos())
				{
					_ptr[i + 1] = _ptr[i];
				}
				_ptr[i + 1] = val;
				iterator it(&_ptr[i], _size + 1, i);
				_size++;
				return it;
			}
			else
			{
				this->reserve_and_insert(_capacity * 2, position, val);
				_size++;
				return iterator(&_ptr[position.get_pos()], _size, position.get_pos());
			}
			return iterator();
		}
		void insert (iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return ;
			if (_capacity >= _size + n)
			{
				if (position == this->end())
				{
					while(n--)
						push_back(val);
					return ;
				}
				std::cout << position.get_pos() << std::endl;
				for (int j = _size + 1 ; j >= position.get_pos(); --j) //shift elements 
				{
					_ptr[j + n] = _ptr[j];
					if (j <= position.get_pos() + n) // add new elements
						_ptr[j] = val;
				}
				_size += n;
				return;
			}
			size_type new_capacity = _capacity * 2;
			if (n > new_capacity)
				new_capacity = _size + n;
			this->reserve_and_insert(new_capacity , position, n , val); // reallocate and add elements
			return ;
		}
		template <class InputIterator>
		void reserve_and_insert (size_type n, iterator position, size_type nbr, InputIterator itr, 
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			if (n > _capacity)
			{
				vector<T> tmp(this->begin(), this->end());
				int size = tmp.size();
				free_vect();
				allocate_arr(n, T());
				_size = size + nbr;
				int j = 0;
				for(int i = 1; i <= _size; ++i)
				{
					if (i == position.get_pos())
					{
						while(i < i + nbr)
							_ptr[i] = *itr++;
						i += nbr;
					}
					_ptr[i] = tmp[j];
					++j;
				}
			}
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, 
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			// std::cout << "here \n";
			// size_type n = last - first;
			// InputIterator tmp(first);
			// if (n == 0)
			// 	return ;
			// if (_capacity >= _size + n)
			// {
			// 	if (position == this->end())
			// 	{
			// 		while(n--)
			// 			push_back(*tmp++);
			// 		return ;
			// 	}
			// 	std::cout << position.get_pos() << std::endl;
			// 	for (int j = _size + 1 ; j >= position.get_pos(); --j) //shift elements 
			// 	{
			// 		_ptr[j + n] = _ptr[j];
			// 		if (j <= position.get_pos() + n) // add new elements
			// 			_ptr[j] = *tmp++;
			// 	}
			// 	_size += n;
			// 	return;
			// }
			// size_type new_capacity = _capacity * 2;
			// if (n > new_capacity)
			// 	new_capacity = _size + n;
			// this->reserve_and_insert(new_capacity , position, n , tmp); // reallocate and add elements
			// return ;
		}
};

};