/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:15:32 by mbani             #+#    #+#             */
/*   Updated: 2021/07/08 13:04:16 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename Tp>
class iterators
{
	private:
		Tp *_it;
		size_t _size;
		int _pos;
	public:
		size_t get_size() const
		{return this->_size;}
		int get_pos() const
		{return this->_pos;}
		iterators():_it(nullptr), _size(0), _pos(-1)
		{
		};
		// iterators(Tp *ptr):_it(ptr){};
		iterators(Tp *vect, size_t size, size_t pos)
		{
			this->_it = vect;
			this->_size = size;
			this->_pos = pos;
		};
		iterators(const iterators &obj)
		{
			this->_it = obj.get_ptr();
			this->_size = obj.get_size();
			this->_pos = obj.get_pos();
		};
		void operator=(const iterators &obj)
		{
			this->_it = obj._it;
			this->_size = obj._size;
			this->_pos = obj._pos;
		};
		Tp& operator*() const
		{
			return *_it;
		}
		Tp get_pos()
		{
			return this->_pos;
		}
		iterators *operator->()
		{
		}
		iterators operator++()//preincrement
		{
			++_pos;
			++_it;
			return *this;
		}
		iterators operator++(int)
		{
			iterators tmp(*this);
			++_pos;
			++_it;
			return tmp;
		};
		iterators operator--()
		{
			--_pos;
			--_it;
			return *this;
		}
		iterators operator--(int)
		{
			iterators tmp(*this);
			--_pos;
			--_it;
			return tmp;
		}
		std::ptrdiff_t operator-(iterators const obj)
		{
			return this->_pos - obj._pos;
		}
		std::ptrdiff_t operator+(iterators const obj)
		{
			return this->_pos + obj._pos;
		}
		iterators operator-(size_t position)
		{
			this->_it -= position;
			this->_pos -= position;
			return *this;
		}
		iterators operator+(size_t position)
		{
			this->_it += position;
			this->_pos += position;
			return *this;
		}
		bool operator==(iterators const &obj)
		{
			return (this->_it == obj._it);
		}
		bool operator!=(iterators const &obj)
		{
			return (this->_it != obj._it);
		}
		Tp *get_ptr() const
		{
			return _it;
		}
		operator iterators<const Tp>() const 
		{
			return iterators<const Tp>(_it, _size, _pos);
		}

		~iterators(){};
};

// template <class Tp, class Tv>
// class rev_iter
// {
// 	private:
// 		Tp *current;
// 	public:
// 		rev_iter()
// 		{
// 			this->current = nullptr;
// 		};
// 		rev_iter(Tp *node)
// 		{
// 			this->current = node;
// 		}
// 		rev_iter(const rev_iter &obj)
// 		{
// 			*this = obj;
// 		}
// 		rev_iter(iterators<Tp,Tv> it)
// 		{
// 			this->current = (it.get_node())->prev;
// 		}
// 		void operator=(const rev_iter &obj)
// 		{
// 			this->current = obj.current;
// 		}
// 		bool operator!=(const rev_iter &obj)
// 		{
// 			return (this->current != obj.current);
// 		}
// 		bool operator==(const rev_iter &obj)
// 		{
// 			return (this->current == obj.current);
// 		}
// 		Tv &operator*() const
// 		{
// 			static Tv val = Tv();
// 			if (this->current)
// 				return this->current->value;
// 			return val;
// 		}
// 		rev_iter operator++()//preincrement
// 		{
// 			this->current = this->current->prev;
// 			return this->current;
// 		}
// 		rev_iter operator++(int)
// 		{
// 			rev_iter tmp(*this);
// 			this->current = this->current->prev;
// 			return *tmp;
// 		}
// 		rev_iter operator--()//predecrement
// 		{
// 			this->current = this->current->next;
// 			return *this;
// 		}
// 		rev_iter operator--(int)
// 		{
// 			rev_iter tmp(*this);
// 			this->current = this->current->next;
// 			return tmp;
// 		}
// 		operator rev_iter<node, const Tv>() const
// 		{
// 			return rev_iter<node, const Tv>(current);
// 		}
// };