/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:26:56 by mbani             #+#    #+#             */
/*   Updated: 2021/09/29 12:37:51 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "pair.hpp"
#include <cstdlib>

template <class T, class Alloc, class Compare>
class  AVL
{
	public:
		typedef T 				type;
		typedef AVL<T, Alloc, Compare> 	Node;
		typedef Alloc 			allocator;
		typedef typename Alloc::template rebind<AVL>::other node_all;
	private:
		allocator 		pair_alloc;
		node_all 		node_alloc;
		type 			*data;
		size_t 			size;
		Node			*root;
		Node			*left;
		Node			*right;
		Node			*parent;
		Compare			comp;
	public:
		AVL()
		{
			root = right = left = parent = nullptr;
			size = 0;
		}
		// AVL(const type & obj = type()):data(obj), size(0)
		// {
		// 	root = parent = right = left = nullptr;
		// }
		Node *newNode(const type&obj)
		{
			AVL *new_node = node_alloc.allocate(1); // allocate node
			node_alloc.construct(new_node);
			new_node->data = pair_alloc.allocate(1); // allocate pair <key, value>
			pair_alloc.construct(new_node->data, obj); //assing pair to data
			return new_node;
		}
		void freeNode(Node **tmp)
		{
			pair_alloc.destroy(tmp[0]->data);
			pair_alloc.deallocate(tmp[0]->data, 1);
			tmp[0]->data = nullptr;
			node_alloc.destroy(tmp[0]);
			node_alloc.deallocate(tmp[0], 1);
			tmp[0] = nullptr;
		}
		size_t height()
		{
			if (root == nullptr)
				return 0;
			return height(root) - 1;
		}
		size_t height(Node *tmp)
		{
			if(tmp == nullptr)
				return 0;
			// going to the most left/right node and then coming back && increasing height val recursively 
			size_t left_height = height(tmp->left) + 1; 
			size_t right_height = height(tmp->right) + 1;
			return std::max(left_height, right_height);
		}
		void check_balance(Node *node)
		{
			// if (node->left && node->right)
			if (std::abs((int)((height(node->left))-(height(node->right) ))) > 1)
			{
				// the node caused inbalance we should rebalance the tree
				std::cout << "inbalanced tree !!\n";
			}
			if (node->parent == nullptr) // it's the root the whole tree is balanced 
				return ;
			check_balance(node->parent); // rebalance from the current node to the root recursively
			
		}
		void add(const type &obj)
		{
			Node *new_node = newNode(obj);
			if (this->root == nullptr)
			{
				std::cout << "Root :" << new_node->data->second << std::endl;
				this->root = new_node;
				this->size++;
				return ;
			}
			add(this->root, new_node);
		}
		void add(Node *parent, Node *new_node)
		{
			if (!(comp(parent->data->first, new_node->data->first)) && !(comp(new_node->data->first, parent->data->first)))
			{
				// duplicate key :should free new node && return the existing one
				freeNode(&new_node);
					std::cout << "freed\n";
				return ;
			}
			if (comp(parent->data->first, new_node->data->first)) // if parent->key < new_node->key 
			{
				//  add to parent left
				if (parent->left == nullptr)
				{
					std::cout << "Left: " << new_node->data->second << std::endl; 
					parent->left = new_node;
					new_node->parent = parent;
					this->size++;
					// return ;
				}
				else
					add(parent->left, new_node);
			}
			else if (!comp(parent->data->first, new_node->data->first)) // check if parent->key > new_node->key
			{
				// add to parent right
				std::cout << "Right: " << new_node->data->second << std::endl;
				if (parent->right == nullptr)
				{
					parent->right = new_node;
					new_node->parent = parent;
					size++;
					// return ;
				}
				else 
					add(parent->right, new_node);
			}
			check_balance(new_node);
		}
};