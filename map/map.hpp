/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:40:54 by mbani             #+#    #+#             */
/*   Updated: 2021/10/15 12:46:24 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools/pair.hpp"
#include "../tools/make_pair.hpp"
#include "AVL.hpp"
#include "../tools/map_iterators.hpp"

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
	typedef Key																					key_type;
	typedef	T																					mapped_type;
	typedef typename ft::pair<const key_type,mapped_type>										value_type;
	typedef Compare																				key_compare;
	typedef	value_compare																		value_comp;
	typedef Alloc																				allocator_type;
	typedef value_type &																		reference;
	typedef	const value_type &																	const_reference;
	typedef value_type *																		pointer;
	typedef const value_type *																	const_pointer;
	typedef ft::bidirectional_iterator< AVL<value_type, allocator_type, key_compare> >			iterator;
	typedef ft::bidirectional_iterator<const AVL<value_type, allocator_type, key_compare> >		const_iterator;
	// typedef ft::reverse<value_type>								reverse_iterator;
	// typedef ft::reverse<const value_type>						const_reverse_iterator;
	typedef ptrdiff_t										difference_type;
	typedef size_t											size_type;

	private:
		typedef AVL<value_type, allocator_type, key_compare> Node;
		Node avl;
		const Node *get_avl() const
		{
			const Node *ptr = &avl;
			return ptr;
		}
	public:
	explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()):avl()
			{
				(void)comp;
				(void)alloc;		
			};
	template <class InputIterator>
  	map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type()):avl()
	{
		(void)comp;
		(void)alloc;
		bool is_inserted = false;
		for(; first != last; ++first)
			avl.add((*first), is_inserted);
	};
	map (const map& x)
	{
		*this = x;
	}
	map& operator= (const map& x)
	{
		avl.assign(x.get_avl());
		return *this;
	}
	iterator begin()
	{
		if (avl.size())
			return iterator(avl.findMinimum(avl.get_root()), NULL);
		return iterator();
	}
	const_iterator begin() const
	{
		if (avl.size())
			return const_iterator(avl.findMinimum(avl.get_root()), NULL);
		return const_iterator();
	}
	iterator end()
	{
		return iterator(NULL, avl.findMax(avl.get_root()));
	}
	const_iterator end() const
	{
		return const_iterator(NULL, avl.findMax(avl.get_root()));
	}
	bool empty() const
	{
		return (avl.size() == 0);
	}
	size_type size() const
	{
		return avl.size();
	}
	size_type max_size() const
	{
		return avl.max_size();
	}
	ft::pair<iterator,bool> insert (const value_type& val)
	{
		bool is_inserted = false;
		Node *res =	avl.add(val, is_inserted);
		return ft::make_pair(iterator(res, NULL), is_inserted);
	}
};
}



// 100,50,20,18,25,23,21


			// int ind = 50;
						// std::string val = "value";
						// ft::pair<int, std::string> tst;
		// AVL<value_type, allocator_type, key_compare> avl1;
						// AVL<value_type, allocator_type, key_compare> *res;
			// res = (avl.add(tst));
			// std::cout << res->get_pair()->first << std::endl;
			// std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			// int ind2 = 100;
			// std::string val2 = "value 02";
			// ft::pair<int, std::string> tst2(ind2, val2);
			// res = avl.add(tst2);
			// std::cout << res->get_pair()->first << std::endl;
						// bool is_inserted = false;
						// for(int i = 3; i < 10; ++i)
						// {
						// 	tst = ft::make_pair(i, val);
						// 	res = avl.add(tst, is_inserted);
						// 	std:: cout << is_inserted;
						// }
						// std::cout << std::endl;
						// res = avl.add(tst, is_inserted); 
						// std:: cout <<"inserted: " << is_inserted << std::endl;
						// if (res)
						// 	std::cout << "value :" << res->get_pair()->first << std::endl;
						// std::cout << "Root :" << std::endl;
						// avl.printBT();
						// while(1);
		// res = avl.find(ft::make_pair(7, val));
			// AVL<value_type, allocator_type, key_compare> *tmp;

		// tmp = avl.get_successor(res);
		// res = avl.get_predecessor(res);
		// 	// std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
		// 	int ind0 = 60;
		// 	std::string val0 = "value 00";
		// 	ft::pair<int, std::string> tst0(ind0, val0);
		// 	res = avl.add(tst0);
		// 	std::cout << tmp->get_pair()->first << std::endl;
		// 	std::cout << res->get_pair()->first << std::endl;
		// if (tmp == res)
		// 	std::cout << "This node doesn't have a successor \n";
		// 	// // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
		// 	int ind5 = 55;
		// 	std::string val5 = "value 55";
		// 	ft::pair<int, std::string> tst5(ind5, val5);
		// 	res = avl.add(tst5);
		// 	// // // // // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
		// 	int ind3 = 40;
		// 	std::string val3 = "value 03";
		// 	ft::pair<int, std::string> tst3(ind3, val3);
		// 	res = avl.add(tst3);
		// 	// // // // // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
		// 	int ind9 = 37;
		// 	std::string val9 = "value 09";
		// 	ft::pair<int, std::string> tst9(ind9, val9);
		// 	res = avl.add(tst9);
		// 	// // // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
		// 	int ind18 = 45;
		// 	std::string val18 = "value 018";
		// 	ft::pair<int, std::string> tst18(ind18, val18);
		// 	res = avl.add(tst18);


		// 	int ind07 = 25;
		// 	std::string val07 = "value 007";
		// 	ft::pair<int, std::string> tst07(ind07, val07);
		// 	res = avl.add(tst07);


		// 	int ind99 = 20;
		// 	std::string val99 = "value 099";
		// 	ft::pair<int, std::string> tst99(ind99, val99);
		// 	res = avl.add(tst99);
		// 	// res = avl.find(tst9);
		// 	// // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
		// 	avl1.assign(&avl);
		// 	avl.printBT();
		// 	std::cout << std::endl;
		// 	std::cout << "Height :" << avl.height() << std::endl;
		// // 	std::cout << "Size : " << avl.size() <<std::endl;
		// // 	std::cout << "removed Nodes : " << (avl.remove(avl.find(tst07))) << std::endl;
		// // 	// // std::cout << "After remove\n\n\n";
		// 	avl.clear();
		// 	avl1.printBT();
			// while(1);
		// 	std::cout << std::endl;
		// 	std::cout << "Height :" << avl.height() << std::endl;
		// 	std::cout << "Size : " << avl.size() <<std::endl;
			

		// 	res = avl.find(tst0);
		// 	avl.remove(res);
		// 	avl.printBT();
		// 	std::cout << std::endl;
		// 	std::cout << "Height :" << avl.height() << std::endl;
		// 	std::cout << "Size : " << avl.size() <<std::endl;

		// 	res = avl.find(tst);
		// 	avl.remove(res);
		// 	avl.printBT();
		// 	std::cout << std::endl;
		// 	std::cout << "Height :" << avl.height() << std::endl;
		// 	std::cout << "Size : " << avl.size() <<std::endl;

		// 	res = avl.find(tst5);
		// 	avl.remove(res);
		// 	avl.printBT();
		// 	std::cout << std::endl;
		// 	std::cout << "Height :" << avl.height() << std::endl;
		// 	std::cout << "Size : " << avl.size() <<std::endl;

		// 	res = avl.find(tst3);
		// 	avl.remove(res);
		// 	avl.printBT();
		// 	std::cout << std::endl;
		// 	std::cout << "Height :" << avl.height() << std::endl;
		// 	std::cout << "Size : " << avl.size() <<std::endl;
		
		// 	res = avl.find(tst2);
		// 	avl.remove(res);
		// 	avl.printBT();
		// 	std::cout << std::endl;
		// 	std::cout << "Height :" << avl.height() << std::endl;
		// 	std::cout << "Size : " << avl.size() <<std::endl;


		