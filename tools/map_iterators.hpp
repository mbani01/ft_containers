/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:45:54 by mbani             #+#    #+#             */
/*   Updated: 2021/10/19 11:46:44 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "../tools/pair.hpp"

namespace ft
{

template<typename Tp, typename U>
class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, U>
{
	public:
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::value_type			value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::difference_type		difference_type;
		typedef Tp*																				node_pointer;
		typedef Tp&																				node_reference;
		typedef U*																				pointer;
		typedef U&																				reference;

	private:
		node_pointer _iter;
		node_pointer _last;
	public:
		bidirectional_iterator():_iter(NULL), _last(NULL)
		{};
		bidirectional_iterator(node_pointer avl, node_pointer last):_iter(avl), _last(last)
		{};
		bidirectional_iterator(const bidirectional_iterator &obj)
		{
			this->_iter = obj._iter;
			this->_last = obj._last;
		}
		bidirectional_iterator &operator=(const bidirectional_iterator &obj)
		{
			this->_iter = obj._iter;
			this->_last = obj._last;
			return *this;
		}
		bidirectional_iterator base() const
		{
			return (*this);
		}
		reference operator*()const
		{
			return *(_iter->get_pair());
		}
		pointer operator->() const
		{
			return _iter->get_pair();	
		}
		bidirectional_iterator& operator++()
		{
			this->_iter = _iter->get_successor(_iter);
			return *this;
		}
		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		bidirectional_iterator& operator--()
		{
			if (this->_iter == NULL && _last != NULL)
			{
				_iter = _last;
				return *this;
			}
			this->_iter = _iter->get_predecessor(_iter);
			return *this;
		}
		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp(*this);
			--(*this);
			return tmp;
		}
		operator bidirectional_iterator<Tp, const U>() const
		{
			return bidirectional_iterator<Tp, const U>(_iter, _last);
		}
		node_pointer get_node()const
		{
			return _iter;
		}
		template<typename T, typename P, typename T1, typename P1>
		friend bool operator!=(bidirectional_iterator<T, P> rhs, bidirectional_iterator<T1, P1> lhs);
		template<typename T, typename P, typename T1, typename P1>
		friend bool operator==(bidirectional_iterator<T, P> rhs, bidirectional_iterator<T1, P1> lhs);
};

template<typename T, typename P, typename T1, typename P1>
bool operator==(bidirectional_iterator<T, P> rhs, bidirectional_iterator<T1, P1> lhs)
		{
			return &(*rhs._iter) == &(*lhs._iter);
		}

template<typename T, typename P, typename T1, typename P1>
bool operator!=(bidirectional_iterator<T, P> rhs, bidirectional_iterator<T1, P1> lhs)
		{
			return &(*rhs._iter) != &(*lhs._iter);
		}
}