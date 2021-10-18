/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:50:03 by mbani             #+#    #+#             */
/*   Updated: 2021/10/18 18:54:42 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

template <class Iterator>
struct iterator_traits
{
   typedef typename Iterator::value_type		value_type;
   typedef typename Iterator::difference_type	difference_type;
   typedef typename Iterator::pointer			   pointer;
   typedef typename Iterator::reference			reference;
   typedef typename Iterator::iterator_category	iterator_category;
};

template <class U>
struct iterator_traits<U*>
{
   typedef U							value_type;
   typedef ptrdiff_t					difference_type;
   typedef U*							pointer;
   typedef U&							reference;
   typedef ft::random_access_iterator_tag	iterator_category;
};

template <class U> class iterator_traits<const U*>
{
   typedef const U						value_type;
   typedef ptrdiff_t					difference_type;
   typedef const U*						pointer;
   typedef const U&						reference;
   typedef ft::random_access_iterator_tag	iterator_category;
};

template<class Category, class P,class Distance = std::ptrdiff_t,
		class Pointer = P*, class Reference = P&>
struct iterator
{
	typedef Category	iterator_category;
	typedef P			value_type;
	typedef Distance	difference_type;
	typedef	Reference	reference;
};

}