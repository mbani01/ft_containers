/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 08:04:32 by mbani             #+#    #+#             */
/*   Updated: 2021/10/05 10:44:38 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "iterators.hpp"

namespace ft
{
			
	/*	======================> enable_if && is_integral implementation <============================  */
	template<typename>	struct is_integral {static const bool value = false;};
	template<> 			struct is_integral<bool> {static const bool value = true;};
	template<> 			struct is_integral<char> {static const bool value = true;};
	template<> 			struct is_integral<signed char> {static const bool value = true;};
	template<> 			struct is_integral<short int> {static const bool value = true;};
	template<> 			struct is_integral<int> {static const bool value = true;};
	template<> 			struct is_integral<long int> {static const bool value = true;};
	template<> 			struct is_integral<long long int> {static const bool value = true;};
	template<> 			struct is_integral<unsigned char> {static const bool value = true;};
	template<> 			struct is_integral<unsigned short int> {static const bool value = true;};
	template<> 			struct is_integral<unsigned int> {static const bool value = true;};
	template<> 			struct is_integral<unsigned long int> {static const bool value = true;};
	template<> 			struct is_integral<unsigned long long int> {static const bool value = true;};

	template<bool Condition, typename TC = void>
	struct enable_if
	{
	};
	template<typename TC>
	struct enable_if<true, TC>
	{
		typedef TC type;
	};

