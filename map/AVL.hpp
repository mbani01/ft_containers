/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:26:56 by mbani             #+#    #+#             */
/*   Updated: 2021/10/02 12:54:51 by mbani            ###   ########.fr       */
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
		size_t 			_size;
		type 			*data;
		Node			*root;
		Node			*left;
		Node			*right;
		Node			*parent;
		Compare			comp;
	public:
		AVL()
		{
			root = right = left = parent = nullptr;
			_size = 0;
		}
		// AVL(const type & obj = type()):data(obj), size(0)
		// {
		// 	root = parent = right = left = nullptr;
		// }
		Node &operator=(const type &obj)
		{
			freeNode(this);
			this = newNode(obj);
			return *this;
		}
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
			if (tmp[0]->data)
			{
				pair_alloc.destroy(tmp[0]->data);
				pair_alloc.deallocate(tmp[0]->data, 1);
			}
			tmp[0]->data = nullptr;
			if (tmp[0])
			{
				node_alloc.destroy(tmp[0]);
				node_alloc.deallocate(tmp[0], 1);
			}
			tmp[0] = nullptr;
		}
		type *get_pair()
		{
			return this->data;
		}
		size_t size()
		{
			return this->_size;
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
			size_t left_height;
			size_t right_height ;
			left_height = height(tmp->left) + 1; 
			right_height = height(tmp->right) + 1;
			return std::max(left_height, right_height);
		}
		void check_balance(Node *node)
		{
			// if (node->left && node->right)
			if (std::abs((int)((height(node->left))-(height(node->right) ))) > 1)
			{
				// the node caused inbalance, we should rebalance the tree
				// std::cout << "this node cause inbalance " << node->data->first << " parent " << ((node->parent) ? node->parent->data->first : node->data->first) << std::endl;
				rebalance(node);
				// std::cout << "node after balance " << node->data->first << " parent " << ((node->parent) ? node->parent->data->first : node->data->first) << std::endl;
				// if (node->parent)
				// {
				// 	std::cout << "left " << node->parent->left->data->first << std::endl;
				// 	std::cout << "right " << node->parent->right->data->first << std::endl;
				// 	// std::cout << "parent" << node->parent->parent->data->first << std::endl;
				// }
			}
			if (node->parent == nullptr) // it's the root the whole tree is balanced 
				return ;
			check_balance(node->parent); // rebalance from the current node to the root recursively
		}
		void rebalance(Node *node)
		{
			// Node *tmp
			if (height(node->left) > height(node->right))
			{
				//inbalance is in the left child
				if (height(node->left->left) > height(node->left->right))
				{
						//left child left subtree (Right Rotation)
					// std::cout << "right rotation of node " << node->data->first << std::endl;
					node = right_rot(node);
					// return node->left;
				}
				else
				{
						//left child right subtree (LeftRight Rotation)
					// std::cout << "leftright rotation of node " << node->data->first << std::endl;
					node = leftRight_rot(node);
				}
			}
			else
			{
				//inbalance in the right child
				if (height(node->right->right) > height(node->right->left))
				{
						//right child right subtree (Left Rotation)
					// std::cout << "left rotation of node " << node->data->first << std::endl;
					node = left_rot(node);
					// return node->right;
				}
				else
				{
						//right child left subtree (RightLeft Rotation)
					// std::cout << "rightleft rotation of node " << node->data->first << std::endl;
					node = rightLeft_rot(node);
				}
			}
			if (node->parent == nullptr) // set root to node
					root = node;
			// return tmp;
		}
		Node *left_rot(Node *node)
		{
			Node *tmp = node->right;
			if (node->parent)
				node->parent->right = tmp;
			tmp->parent = node->parent;
			node->right = tmp->left;
			tmp->left = node;
			node->parent = tmp;
			return tmp;
		}
		Node *right_rot(Node *node)
		{
			Node *tmp = node->left;
			if (node->parent)
				node->parent->left = tmp;
			tmp->parent = node->parent;
			node->left = tmp->right;
			node->parent = tmp;
			tmp->right = node;
			return tmp;
		}
		Node *leftRight_rot(Node *node)
		{
			node->left = left_rot(node->left);
			return right_rot(node);
		}
		Node *rightLeft_rot(Node *node)
		{
			node->right = right_rot(node->right);
			return right_rot(node);
		}
		T *add(const type &obj)
		{
			bool is_inserted;
			Node *new_node = newNode(obj);
			if (this->root == nullptr)
			{
				// std::cout << "Root :" << new_node->data->first << std::endl;
				this->root = new_node;
				this->_size++;
				return new_node->data;
			}
			T *result = add(this->root, new_node, is_inserted);
			if (!is_inserted)
			{
				freeNode(&new_node);
				return nullptr;
			}
			return result;
		}
		type *add(Node *parent, Node *new_node, bool &is_inserted)
		{
			type *tmp = new_node->data;
			if (!(comp(parent->data->first, new_node->data->first)) && !(comp(new_node->data->first, parent->data->first)))
			{
				// duplicate key :should free new node && return the existing one
				// freeNode(&new_node);
				// 	std::cout << "freed\n";
				is_inserted = false;
				return parent->data;
			}
			if (!comp(parent->data->first, new_node->data->first)) // if parent->key < new_node->key 
			{
				//  add to parent left
				// std::cout << "compar is new greater than parent " << comp(parent->data->first, new_node->data->first) << std::endl;
				if (parent->left == nullptr)
				{
					parent->left = new_node;
					new_node->parent = parent;
					// std::cout << "Left: " << new_node->data->first << " parent " << (new_node->parent ? new_node->parent->data->first : new_node->data->first) << std::endl; 
					this->_size++;
					is_inserted = true;
					return new_node->data;
				}
				else
					add(parent->left, new_node, is_inserted);
			}
			else if (comp(parent->data->first, new_node->data->first)) // check if parent->key > new_node->key
			{
				// add to parent right
				if (parent->right == nullptr)
				{
					parent->right = new_node;
					new_node->parent = parent;
					is_inserted = true;
					// std::cout << "Right: " << new_node->data->first << " parent " << (new_node->parent ? new_node->parent->data->first : new_node->data->first) <<  std::endl;
					this->_size++;
					return new_node->data;
				}
				else 
					add(parent->right, new_node, is_inserted);
			}
			check_balance(new_node);
			return tmp;
		}
};