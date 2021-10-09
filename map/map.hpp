/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:40:54 by mbani             #+#    #+#             */
/*   Updated: 2021/10/09 11:43:11 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "pair.hpp"
#include "AVL.hpp"

namespace ft
{


template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
class map
{

	class value_compare
	{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
	friend class map;
	protected:
	Compare comp;
	value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
	public:
	typedef bool result_type;
	typedef T first_argument_type;
	typedef T second_argument_type;
	bool operator() (const T& x, const T& y) const
	{
		return comp(x.first, y.first);
	}
	};
	public:
	typedef Key		key_type;
	typedef	T		mapped_type;
	typedef typename ft::pair<const key_type,mapped_type>		value_type;
	typedef Compare												key_compare;
	typedef	value_compare										value_comp;
	typedef Alloc												allocator_type;
	typedef value_type &										reference;
	typedef	const value_type &									const_reference;
	typedef value_type *										pointer;
	typedef const value_type *									const_pointer;
	// typedef ft::bidirectional_access_iterator<value_type>		iterator;
	// typedef ft::bidirectional_access_iterator<const value_type>	const_iterator;
	// typedef ft::reverse<value_type>								reverse_iterator;
	// typedef ft::reverse<const value_type>						const_reverse_iterator;
	typedef ptrdiff_t										difference_type;
	typedef size_t											size_type;

	private:
		AVL<value_type, allocator_type, key_compare> avl;
	public:
		map()
		{
			int ind = 90;
			std::string val = "value";
			ft::pair<int, std::string> tst(ind, val);
			AVL<value_type, allocator_type, key_compare> *res;
			res = (avl.add(tst));
			// std::cout << res->get_pair()->first << std::endl;
			// std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind2 = 5;
			std::string val2 = "value 02";
			ft::pair<int, std::string> tst2(ind2, val2);
			res = avl.add(tst2);
			// std::cout << res->get_pair()->first << std::endl;

			// std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind0 = 5;
			std::string val0 = "value 00";
			ft::pair<int, std::string> tst0(ind0, val0);
			res = avl.add(tst0);
			// std::cout << res->get_pair()->first << std::endl;

			// // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind5 = 91;
			std::string val5 = "value 55";
			ft::pair<int, std::string> tst5(ind5, val5);
			res = avl.add(tst5);
			// // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind3 = 5;
			std::string val3 = "value 03";
			ft::pair<int, std::string> tst3(ind3, val3);
			res = avl.add(tst3);
			// // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind9 = 6;
			std::string val9 = "value 09";
			ft::pair<int, std::string> tst9(ind9, val9);
			res = avl.add(tst9);
			// // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind18 = 7;
			std::string val18 = "value 018";
			ft::pair<int, std::string> tst18(ind18, val18);
			res = avl.add(tst18);
			// // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			res = avl.find(tst18);
			if (res)
				std::cout << "found " << res->parent->get_pair()->first << std::endl;
			else
				std::cout << "Not found \n";
			std::cout << (avl.remove(res)) << std::endl;
			res = avl.find(tst18);
			if (res)
				std::cout << "found " << res->parent->get_pair()->first << std::endl;
			else
				std::cout << "Not found \n";
			std::cout << "Height :" << avl.height() << std::endl;
			std::cout << avl.size() <<std::endl;
		}
};

}