template < class T, class Alloc = std::allocator<T> >
class vector
{
	public:
			/*	======================> typedef <============================  */
		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::random_access_iterator<T>				iterator;
		typedef ft::random_access_iterator<const T>			const_iterator;
		typedef ft::reverse_iterator<iterator>		  		reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef  ptrdiff_t									difference_type;
		typedef  size_t										size_type;

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
		void allocate_arr(size_t n, const T val)
		{
			this->_ptr = _alloc.allocate(n + 2);
			// _ptr[n + 1] = val;
			// _ptr[0] = val;
			if (!_ptr)
				fatal_error();
			for(size_t i = 1 ; i <= n; i++)
			{
				_ptr[i] = val;
			}
			_size = n;
			_capacity = n;
		}
		template <class InputIterator>
		void allocate_range(InputIterator first, InputIterator last)
		{
		// DOES NOT SET SIZE && CAPACITY 	
			this->_ptr = _alloc.allocate(_size + 2);
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
			for(size_t i = 1; i <= _size; ++i)
				_ptr[i].~T();
			_alloc.deallocate(_ptr, _capacity + 2);
			_ptr = nullptr;
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
				for(size_t i = 1; i <= _size; ++i)
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
				for(unsigned long i = 1; i <= _size; ++i)
				{
					if (i == (unsigned long)position.get_pos())
						i += nbr;
					_ptr[i] = tmp[j];
					++j;
				}
			}
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
				for(size_t i = 1; i <= _size; ++i)
				{
					if ((int)i == position.get_pos())
					{
						for(; i < position.get_pos() + nbr; ++i)
							_ptr[i] = *itr++;
					}
					_ptr[i] = tmp[j];
					++j;
				}
			}
		}
	public:
			// Dereferencing start from 1 to n (included) 0 && n+1 reserved for rbegin and end

		/*	======================> constructors  && descturtor <============================  */
		explicit vector (const allocator_type& alloc = allocator_type())
		{
			(void)alloc;
			_size = 0;
			_capacity = 0;
			_ptr = nullptr;
		};
		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
		{
			(void)alloc;
			_size = n;
			_capacity = n;
			allocate_arr(n, val);
		};
		template <class InputIterator>
         vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type(), 
				typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			(void)alloc;
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
		vector& operator= (const vector& x)
		{
			const_iterator last(x.end());
			const_iterator first(x.begin());
			if (x.size() > _capacity)
			{
				free_vect();
				this->_size = x.size();
				this->_capacity = _size;
				this->_ptr = _alloc.allocate(_size + 2);
				_ptr[_size + 1] = *first;
				_ptr[0] = *first;
				if (!_ptr)
					fatal_error();
				int i = 1;
				for(size_t len = 0 ; len < x.size() ; ++len)
				{
					_ptr[i] = x[i - 1];
					++i;
				}
				return *this;
			}
			_size = x.size();
			int i = 1;
			for(unsigned long len = 0 ; len < x.size() ; ++len)
			{
				_ptr[i] = x[i - 1];
				i++;
			}
			return *this;
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
		reverse_iterator rbegin(void)
		{
			if (_capacity != 0)
				return (reverse_iterator(end()));
			return (reverse_iterator());
		}
		const_reverse_iterator rbegin(void) const
		{
			if (_capacity != 0)
				return (reverse_iterator(end()));
			return (reverse_iterator());
		}
		reverse_iterator rend(void)
		{
			if (_capacity != 0)
				return (reverse_iterator(begin()));
			return (reverse_iterator());
		}
		const_reverse_iterator rend(void) const
		{
			if (_capacity != 0)
				return (reverse_iterator(begin()));
			return (reverse_iterator());
		}
		size_type size() const
		{
			return (this->_size);
		}
		size_type max_size() const
		{
			return (_alloc.max_size());	
		}
		void resize (size_type n, value_type val = value_type())
		{
			if (n <= _size)
			{
				for(size_t i = n; i != _size; ++i)
				{
					_ptr[i].~T();
				}
				this->_size = n;
				return;
			}
			if (n > _size && n <= _capacity)
			{
				for(size_t i = _size; i < n; ++i)
					_ptr[i + 1] = val;
				this->_size = n;
				return;					
			}
			if (n > _capacity)
			{
				size_t new_cap = _capacity * 2;
				if (n > new_cap)
					new_cap =  n;
				vector<T> tmp;
				tmp.reserve(new_cap);
				tmp.insert(this->begin(), this->begin(), this->end());
				tmp.insert(tmp.end(), tmp.capacity() - tmp.size(), val);
				free_vect();
				this->swap(tmp);
				this->_size = n;
				return;
			}
			return;
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
				for(size_t i = 1; i <= _size; ++i)
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
					if (last - first > (int)_capacity)
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
			for (size_t i = 1; i <= n; i++)
				_ptr[i] = val;
		}
		void push_back (const value_type& val)
		{
			
			if (_size == _capacity)
			{
				if (_capacity == 0)
				{
					this->_ptr = _alloc.allocate(3);
					_capacity = 1;
				}
				else 
				{
					int size = _size;
					T* tmp = _alloc.allocate((_capacity * 2) + 2);
					for(size_t i = 1; i <= _size ; ++i)
						tmp[i] = _ptr[i];
					free_vect();
					this->_ptr = tmp;
					_size = size;
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
			_ptr[_size].~T();
			_size--;
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
				for (int j = _size + 1 ; j >= position.get_pos(); --j) //shift elements 
					_ptr[j + n] = _ptr[j];
				for (unsigned long j = position.get_pos(); j < position.get_pos() + n; ++j) 
						_ptr[j] = val;
				_size += n;
				return;
			}
			size_type new_capacity = _capacity * 2;
			if (n > new_capacity)
				new_capacity = _size + n;
			this->reserve_and_insert(new_capacity , position, n , val); // te and add elements
			return ;
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, 
			typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
		{
			size_type n = last - first;
			InputIterator tmp(first);
			if (n == 0)
				return ;
			if (_capacity >= _size + n)
			{
				if (position == this->end())
				{
					while(n--)
						push_back(*tmp++);
					return ;
				}
				for (int j = _size + 1 ; j >= position.get_pos(); --j) //shift elements
					_ptr[j + n] = _ptr[j];
				for (unsigned long j = position.get_pos(); j < position.get_pos() + n; ++j) 
						_ptr[j] = *tmp++;
				_size += n;
				return;
			}
			size_type new_capacity = _capacity * 2;
			if (n > new_capacity)
				new_capacity = _size + n;
			this->reserve_and_insert(new_capacity , position, n , tmp); // reallocate and add elements
			return ;
		}
		iterator erase (iterator position)
		{
			for(size_t i = position.get_pos(); i < _size + 1; ++i)
				{
					_ptr[i].~value_type();
					_ptr[i] = _ptr[i + 1];
				}
			_size--;
			return iterator(&_ptr[position.get_pos()], _size, position.get_pos());
		}
		iterator erase (iterator first, iterator last)
		{
			int len = last - first;
			for(int i = first.get_pos(); i < last.get_pos(); ++i)
			{
				this->_ptr[i].~value_type();
				if (_ptr[i + len])
					_ptr[i] = _ptr[i + len];
			}
			_size -= len;
			return iterator(&_ptr[first.get_pos()], _size, first.get_pos());
		}
		void swap (vector& x)
		{
			T *tmp = x._ptr;
			x._ptr = this->_ptr;
			_ptr = tmp;
			size_type tmp_sz = x._size;
			x._size = this->_size; 
			this->_size = tmp_sz;
			size_type tmp_cp = x._capacity;
			x._capacity = this->_capacity; 
			this->_capacity = tmp_cp;			
		}
		void clear()
		{
			this->erase(this->begin(), this->end());
		}
		allocator_type get_allocator() const
		{
			return this->_alloc;
		}
};

	/* 
	
		Non-member functions
	
	*/
template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	for(size_t i = 0 ; i < lhs.size(); ++i)
	{
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}
template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs==rhs);
}
template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() > rhs.size())
		return false;
	for(size_t i = 0; i < lhs.size() &&  i < rhs.size(); ++i)
	{
		if (lhs[i] < rhs[i])
			continue;
		return false;
	}
	return true;
}
template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() > rhs.size())
		return false;
	for(size_t i = 0; i < lhs.size(); ++i)
	{
		if (lhs[i] <= rhs[i])
			continue;
		return false;
	}
	return true;	
}
template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return !(lhs <= rhs);
}
template <class T, class Alloc>
bool operator>=  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{

	return !(lhs < rhs);
}

template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
{
	x.swap(y);
}

template <class InputIterator1, class InputIterator2>
bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
{
  while (first1!=last1) {
    if (!(*first1 == *first2))
      return false;
    ++first1; ++first2;
  }
  return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal (InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, BinaryPredicate pred)
{
  while (first1!=last1) {
    if (!pred(*first1,*first2))
      return false;
    ++first1; ++first2;
  }
  return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
  while (first1!=last1)
  {
    if (first2==last2 || *first2<*first1) return false;
    else if (*first1<*first2) return true;
    ++first1; ++first2;
  }
  return (first2!=last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2,Compare comp)
{
  while (first1!=last1)
  {
    if (first2==last2 || !comp(*first1,*first2)) return false;
    else if (comp(*first1,*first2)) return true;
    ++first1; ++first2;
  }
  return (first2!=last2);
}
};