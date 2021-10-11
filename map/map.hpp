/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:40:54 by mbani             #+#    #+#             */
/*   Updated: 2021/10/11 18:11:29 by mbani            ###   ########.fr       */
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
			int ind = 100;
			std::string val = "value";
			ft::pair<int, std::string> tst(ind, val);
			AVL<value_type, allocator_type, key_compare> *res;
			res = (avl.add(tst));
			// std::cout << res->get_pair()->first << std::endl;
			// std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind2 = 50;
			std::string val2 = "value 02";
			ft::pair<int, std::string> tst2(ind2, val2);
			res = avl.add(tst2);
			// std::cout << res->get_pair()->first << std::endl;

			// std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind0 = 20;
			std::string val0 = "value 00";
			ft::pair<int, std::string> tst0(ind0, val0);
			res = avl.add(tst0);
			// std::cout << res->get_pair()->first << std::endl;

			// // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind5 = 18;
			std::string val5 = "value 55";
			ft::pair<int, std::string> tst5(ind5, val5);
			res = avl.add(tst5);
			// // // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind3 = 25;
			std::string val3 = "value 03";
			ft::pair<int, std::string> tst3(ind3, val3);
			res = avl.add(tst3);
			// // // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind9 = 23;
			std::string val9 = "value 09";
			ft::pair<int, std::string> tst9(ind9, val9);
			res = avl.add(tst9);
			// // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			int ind18 = 21;
			std::string val18 = "value 018";
			ft::pair<int, std::string> tst18(ind18, val18);
			res = avl.add(tst18);
			// res = avl.find(tst9);
			// // // std::cout << "Inserted node's key: " << res->first << " value: " << res->second << std::endl;
			avl.printBT();
			std::cout << std::endl;
			std::cout << "Height :" << avl.height() << std::endl;
			std::cout << "Size : " << avl.size() <<std::endl;
			std::cout << "removed Nodes : " << (avl.remove(avl.find(tst))) << std::endl;
			std::cout << "After remove\n\n\n";
			
			avl.printBT();
			std::cout << std::endl;
			std::cout << "Height :" << avl.height() << std::endl;
			std::cout << "Size : " << avl.size() <<std::endl;
			

			res = avl.find(tst2);
			avl.remove(res);
			avl.printBT();
			std::cout << std::endl;
			std::cout << "Height :" << avl.height() << std::endl;
			// std::cout << "Size : " << avl.size() <<std::endl;

			// res = avl.find(tst18);
			// avl.remove(res);
			// avl.printBT();
			// std::cout << std::endl;
			// std::cout << "Height :" << avl.height() << std::endl;
			// std::cout << "Size : " << avl.size() <<std::endl;
		}
};

/*Node *rebalance(Node *node)
		{
			if (node->bf > 1)
			{
				//inbalance is in the left child
				// if (node->bf == 2 && node->left->bf == 1) //left child left subtree (Right Rotation)
				if(node->bf > 1 && comp(node->data->first, node->left->data->first))
					return right_rot(node);
				else if (node->bf > 1 && !comp(node->data->first, node->left->data->first)) //left child right subtree (LeftRight Rotation)
					return leftRight_rot(node);
			}
			else if (node->bf < -1)
			{
				//inbalance in the right child
				if (node->bf < -1 && !comp(node->data->first, node->right->data->first)) //right child right subtree (Left Rotation)
					return left_rot(node);
				else if (node->bf < -1 && !comp(node->data->first, node->right->data->first)) //right child left subtree (RightLeft Rotation)
					return rightLeft_rot(node);
			}
			// if (!node->parent)
			// 	root = node;
			return node;
		}*/

}