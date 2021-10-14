/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:45:54 by mbani             #+#    #+#             */
/*   Updated: 2021/10/14 17:54:19 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "../tools/pair.hpp"

namespace ft
{

template<typename Tp, typename U>
class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Tp>
{
	public:
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::value_type			value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, Tp>::difference_type		difference_type;
		typedef Tp*																				node_pointer;
		typedef Tp&																				reference;	
		typedef U																				pair;
	private:
		node_pointer _iter;
	public:
		bidirectional_iterator():_iter(NULL)
		{};
		bidirectional_iterator(node_pointer avl):_iter(avl)
		{};
		bidirectional_iterator(const bidirectional_iterator &obj)
		{
			this->_iter = obj._iter;
		}
		bidirectional_iterator &operator=(const bidirectional_iterator &obj)
		{
			this->_iter = obj._iter;
			return *this;
		}
		bool operator==(bidirectional_iterator &obj)
		{
			return this->_iter == obj._iter;
		}
		pair operator*()const
		{
			return *(_iter->get_pair());
		}
		pair *operator->() const
		{
			return _iter->get_pair();	
		}
		bidirectional_iterator operator++()
		{
			this->_iter = _iter->get_successor(_iter);
			return *this;
		}
		template<typename T, typename P>
		friend bool operator!=(bidirectional_iterator<T, P> &rhs, bidirectional_iterator<T, P> &lhs);
};

template<typename T, typename P>
bool operator!=(bidirectional_iterator<T, P> &rhs, bidirectional_iterator<T, P> &lhs)
		{
			return &(*rhs._iter) != &(*lhs._iter);
		}
}