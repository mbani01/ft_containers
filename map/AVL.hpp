/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:26:56 by mbani             #+#    #+#             */
/*   Updated: 2021/10/08 17:02:49 by mbani            ###   ########.fr       */
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
		int				_height;
		int				bf;
		type 			*data;
		Node			*root;
		Node			*left;
		Node			*right;
		Compare			comp;
	public:
		Node			*parent;
		AVL()
		{
			root = right = left = parent = NULL;
			_size = _height = bf = 0;
		}
		// AVL(const type & obj = type()):data(obj), size(0)
		// {
		// 	root = parent = right = left = NULL;
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
			if (tmp[0]->parent && tmp[0]->parent->right == tmp[0])
					tmp[0]->parent->right = NULL;
			else if (tmp[0]->parent && tmp[0]->parent->left == tmp[0])
					tmp[0]->parent->left = NULL;
			if (tmp[0]->data)
			{
				pair_alloc.destroy(tmp[0]->data);
				pair_alloc.deallocate(tmp[0]->data, 1);
			}
			tmp[0]->data = NULL;
			tmp[0]->parent = NULL;
			tmp[0]->left = NULL;
			tmp[0]->right = NULL;
			if (tmp[0])
			{
				node_alloc.destroy(tmp[0]);
				node_alloc.deallocate(tmp[0], 1);
			}
			tmp[0] = NULL;
		}
		type *get_pair()
		{
			return this->data;
		}
		size_t size()
		{
			// for(; root; root = root->left)
			// 	std::cout << "Key " << root->data->first << "Parent " << (root->parent ? root->parent->data->first : root->data->first) << std::endl;
			// std::cout << root->parent->right->parent->data->first << std::endl;
			return this->_size;
		}
		int height()
		{
			return get_height(root);
		}
		int get_height(Node *node)
		{
			if (!node)
				return -1;
			return std::max(get_height(node->left), get_height(node->right)) + 1;
		}
		void update_height(Node *node)
		{
			if (!node)
				return ;
			int left_height = -1;
			int right_height = -1;
			if (node->left)
				left_height = node->left->_height;
			if (node->right)
				right_height = node->right->_height;
			node->_height = 1 + std::max(left_height, right_height);
			node->bf = left_height - right_height;
			return ;
		}

		Node *left_rot(Node *node)
		{

			Node *tmp = node->right;
			if (node->parent)
				node->parent->right = tmp;
			if (tmp->left)
				tmp->left->parent = node;
			tmp->parent = node->parent;
			node->right = tmp->left;
			tmp->left = node;
			node->parent = tmp;
			update_height(tmp);
			update_height(tmp->parent);
			return tmp;
		}
		Node *right_rot(Node *node)
		{
			Node *tmp = node->left;
			if (node->parent)
				node->parent->left = tmp;
			if (tmp->right)
				tmp->right->parent = node;
			tmp->parent = node->parent;
			node->left = tmp->right;
			node->parent = tmp;
			tmp->right = node;
			update_height(tmp);
			update_height(tmp->parent);
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
			return left_rot(node);
		}
		Node *add(const type &obj)
		{
			bool is_inserted;
			Node *new_node = newNode(obj);
			// if (this->root == NULL)
			// {
			// 	// std::cout << "Root :" << new_node->data->first << std::endl;
			// 	this->root = new_node;
			// 	this->_size++;
			// 	return new_node;
			// }
			root = add(this->root, new_node, is_inserted, NULL);
			if (!is_inserted)
			{
				freeNode(&new_node);
				return NULL;
			}
			return new_node;
		}
		// void update_height(Node *node)
		// {	
		// 	if (!node)
		// 		return ;
		// 	node->_height = get_height(node);
		// 	std::cout << "Node : " << node->data->first << " height : " << node->_height << std::endl;
		// 	update_height(node->parent);
		// }
		// Node balance(Node *node)
		// {

		// }
		Node *check_balance(Node *node)
		{
			// check if balance factor > 1 || < -1 
			if (node->bf != 1 && node->bf != 0 && node->bf != -1)
				node = rebalance(node);
			// if (node->parent == NULL) // it's the root the whole tree is balanced 
			// 	return node;
			return node;
			// return check_balance(node->parent); // rebalance from the current node to the root recursively
		}
		Node *rebalance(Node *node)
		{
			if (node->bf > 1)
			{
				//inbalance is in the left child
				if (node->bf == 2 && node->left->bf == 1) //left child left subtree (Right Rotation)
					node = right_rot(node);
				else if (node->bf == 2 && node->right->bf == -1) //left child right subtree (LeftRight Rotation)
					node = leftRight_rot(node);
			}
			else if (node->bf < -1)
			{
				//inbalance in the right child
				if (node->bf == -2 && node->right->bf == -1) //right child right subtree (Left Rotation)
					node = left_rot(node);
				else if (node->bf == -2 && node->right->bf == 1) //right child left subtree (RightLeft Rotation)
					node = rightLeft_rot(node);
			}
			if (node->parent == NULL) // set root to node
					root = node;
			return node;
		}
		Node *add(Node *current, Node *new_node, bool &is_inserted, Node *parent)
		{
			if (current == NULL)
			{
				new_node->parent = parent;
				this->_size++;
				is_inserted = true;
				// std::cout << "Node : " << new_node->data->first << " its parent : " << parent->data->first << std::endl;
				return new_node;
			}
			if (!(comp(current->data->first, new_node->data->first)) && !(comp(new_node->data->first, current->data->first))) // duplicate key :should free new node && return the existing one
			{
				is_inserted = false;
				return new_node; 
			}
			if (!comp(current->data->first, new_node->data->first))						//	if parent->key > new_node->key 
				current->left = add(current->left, new_node, is_inserted, current); 	//	add to parent left
			else if (comp(current->data->first, new_node->data->first)) 				//	check if parent->key < new_node->key
				current->right = add(current->right, new_node, is_inserted, current);	//	add to parent right
			// update_height(new_node);
			current->_height = get_height(current);
			return check_balance(current);
		}
		Node *find(type pair)
		{
			if (!(comp(root->data->first, pair.first)) && !(comp(pair.first, root->data->first)))
				return root;
			return find(this->root, pair);
		}
		Node *find(Node* parent, type pair)
		{
			if (!parent)
				return NULL;
			if (!(comp(parent->data->first, pair.first)) && !(comp(pair.first, parent->data->first)))
			{
				// key's are equal
				return parent;
			}
			else if (!comp(parent->data->first, pair.first)) //parent key < pair.key
			{
				return find(parent->left, pair);
			}
			else
				return find(parent->right, pair);
		}
		size_t remove(Node *node)
		{
			Node *res = this->find(*(node->data));
			if (!res)
				return 0;
			if (!get_height(res->right) && !get_height(res->left)) // node has no child
			{
				res = node->parent;
				freeNode(&node);
				--_size;
				check_balance(res);
				return 1;
			}
			return 100;
		}
};