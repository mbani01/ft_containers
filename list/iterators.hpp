/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:15:32 by mbani             #+#    #+#             */
/*   Updated: 2021/06/21 12:19:47 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <class Tp, class Tv>
class iterators
{
	protected:
		Tp *current;
		// T value;
	public:
		iterators():current(nullptr)
		{
			std::cout << "called\n";
		};
		iterators(Tp *node)
		{
			this->current = node;
		};
		iterators(const iterators &obj)
		{
			*this = obj;
		};
		void operator=(const iterators &obj)
		{
			this->current = obj.current;
		};
		Tv& operator*() const
		{
			return this->current->value;
		}
		iterators *operator->()
		{
			return this->current;
		}
		iterators operator++()//preincrement
		{
			this->current = this->current->next;
			return this->current;
		}
		iterators operator++(int)
		{
			iterators tmp(*this);
			this->current = this->current->next;
			return tmp;
		};
		iterators operator--()
		{
			this->current = this->current->prev;
			return *this;
		}
		iterators operator--(int)
		{
			iterators tmp(*this);
			this->current = this->current->prev;
			return tmp;
			
		}
		bool operator==(iterators const &obj)
		{
			return this->current == obj.current;
		}
		bool operator!=(iterators const &obj)
		{
			return this->current != obj.current;
		}
		operator iterators<node, const Tv>() const 
		{
			return iterators<node, const Tv>(current);}

		~iterators(){};
};

// template <class Tp>
// class const_iterators : public iterators<Tp>
// {
// 	public:
// 		const_iterators(){};
// 		~const_iterators(){};
// 		const_iterators(Tp *head)
// 		{
// 			std::cout << "called here\n";
// 			this->current = head;
// 		};
// 		const_iterators(const const_iterators &it)
// 		{
// 			*this = it;
// 		};
// 		const_iterators &operator=(const const_iterators &it)
// 		{
// 			this->current = it.current;
// 			return *this;
// 		};
// 		const T operator*()
// 		{
// 			return this->current->value;
// 		};
// };