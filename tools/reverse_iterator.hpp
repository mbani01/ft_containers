/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:23:27 by mbani             #+#    #+#             */
/*   Updated: 2021/10/18 19:00:26 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
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
		Iterator tmp(this->_it);
		return *--tmp;
		// return *(this->base() - 1);
	}
	pointer operator->() const
	{
		return &(operator*());
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
bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return lhs.base() == rhs.base();
}
template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
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