/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:15:32 by mbani             #+#    #+#             */
/*   Updated: 2021/06/24 10:03:11 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <class Tp, class Tv>
class iterators
{
	protected:
		Tp *current;
	public:
		iterators():current(nullptr)
		{
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
			return this;
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
		Tp *get_node()
		{
			return this->current;
		}
		operator iterators<node, const Tv>() const 
		{
			return iterators<node, const Tv>(current);
		}

		~iterators(){};
};

template <class Tp, class Tv>
class rev_iter
{
	private:
		Tp *current;
	public:
		rev_iter()
		{
			this->current = nullptr;
		};
		rev_iter(Tp *node)
		{
			this->current = node;
		}
		rev_iter(const rev_iter &obj)
		{
			*this = obj;
		}
		rev_iter(iterators<Tp,Tv> it)
		{
			this->current = (it.get_node())->prev;
		}
		void operator=(const rev_iter &obj)
		{
			this->current = obj.current;
		}
		bool operator!=(const rev_iter &obj)
		{
			return (this->current != obj.current);
		}
		bool operator==(const rev_iter &obj)
		{
			return (this->current == obj.current);
		}
		Tv &operator*() const
		{
			return this->current->value;
		}
		rev_iter operator++()//preincrement
		{
			this->current = this->current->prev;
			return this->current;
		}
		rev_iter operator++(int)
		{
			rev_iter tmp(*this);
			this->current = this->current->prev;
			return *tmp;
		}
		rev_iter operator--()//predecrement
		{
			this->current = this->current->next;
			return *this;
		}
		rev_iter operator--(int)
		{
			rev_iter tmp(*this);
			this->current = this->current->next;
			return tmp;
		}
		operator rev_iter<node, const Tv>() const
		{
			return rev_iter<node, const Tv>(current);
		}
};