/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 10:49:44 by mbani             #+#    #+#             */
/*   Updated: 2021/06/16 16:45:48 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <iterator>

namespace ft
{
template<class T, class Alloc = std::allocator<T> >
class list : public std::allocator<T>
{
private:
	typedef struct node{
		T value;
		node(): next(nullptr){};
		struct node *next;
		struct node *prev;
	}				node;
	node *head;
	void node_addback(node **head, node *new_node){
		node *tmp = *head;
		if (*head == nullptr)
		{
			printf("entred here\n");
			*head = new_node;
		}
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_node;
			new_node->prev = tmp;	
		}
	};
public:
	template<class Tp>
	class my_iterator {
		private:
			Tp *lst;
		public:
		my_iterator(){lst = nullptr;};
		my_iterator(Tp *lst){this->lst = lst;};
		Tp &begin(Tp *lst){while(lst->prev) lst = lst->prev; return lst;};
		Tp &end(Tp *lst){while(lst) lst = lst->next; return lst;};
		void operator++(){lst = lst->next;};
		void operator--(){this->lst = this->lst->prev;};
		bool operator==(my_iterator<Tp> const &obj){return this->lst == obj.lst;};
		Tp& operator*() const {return *lst;};
	};
	template<class Tp>
	class rev_iterator {
		private:
			Tp *lst;
		public:
		rev_iterator(){lst = nullptr;};
		rev_iterator(Tp *lst){while(lst->next) lst = lst->next; return lst;};
		Tp &rend(Tp *lst){while(lst->prev) lst = lst->prev; return lst;};
		Tp &rbegin(Tp *lst){while(lst->next) lst = lst->next; return lst;};
		void operator++(){lst = lst->next;};
		void operator--(){this->lst = this->lst->prev;};
		bool operator==(rev_iterator<Tp> const &obj){return this->lst == obj.lst;};
		Tp& operator*() const {return *lst;};
	};
	typedef T 											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference 			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef my_iterator<node>							iterator;
	typedef my_iterator<node const>						const_iterator;
	typedef rev_iterator<node>			  				reverse_iterator;
	typedef rev_iterator<node const>					const_reverse_iterator;
	typedef  ptrdiff_t									difference_type;
	typedef  size_t										size_type;
	typedef typename allocator_type::template rebind<node>::other node_allocator;
	explicit list(const allocator_type& = allocator_type()){
		allocator_type();
	};
	explicit list (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	{
		this->head = nullptr;
		node *tmp = NULL;
		node_allocator node_all;
		allocator_type list_all;
		for(int i = 0; i < n; i++)
		{
			tmp = node_all.allocate(1);
				printf("value %d\n", val);
			node_all.construct(tmp, node());
			tmp->value = val;
			tmp->next = nullptr;
			tmp->prev = nullptr;
			node_addback(&head, tmp);
		};
		// alloc.construct
	};	
	// operator=(const &list);
	// empty();
	// size();
	// max_size();
	// front();
	// back();
	// assign();
	// push_front();
	// pop_front();
	// push_back();
	// insert();
	// erase();
	// swap();
	// resize();
	// clear();
	// splice();
	// remove();
	// remove_if();
	// unique();
	// merge();
	// sort();
	// reverse();
	// get_allocator();
	// ~list();
	// friend bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	// friend bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	// friend bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	// friend bool operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	// friend bool operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);
	// friend bool operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs);

};

// list::list(/* args */)
// {
// };

// list::~list()
// {
// }

};
