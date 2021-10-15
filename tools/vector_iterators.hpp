/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterators.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:15:32 by mbani             #+#    #+#             */
/*   Updated: 2021/10/15 11:30:05 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterator_traits.hpp"

namespace ft
{
template <typename Tp>
class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, Tp>
{
	public:
	typedef typename ft::iterator<ft::random_access_iterator_tag, Tp>::iterator_category	iterator_category;
	typedef typename ft::iterator<ft::random_access_iterator_tag, Tp>::value_type			value_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, Tp>::difference_type		difference_type;
	typedef Tp*																				pointer;
	typedef Tp&																				reference;
	private:
		pointer _it;
		size_t _size;
		int _pos;
	public:
		size_t get_size() const
		{return this->_size;}
		int get_pos() const
		{return this->_pos;}
		random_access_iterator():_it(nullptr), _size(0), _pos(-1)
		{
		};
		random_access_iterator(Tp *vect, size_t size, size_t pos)
		{
			this->_it = vect;
			this->_size = size;
			this->_pos = pos;
		};
		random_access_iterator(const random_access_iterator &obj)
		{
			this->_it = obj.get_ptr();
			this->_size = obj.get_size();
			this->_pos = obj.get_pos();
		};
		void operator=(const random_access_iterator &obj)
		{
			this->_it = obj._it;
			this->_size = obj._size;
			this->_pos = obj._pos;
		};
		reference operator*() const
		{
			return *_it;
		}
		Tp get_pos()
		{
			return this->_pos;
		}
		Tp const *operator->() const
		{
			return &(operator*());
		}
		reference operator[](difference_type n) const
		{
			return _it[n];
		}
		pointer base() const 
		{
			return this->_it;
		}
		random_access_iterator operator++()//preincrement
		{
			++_pos;
			++_it;
			return *this;
		}
		random_access_iterator operator++(int)
		{
			random_access_iterator tmp(*this);
			++_pos;
			++_it;
			return tmp;
		};
		random_access_iterator operator--()
		{
			--_pos;
			--_it;
			return *this;
		}
		random_access_iterator operator--(int)
		{
			random_access_iterator tmp(*this);
			--_pos;
			--_it;
			return tmp;
		}
		std::ptrdiff_t operator-(random_access_iterator const obj)
		{
			return this->_pos - obj._pos;
		}
		std::ptrdiff_t operator+(random_access_iterator const obj)
		{
			return this->_pos + obj._pos;
		}
		random_access_iterator operator-(size_t position)
		{
			random_access_iterator tmp(*this);
			tmp._it -= position;
			tmp._pos -= position;
			return tmp;
		}
		random_access_iterator operator+(difference_type position)
		{
			random_access_iterator tmp(*this);
			tmp._it += position;
			tmp._pos += position;
			return tmp;
		}
		random_access_iterator operator+=(difference_type n)
		{
			this->_it += n;
			this->_pos += n;
			return *this;
		}
		random_access_iterator operator-=(difference_type n)
		{
			this->_it -= n;
			this->_pos -= n;
			return *this;
		}
		bool operator==(random_access_iterator const &obj)
		{
			return (this->_it == obj._it);
		}
		bool operator!=(random_access_iterator const &obj)
		{
			return (this->_it != obj._it);
		}
		pointer get_ptr() const
		{
			return _it;
		}
		operator random_access_iterator<const Tp>() const 
		{
			return random_access_iterator<const Tp>(_it, _size, _pos);
		}

		~random_access_iterator(){};
};
template <typename Tp>
random_access_iterator<Tp> operator+(typename ft::iterator<ft::random_access_iterator_tag, Tp>::difference_type		n, random_access_iterator<Tp> lhs)
{
	return lhs + n;
}

template <typename Tp>
bool operator<(random_access_iterator<Tp> lhs, random_access_iterator<Tp> rhs)
{
	return lhs.get_pos() < rhs.get_pos();
}

template <typename Tp>
bool operator<=(random_access_iterator<Tp> lhs, random_access_iterator<Tp> rhs)
{
	return lhs.get_pos() <= rhs.get_pos();
}

template <typename Tp>
bool operator>(random_access_iterator<Tp> lhs, random_access_iterator<Tp> rhs)
{
	return lhs.get_pos() > rhs.get_pos();
}

template <typename Tp>
bool operator>=(random_access_iterator<Tp> lhs, random_access_iterator<Tp> rhs)
{
	return lhs.get_pos() >= rhs.get_pos();
}

template <class Iterator> 
class reverse_iterator
{
	public:
	typedef Iterator 													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;
	private:
		iterator_type _it;
	public:
	reverse_iterator(): _it()
	{
	};
	explicit reverse_iterator (iterator_type it): _it(it)
	{
	};
	template <class Iter>
  	reverse_iterator (const reverse_iterator<Iter>& rev_it)
	{
		this->_it = rev_it.base();
	}
	void operator=(const reverse_iterator &obj)
	{
		this->_it = obj.base();
	}
	iterator_type base() const
	{
		return this->_it;
	}
	reference operator*() const
	{
		return *(this->base() - 1);
	}
	reverse_iterator operator+ (difference_type n) const
	{
		iterator_type tmp_it(this->_it);
		tmp_it -= n;
		reverse_iterator tmp_rev(tmp_it);
		return tmp_rev;
	}
	reverse_iterator& operator++()
	{
		this->_it.operator--();
		return *this;
	}
	reverse_iterator operator++(int)
	{
		reverse_iterator temp = *this;
		++(*this);
		return temp;
	}
	reverse_iterator& operator+= (difference_type n)
	{
		this->_it -= n;
		return *this;
	}
	reverse_iterator operator- (difference_type n) const
	{
		iterator_type tmp_it(this->_it);
		tmp_it += n;
		reverse_iterator tmp_rev(tmp_it);
		return tmp_rev;		
	}
	reverse_iterator& operator--()
	{
		this->_it.operator++();
		return *this;
	}
	reverse_iterator operator--(int) 
	{
		reverse_iterator temp = *this;
		--(*this);
		return temp;
	}
	reverse_iterator& operator-= (difference_type n)
	{
		this->_it += n;
		return *this;
	}
	pointer operator->() const
	{
		return &(operator*());
	}
	reference operator[] (difference_type n) const
	{
		return this->_it.operator[](-n - 1);
	}
	operator reverse_iterator<const Iterator>() const 
	{
		return reverse_iterator<const Iterator>(_it);
	}
};

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() == rhs.base();
}
template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() != rhs.base();
}
template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() > rhs.base();
}
template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() >= rhs.base();
}
template <class Iterator>
bool operator>  (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() < rhs.base();
}
template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() <= rhs.base();
}
template <class Iterator>
reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
{
	return rev_it + n;
}
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (
const reverse_iterator<Iterator>& lhs,
const reverse_iterator<Iterator>& rhs)
{
	return rhs.base() - lhs.base();
}
}