/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:26:56 by mbani             #+#    #+#             */
/*   Updated: 2021/10/16 13:25:33 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "../tools/pair.hpp"

template <class T, class Alloc, class Compare>
class  AVL
{
	public:
		typedef T 											type;
		typedef AVL<T, Alloc, Compare> 						Node;
		typedef Alloc 										allocator;
		typedef typename Alloc::template rebind<AVL>::other node_all;
	private:
		allocator 		pair_alloc;
		node_all 		node_alloc;
		size_t 			_size;
		int				bf;
		type 			*data;
		Node			*root;
		Node			*left;
		Node			*right;
		Compare			comp;
		int				_height;
		Node			*parent;
	public:
		AVL()
		{
			root = right = left = parent = NULL;
			_size = _height = bf = 0;
		}
		Node *getptr()
		{
			return this;
		}
		void clear()
		{
			clear(root);
			root = NULL;
			_size = 0;
		}
		void clear(Node *node)
		{
			if (node != NULL)
			{
				clear(node->left);
				clear(node->right);
				freeNode(&node);
			}
		}
		void assign1(const Node *obj)
		{
			if (!obj)
				return ;
			bool is_inserted = false;
			this->add(*(obj->data), is_inserted, false);
			assign1(obj->right);
			assign1(obj->left);
		}
		void assign(const Node *obj)
		{
			this->clear();
			root = NULL;
			assign1(obj->root);
		}
		// bool operator==(const Node* obj)
		// {
		// 	return  (this->parent == obj->parent && this->left == obj->left && this->right == obj->right && *(this->data) == *(obj->data));
		// }
		// Node &operator=(const type &obj)
		// {
		// 	std::cout << "Called !\n"; 
		// 	freeNode(this);
		// 	this = newNode(obj);
		// 	return *this;
		// }
		// Node
		Node *newNode(const type&obj)
		{
			AVL *new_node = node_alloc.allocate(1); // allocate node
			node_alloc.construct(new_node);
			new_node->data = pair_alloc.allocate(1); // allocate pair <key, value>
			pair_alloc.construct(new_node->data, obj); //assing pair to data
			return new_node;
		}
		Node *get_root()const
		{
			return this->root;
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
		type *get_pair() const
		{
			return this->data;
		}
		size_t size() const
		{
			return this->_size;
		}
		int height()
		{
			if (root)
				return root->_height;
			return -1;
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
			node->bf = right_height - left_height;
			return ;
		}
		void update_parent(Node *node, Node *tmp)
		{
			int is_left_child = -1;
			if (node && node->parent && node->parent->left == node)
				is_left_child = 1;
			else if (node && node->parent && node->parent->right == node)
				is_left_child = 0;
			switch (is_left_child)
			{
			case 1:
				/* code */
				node->parent->left = tmp;
				break;
			case 0:
				node->parent->right = tmp;
				break;
			default:
				break;
			}
			tmp->parent = node->parent;
			node->parent = tmp;
		}
		Node *left_rot(Node *node)
		{
			Node *tmp = node->right;
			node->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = node;
			tmp->left = node;
			update_height(node);
			update_height(tmp);
			update_parent(node, tmp);
			return tmp;
		}
		Node *right_rot(Node *node)
		{
			Node *tmp = node->left;
			node->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = node;
			tmp->right = node;
			update_height(node);
			update_height(tmp);
			update_parent(node, tmp);
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
		Node *rebalance(Node *node)
		{
			if (node->bf == -2) // node is left heavy
			{
				if (node->left->bf <= 0)
					node = right_rot(node); 
				else
					node = leftRight_rot(node);
			}
			else if (node->bf == 2) // node is right heavy
			{
				if (node->right->bf >= 0)
					node = left_rot(node);
				else
					node = rightLeft_rot(node);
			}
			if (!node->parent)
				root = node;
			return node;
		}
		Node *add(const type &obj, bool &is_inserted, bool balance = true)
		{
			Node *new_node = newNode(obj);
			root = add(this->root, &new_node, is_inserted, NULL, balance);
			return new_node;
		}
		Node *add(Node *current, Node **new_node, bool &is_inserted, Node *parent, bool balance = true)
		{
			if (current == NULL)
			{
				new_node[0]->parent = parent;
				this->_size++;
				is_inserted = true;
				return new_node[0];
			}
			if (!(comp(current->data->first, new_node[0]->data->first)) && !(comp(new_node[0]->data->first, current->data->first))) // duplicate key :should free new node && return the existing one
			{
				is_inserted = false;
				freeNode(new_node);
				new_node[0] = current;
				return current; 
			}
			if (!comp(current->data->first, new_node[0]->data->first))						//	if parent->key > new_node->key 
				current->left = add(current->left, new_node, is_inserted, current); 	//	add to parent left
			else if (comp(current->data->first, new_node[0]->data->first)) 				//	check if parent->key < new_node->key
				current->right = add(current->right, new_node, is_inserted, current);	//	add to parent right
			update_height(current);
			if (balance)
				return rebalance(current);
			return current;
		}
		Node *find(type pair)
		{
			return find(this->root, pair);
		}
		Node *find(Node* parent, type pair)
		{
			if (!parent)
				return NULL;
			if (!(comp(parent->data->first, pair.first)) && !(comp(pair.first, parent->data->first))) // key's are equal
				return parent;
			else if (!comp(parent->data->first, pair.first)) //parent key < pair.key
				return find(parent->left, pair);
			else
				return find(parent->right, pair);
		}
		int remove(Node *node)
		{
			bool is_deleted = false;
			if (!node)
				return 0;
			root = remove(this->root, node, is_deleted);
			if (is_deleted)
				--_size;
			return is_deleted;
		}
		int remove(type &pair)
		{
			bool is_deleted = false;
			Node *node = newNode(pair);
			if (!node)
				return 0;
			root = remove(this->root, node, is_deleted);
			if (is_deleted)
				--_size;
			return is_deleted;
		}
		Node *remove(Node *current, Node *to_delete, bool &is_deleted)
		{
			if(!current) // 404 Not found
			{
				is_deleted = false;
				return NULL;
			}
			if(!(comp(current->data->first, to_delete->data->first)) && !(comp(to_delete->data->first, current->data->first)))
			{
				is_deleted = true;
				current = remove_node(current);
			}
			else if (!comp(current->data->first, to_delete->data->first))	// current > to_delete
				current->left = remove(current->left, to_delete, is_deleted);
			else if (comp(current->data->first, to_delete->data->first)) // current < to_delete
				current->right = remove(current->right, to_delete, is_deleted);
			update_height(current);
			if (current)
				return rebalance(current);
			return NULL;
		}
		Node *remove_leaf_node(Node *to_delete)
		{	
			Node *tmp = to_delete->parent;
			freeNode(&to_delete);
			update_height(tmp);
			// --_size;
			return NULL;
		}
		bool is_right_child(Node *node, Node *parent)
		{
			if ((node && parent && parent->right && parent->right == node) || node == root)
				return true;
			return false;
		}
		bool is_left_child(Node *node, Node *parent)
		{
			if ((node && parent && parent->left && parent->left == node) || node == root)
				return true;
			return false;
		}
		Node *remove_right_child(Node *to_delete, Node *tmp)
		{
			if (to_delete->bf == 1) // has right child
			{
				if (to_delete == root)
				{
					root = to_delete->right;
					root->parent = NULL;
					freeNode(&to_delete);
					// --_size;
					update_height(root);
					return root;
				}
				tmp->right = to_delete->right;
				tmp->right->parent = tmp;
				freeNode(&to_delete);
				update_height(tmp);
				// --_size;
				return tmp->right;
			}
			else if (to_delete->bf == -1)
			{
				if (to_delete == root)
				{
					root = to_delete->left;
					root->parent = NULL;
					freeNode(&to_delete);
					// --_size;
					update_height(root);
					return root;
				}
				tmp->right = to_delete->left;
				tmp->left->parent = tmp;
				freeNode(&to_delete);
				update_height(tmp);
				// --_size;
				return tmp->right;
			}
			return NULL;
		}
		Node *remove_left_child(Node *to_delete, Node *tmp)
		{
			if (to_delete->bf == 1) //has right child
			{
				if (to_delete == root)
				{
					root = to_delete->right;
					root->parent = NULL;
					freeNode(&to_delete);
					// --_size;
					update_height(root);
					return root;
				}
				tmp->left = to_delete->right;
				tmp->left->parent = tmp;
				freeNode(&to_delete);
				update_height(tmp);
				// --_size;
				return tmp->left;
			}
			else if (to_delete->bf == -1) // has left child
			{
				if (to_delete == root)
				{
					root = to_delete->left;
					root->parent = NULL;
					freeNode(&to_delete);
					// --_size;
					update_height(root);
					return root;
				}
				tmp->left = to_delete->left;
				tmp->left->parent = tmp;
				freeNode(&to_delete);
				update_height(tmp);
				// --_size;
				return tmp->left;
			}
			return NULL;
		}
		Node *remove_node_with_one_child(Node *to_delete)
		{
			Node *tmp = to_delete->parent; // save node's parent
			if (is_right_child(to_delete, tmp))
				return remove_right_child(to_delete, tmp);
			else if (is_left_child(to_delete, tmp))
				return remove_left_child(to_delete, tmp);
			return NULL;
		}
		void replace_data(Node *node, Node *tmp)
		{
			if (node && tmp)
			{
				if (node->data)
				{
					pair_alloc.destroy(node->data);
					pair_alloc.deallocate(node->data, 1);
				}
				node->data = pair_alloc.allocate(1); // allocate pair <key, value>
				pair_alloc.construct(node->data, *(tmp->data));
			}
		}
		Node *remove_node_with_childs(Node *to_delete)
		{
			Node *tmp = findMinimum(to_delete->right);
			replace_data(to_delete, tmp);
			bool is_deleted;
			to_delete->right = remove(to_delete->right, tmp, is_deleted);
			return to_delete;
		}
		Node *remove_node(Node *to_delete)
		{
			if (to_delete->_height == 0) // remove leaf node
				return remove_leaf_node(to_delete);
			else if (to_delete->_height == 1 && (to_delete->bf == 1 || to_delete->bf == -1))
				return remove_node_with_one_child(to_delete);
			else if (to_delete->_height >= 1)
				return remove_node_with_childs(to_delete);
			// return 100;
			return to_delete;
		}
		Node* findMinimum(Node* node) // returns most left node
		{
			while (node->left)
				node = node->left;
			return node;
		}
		Node *findMax(Node *node)
		{
			while (node->right)
				node = node->right;
			return node;
		}
		Node *get_successor(Node *node)
		{
			if (!node)
				return node;
			if (node->right)
				return findMinimum(node->right);
			else
			{
				Node *parent = node->parent;
				while(parent && node == parent->right)
				{
					node = parent;
					parent = parent->parent;
				}
				// std::cout << "Val : " << parent->data->first << std::endl;
				if (parent == NULL)
					return root;
				return parent;
			}
		}
		Node *get_predecessor(Node *node)
		{
			if (!node)
				return node;
			if (node->left)
				return findMax(node->left);
			else
			{
				Node *parent = node->parent;
				while(parent && node == parent->left)
				{
					node = parent;
					parent = parent->parent;
				}
				if (!parent)
					return NULL;
				return parent;
			}
		}
		size_t max_size() const
		{
			return node_alloc.max_size();
		}
		void printBT(const std::string& prefix, const Node* node1, bool isLeft)
		{
			if( node1 != nullptr )
			{
				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──" );

				// print the value of the node1
				std::cout << node1->data->first << " ";
				std::cout << (isLeft ? "(L)" : "(R)") << std::endl;
				// enter the next tree level - left and right branch
				printBT( prefix + (isLeft ? "│   " : "    "), node1->left, true);
				printBT( prefix + (isLeft ? "│   " : "    "), node1->right, false);
			}
		}
		void printBT()
		{
			printBT("", root, false);
		}
};