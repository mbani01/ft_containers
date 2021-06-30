/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 10:49:44 by mbani             #+#    #+#             */
/*   Updated: 2021/06/30 09:50:26 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <iterator>

namespace ft
{
template<class T, class Alloc = std::allocator<T> >
class list
{
	private:
	/*	======================> doubly linked-list <============================  */
		typedef struct node{
			T value;
			node(): next(nullptr), prev(nullptr){};
			struct node *next;
		 	struct node *prev;
		}				node;
		
	/*	======================> private functions <============================  */
	void node_fill(T value,node **head)
	{
		node *tmp = nullptr;
		tmp = node_all.allocate(1);
		node_all.construct(tmp, node());
		if (!tmp)
			exit(1);
		tmp->value = value;
		tmp->next = nullptr;
		tmp->prev = nullptr;
		node_addback(head, tmp);
	};
	void free_tmp()
	{
		if (prev)
		{
			node_all.deallocate(prev, 1);
			node_all.destroy(prev);
			prev = nullptr;
		}
		node *tmp;
		while(head)
		{
			tmp = head->next;
			node_all.deallocate(head, 1);
			node_all.destroy(head);
			head = tmp;
		}
		tmp = nullptr;
	}
	void add_rend_node(node *head)
	{
		node *tmp = node_all.allocate(1);
		node_all.construct(tmp, node());
		if (!tmp)
			exit(1);
		head->prev = tmp;
		prev = head->prev;
		tmp->next = head;
		tmp->prev = nullptr;
	}
	void add_last_ele(node **head, node *new_node)
	{
		node *tmp = *head;
		node *last = nullptr;
		while(tmp->next)
			tmp = tmp->next;
		last = tmp->prev;
		new_node->next = tmp;
		tmp->prev = new_node;
		last->next = new_node;
	}
	/*	======================> attributes <============================  */
		node *head;
		node *prev;
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
		/*	======================> typedef <============================  */

		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef iterators<node, T>							iterator;
		typedef iterators< node, const T>					const_iterator;
		typedef rev_iter<node, T>		  					reverse_iterator;
		typedef rev_iter<node, const T>						const_reverse_iterator;
		typedef  ptrdiff_t									difference_type;
		typedef  size_t										size_type;
		typedef typename allocator_type::template rebind<node>::other node_allocator;
		
		/*	======================> constructors  && descturtor <============================  */

		// default constructor
		explicit list(const allocator_type& = allocator_type())
		{
			_size = 0;
			this->head = nullptr;
			this->prev = nullptr;
			// this->head->prev = nullptr;
			// this->head->next = nullptr;
		};
		
		// fill constructor
		explicit list(size_type n, const value_type& val = value_type(),
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
			add_rend_node(head);
			_size = n;
		};
		template <typename TY>static bool is_int(TY){return false;}
		template<>static bool is_int<int>(int){return true;}
		template<>static bool is_int<bool> (bool){return true;};
		template<>static bool is_int<char> (char){return true;};
		template<>static bool is_int<signed char>(signed char) {return true;};
		template<>static bool is_int<short int> (short int){return true;};
		template<>static bool is_int<long int> (long int){return true;};
		template<>static bool is_int<long long int> (long long int){return true;};
		template<>static bool is_int<unsigned char> (unsigned char){return true;};
		template<>static bool is_int<unsigned short int> (unsigned short int){return true;};
		template<>static bool is_int<unsigned int> (unsigned int){return true;};
		template<>static bool is_int<unsigned long int> (unsigned long int){return true;};
		template<>static bool is_int<unsigned long long int> (unsigned long long int){return true;};
		// struct is_int : std::false_type
		// {
		// };
		// template<>  // explicit specialization for T = void
		// struct is_int<int> : std::true_type
		// {
		// };
		
		template<bool Condition, typename TC = void>
		struct enable_if
		{
		};
		template<typename TC>
		struct enable_if<true, TC>
		{
			typedef TC type;
		};
		// range constructor
		template <typename InputIterator>
		list (InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type(), typename enable_if<!is_int(first), InputIterator>::type = 0)
		// list (InputIterator first, InputIterator last,
        //  const allocator_type& alloc = allocator_type())
		 {	 
			node *tmp = NULL;
			
			this->head = nullptr;
			_size = 0;
			while (1)
			{
				node_fill(*first, &head);
				_size++;
				if (first == last)
					break;
				first++;
			}
			add_rend_node(head);
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
		free_tmp();
		iterator it(obj.begin());
		this->_size = obj.size();
		while(1)
		{
			node_fill(*it, &head);
			if (it == obj.end())
				break;
			++it;
		}
		add_rend_node(head);
		return *this;
	};
			/*	======================> iterators <============================  */
	iterator begin(void)
	{
		if (this->head)
			return (iterator(this->head));
		return (iterator());
	};
	const_iterator begin(void) const
	{
		if (this->head)
			return const_iterator(this->head);
		return (iterator());
	};
	reverse_iterator rbegin()
	{
		if (!head)
			return (reverse_iterator());
		node *tmp = head;
		while(tmp->next->next)
			tmp = tmp->next;
		reverse_iterator it(tmp);
		return it;
	}
	const_reverse_iterator rbegin() const
	{
		if (!head)
			return (reverse_iterator());
		node *tmp = head;
		while(tmp->next->next) 
			tmp = tmp->next;
		reverse_iterator it(tmp);
		return it;
	}
	iterator end()
	{
		if (!head)
			return (iterator());
		node *tmp = head;
		while(tmp->next) 
			tmp = tmp->next;
		iterator it(tmp);
		return it;
	}
	const_iterator end() const
	{
		if (!head)
			return (iterator());
		node *tmp = head;
		while(tmp->next)
			tmp = tmp->next;
		iterator it(tmp);
		return it;
	}
	reverse_iterator rend()
	{
		if (!head)
			return (reverse_iterator());
		return (reverse_iterator(this->head->prev));
	}
	const_reverse_iterator rend() const
	{
		if (!head)
			return (reverse_iterator());
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
		return node_all.max_size();
	};
	reference front()
	{
		static T val = value_type();
		if (this->head)
			return this->head->value;
		return val;
	};
	const_reference front() const
	{
		static T val = value_type();
		if (this->head)
			return this->head->value;
		return val;
	};
	reference back()
	{
		reverse_iterator it = rbegin();
		return *it;
	};
	const_reference back() const
	{
		const_reverse_iterator it = rbegin();
		return *it;
	};
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last)
	{
		free_tmp();
		if (first == last)
		{
			_size = 0;
			return ;
		}
		_size = 0;
		while (1)
		{
			node_fill(*first, &head);
			_size++;
			if (first == last)
				break;
			first++;
		}
		add_rend_node(head);
		_size--;
	}
	void assign (size_type n, const value_type& val)
	{


		/* TO BE TESTED !!! */
		node *tmp;
		free_tmp();
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
		add_rend_node(head);
		_size = n;
	}
	// push_front();
	void push_front (const value_type& val)
	{
		node *tmp = nullptr;
		node *tmp1 = nullptr;
		
		tmp = node_all.allocate(1);
		node_all.construct(tmp, node());
		tmp->value = val;
		tmp->prev = nullptr;
		tmp->next = nullptr;
		if (!head)
		{
			head = tmp;
			_size += 1;
			add_rend_node(head);
			tmp = node_all.allocate(1);
			node_all.construct(tmp, node());
			tmp->prev = nullptr;
			tmp->next = nullptr;
			node_addback(&head, tmp);
			return ;
		}

		if (head->prev)
			tmp1 = head->prev;
		tmp->next = head;
		tmp->prev = head->prev;
		head->prev = tmp;
		tmp1->next = tmp;
		head = head->prev;
		_size += 1;
	}
	// pop_front();
	void pop_front()
	{
		if (!head)
			return ;
		node *tmp = head;
		head = head->next;
		head->prev = tmp->prev;
		node_all.deallocate(tmp, 1);
		node_all.destroy(tmp);
		tmp = nullptr;
		_size--;
	}
	// push_back();
	void push_back (const value_type& val)
	{
		node *tmp = node_all.allocate(1);
		node_all.construct(tmp, node());
		if (!tmp)
			exit(1);
		tmp->value = val;
		tmp->prev = nullptr;
		tmp->next = nullptr;
		if (!head)
		{
			head = tmp;
			add_rend_node(head);
			tmp = node_all.allocate(1);
			node_all.construct(tmp, node());
			tmp->prev = nullptr;
			tmp->next = nullptr;
			node_addback(&head, tmp);
			_size++;
			return ;
		}
		add_last_ele(&head, tmp);
		_size++;
	}
	
	void pop_back()
	{
		node *bf_last;
		node *end;
		if (!head)
			return ;
		node *tmp = head;
		while(tmp->next->next)
			tmp = tmp->next;
		end = tmp->next;
		bf_last = tmp->prev;
		bf_last->next = end;
		end->prev = bf_last;
		node_all.deallocate(tmp, 1);
		node_all.destroy(tmp);
		tmp = nullptr;
		// bf_last->next = nullptr;
		
		
		
	}
	// insert();
	// iterator insert (iterator it, const value_type& val)
	// {
	// 	node *pos = it.get_node();
		
	// }
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

};