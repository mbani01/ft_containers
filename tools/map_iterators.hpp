/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:45:54 by mbani             #+#    #+#             */
/*   Updated: 2021/10/16 10:17:33 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "../tools/pair.hpp"

namespace ft
{

template<typename Tp>
class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Tp>
{
	public:
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::value_type			value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::difference_type		difference_type;
		typedef Tp*																				node_pointer;
		typedef Tp&																				reference;
		typedef typename Tp::type																			pair;
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
		pair operator*()const
		{
			return *(_iter->get_pair());
		}
		pair *operator->() const
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
		operator bidirectional_iterator<const Tp>() const
		{
			return bidirectional_iterator<const Tp>(_iter, _last);
		}
		node_pointer get_node()const
		{
			return _iter;
		}
		template<typename T>
		friend bool operator!=(bidirectional_iterator<T> &rhs, bidirectional_iterator<T> &lhs);
		template<typename T>
		friend bool operator==(bidirectional_iterator<T> &rhs, bidirectional_iterator<T> &lhs);
};

template<typename T>
bool operator==(bidirectional_iterator<T> &rhs, bidirectional_iterator<T> &lhs)
		{
			return &(*rhs._iter) == &(*lhs._iter);
		}

template<typename T>
bool operator!=(bidirectional_iterator<T> &rhs, bidirectional_iterator<T> &lhs)
		{
			return &(*rhs._iter) != &(*lhs._iter);
		}
}