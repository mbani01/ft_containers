/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 10:49:44 by mbani             #+#    #+#             */
/*   Updated: 2021/06/24 10:06:34 by mbani            ###   ########.fr       */
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
		/*	======================> doubly linked-list <============================  */
		typedef struct node{
			T value;
			node(): next(nullptr), prev(nullptr){};
			struct node *next;
		 	struct node *prev;
		}				node;
	/*	======================> attributes <============================  */
		node *head;
		size_t _size;
		typename Alloc::template rebind<node>::other node_all;
	/*	==================================================  */
		void node_addback(node **head, node *new_node){
			node *tmp = *head;
			if (*head == nullptr)
				*head = new_node;
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = new_node;
				new_node->prev = tmp;	
			}
		};
	public:
		/*	======================> iterators classes <============================  */
		#include "iterators.hpp"

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

			/*	======================> typedef <============================  */

		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef iterators<node, T>							iterator;
		typedef iterators< node, const T>					const_iterator;
		typedef rev_iter<node, T>		  				reverse_iterator;
		typedef rev_iter<node, const T>					const_reverse_iterator;
		typedef  ptrdiff_t									difference_type;
		typedef  size_t										size_type;
		typedef typename allocator_type::template rebind<node>::other node_allocator;
		
		/*	======================> constructors  && descturtor <============================  */

		// default constructor
		explicit list(const allocator_type& = allocator_type())
		{
			_size = 0;
			this->head = nullptr;
		};
		
		// fill constructor
		explicit list (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
		{
			node *tmp = NULL;

			this->head = nullptr;
			this->_size = 0;
			for(int i = 0; i <= n; i++)
			{
				tmp = node_all.allocate(1);
				node_all.construct(tmp, node());
				if (!tmp)
					exit(1);
				tmp->value = val;
				tmp->next = nullptr;
				tmp->prev = nullptr;
				node_addback(&head, tmp);
			};
			tmp = node_all.allocate(1);
				node_all.construct(tmp, node());
				if (!tmp)
					exit(1);
			head->prev = tmp;
			tmp->next = head;
			_size = n;
		};
		
		// range constructor
		template <class InputIterator>
		list (InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type())
		 {
			node *tmp = NULL;
			 
			this->head = nullptr;
			_size = 0;
			while (1)
			{
				tmp = node_all.allocate(1);
				node_all.construct(tmp, node());
				if (!tmp)
					exit(1);
				tmp->value = *first;
				tmp->next = nullptr;
				tmp->prev = nullptr;
				node_addback(&head, tmp);
				_size++;
				if (first == last)
					break;
				first++;
			}
			tmp = node_all.allocate(1);
				node_all.construct(tmp, node());
				if (!tmp)
					exit(1);
			head->prev = tmp;
			tmp->next = head;
			_size--;
		 };

		//copy constructor
		list (const list& x)
		{
			*this = x;
		};
		
		//destructor
		~list()
		{
			node *tmp = this->head;	
			while(head)
			{
				tmp = head->next;
				node_all.deallocate(head, 1);
				node_all.destroy(head);
				head = tmp;
			}
			tmp = nullptr;
			
		}
		/*	======================> member functions <============================  */
	list &operator=(list& obj)
	{
		node *tmp = this->head;	
		
		while(head)
		{
			tmp = head->next;
			node_all.deallocate(head, 1);
			node_all.destroy(head);
			head = tmp;
		}
		tmp = nullptr;
		iterator it(obj.begin());
		this->_size = obj.size();
		// for(it = obj.begin(); it != obj.end(); it++)
		// {
		while(1)
		{
			tmp = node_all.allocate(1);
			node_all.construct(tmp, node());
			if (!tmp)
				exit(1);
			tmp->value = *it;
			tmp->next = nullptr;
			tmp->prev = nullptr;
			node_addback(&head, tmp);
			if (it == obj.end())
				break;
			++it;
		}
		tmp = node_all.allocate(1);
		node_all.construct(tmp, node());
		if (!tmp)
			exit(1);
		head->prev = tmp;
		tmp->next = head;
		return *this;
	};
			/*	======================> iterators <============================  */
	iterator begin(void)
	{
		return (iterator(this->head));
	};
	const_iterator begin(void) const
	{
		return const_iterator(this->head);
	};
	reverse_iterator rbegin()
	{
		node *tmp = head;
		while(tmp->next->next)
			tmp = tmp->next;
		reverse_iterator it(tmp);
		return it;
	}
	const_reverse_iterator rbegin() const
	{
		node *tmp = head;
		while(tmp->next->next) 
			tmp = tmp->next;
		reverse_iterator it(tmp);
		return it;
	}
	iterator end()
	{
		node *tmp = head;
		while(tmp->next) 
			tmp = tmp->next;
		iterator it(tmp);
		return it;
	}
	const_iterator end() const
	{
		node *tmp = head;
		while(tmp->next)
			tmp = tmp->next;
		iterator it(tmp);
		return it;
	}
	reverse_iterator rend()
	{
		return (reverse_iterator(this->head->prev));
	}
	const_reverse_iterator rend() const
	{
		return (reverse_iterator(this->head->prev));
	}
	bool empty()
	{
		return (_size == 0);
	};
	size_type size() const
	{
		return this->_size;
	};
	size_type max_size()
	{
		return allocator_type::max_size();
	};
	value_type &front()
	{
		return this->head->value;
	};
	value_type &back()
	{
		iterator it = end();
		return *it;
	};
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