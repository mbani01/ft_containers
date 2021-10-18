/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 09:40:54 by mbani             #+#    #+#             */
/*   Updated: 2021/10/18 16:19:05 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../tools/pair.hpp"
#include "../tools/make_pair.hpp"
#include "AVL.hpp"
#include "../tools/map_iterators.hpp"
#include "../vector/vector.hpp"

namespace ft
{

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
class map
{

	public:
	typedef Key																					key_type;
	typedef	T																					mapped_type;
	typedef typename ft::pair<const key_type,mapped_type>										value_type;
	typedef Compare																				key_compare;
	typedef Alloc																				allocator_type;
	typedef value_type &																		reference;
	typedef	const value_type &																	const_reference;
	typedef value_type *																		pointer;
	typedef const value_type *																	const_pointer;
	typedef class value_compare : public std::binary_function<value_type,value_type,bool>
	{
		friend class map;
		protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	} value_compare;
	typedef ft::bidirectional_iterator< AVL<value_type, allocator_type, key_compare>, value_type>			iterator;
	typedef ft::bidirectional_iterator< AVL<value_type, allocator_type, key_compare>, const value_type >		const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	// typedef ft::reverse<const value_type>						const_reverse_iterator;
	typedef ptrdiff_t										difference_type;
	typedef size_t											size_type;

	private:
		typedef AVL<value_type, allocator_type, key_compare> Node;
		Node avl;
		allocator_type allocator;
		key_compare comp_key;
		const Node *get_avl() const
		{
			const Node *ptr = &avl;
			return ptr;
		}
	public:
	explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()):avl()
			{
				comp_key = comp;
				allocator = alloc;		
			};
	template <class InputIterator>
  	map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type()):avl()
	{
		comp_key = comp;
		allocator = alloc;
		bool is_inserted = false;
		for(; first != last; ++first)
			avl.add((*first), is_inserted);
	};
	map (const map& x):avl()
	{
		*this = x;
	}
	map& operator= (const map& x)
	{
		avl.assign(x.get_avl());
		this->comp_key = x.comp_key;
		return *this;
	}
	iterator begin()
	{
		if (avl.size())
			return iterator(avl.findMinimum(avl.get_root()), avl.findMax(avl.get_root()));
		return iterator();
	}
	const_iterator begin() const
	{
		if (avl.size())
			return const_iterator(avl.findMinimum(avl.get_root()), avl.findMax(avl.get_root()));
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
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	// reverse_iterator rbegin() const
	// {
	// 	return const_reverse_iterator(end());
	// }
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	// reverse_iterator rend() const
	// {
	// 	return const_reverse_iterator(begin());
	// }
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
	iterator insert (iterator position, const value_type& val)
	{
		(void)position;
		bool is_inserted = false;
		Node *res =	avl.add(val, is_inserted);
		return iterator(res, avl.findMax(avl.get_root()));
	}
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		for(; first != last; ++first)
		{
			ft::make_pair(first->first, first->second);
			insert(*(first));
		}
	}
	mapped_type& operator[] (const key_type& k)
	{
		return (this->insert(ft::make_pair(k, mapped_type())).first)->second;
	}
	void erase(iterator position)
	{
		avl.remove(position.get_node());
		(void)position;
	}
	size_type erase (const key_type& k)
	{
		value_type pair0 = ft::make_pair(k, mapped_type());
		return avl.remove(pair0);
	}
	void erase (iterator first, iterator last)
	{
		ft::vector<key_type> keys;
		while (first != last)
		{
			keys.push_back((first)->first);
			++first;
		}
		for(size_t i = 0; i <= keys.size(); ++i)
			this->erase(keys[i]);
	}
	void swap (map& x)
	{
		Node tmp = this->avl;
		this->avl = x.avl;
		x.avl = tmp;
	}
	void clear()
	{
		avl.clear();
	}
	key_compare key_comp() const
	{
		return comp_key;
	}
	value_compare value_comp() const
	{
		return value_compare(comp_key);
	}
	iterator find (const key_type& k)
	{
		Node *res = avl.find(ft::make_pair(k, mapped_type()));
		if (res)
			return iterator(res, NULL);
		return iterator(NULL, avl.findMax(avl.get_root()));
	}
	const_iterator find (const key_type& k) const
	{
		Node *res = avl.find(ft::make_pair(k, mapped_type()));
		if (res)
			return const_iterator(res, NULL);
		return const_iterator(NULL, avl.findMax(avl.get_root()));
	}
	size_type count (const key_type& k) const
	{
		Node *res = avl.find(ft::make_pair(k, mapped_type()));
		if (res)
			return 1;
		return 0;
	}
	allocator_type get_allocator() const
	{
		return allocator;
	}
	iterator lower_bound (const key_type& k)
	{
		Node *res = avl.lower_bound(ft::make_pair(k, mapped_type()));
		if (res)
			return iterator(res, NULL);
		return end();
	}
	const_iterator lower_bound (const key_type& k) const
	{
		Node *res = avl.lower_bound(ft::make_pair(k, mapped_type()));
		if (res)
			return const_iterator(res, NULL);
		return end();
	}
	iterator upper_bound (const key_type& k)
	{
		Node *res = avl.upper_bound(ft::make_pair(k, mapped_type()));
		if (res)
			return iterator(res, NULL);
		return end();
	}
	const_iterator upper_bound (const key_type& k) const
	{
		Node *res = avl.upper_bound(ft::make_pair(k, mapped_type()));
		if (res)
			return const_iterator(res, NULL);
		return end();
	}
	ft::pair<iterator,iterator>             equal_range (const key_type& k)
	{
		return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
	}
	ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
	{
		return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
	}
	~map()
	{
		avl.clear();
	}
};
template <class Key, class T, class Compare, class Alloc>
bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	typename ft::map<Key,T,Compare,Alloc>::const_iterator lhs_b = lhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator lhs_e = lhs.end();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator rhs_b = rhs.begin();
	while(lhs_b != lhs_e && *(lhs_b) == *(rhs_b))
	{
		++lhs_b;
		++rhs_b;
	}
	if (lhs_b == lhs_e)
		return true;
	return false;
}
template <class Key, class T, class Compare, class Alloc>
bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs == rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class Key, class T, class Compare, class Alloc>
bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return !(rhs < lhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return rhs < lhs;
}
template <class Key, class T, class Compare, class Alloc>
bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs < rhs);
}
template <class Key, class T, class Compare, class Alloc>
void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
{
	x.swap(y);
}
}