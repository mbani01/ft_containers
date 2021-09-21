/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:44:43 by mbani             #+#    #+#             */
/*   Updated: 2021/09/21 13:00:35 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "../vector/vector.hpp"

namespace ft
{
    
template <class T, class Container = ft::vector<T> >
class stack
{
    public:
        typedef T			value_type;
        typedef Container   container_type;
        typedef size_t		size_type;
    protected:
        container_type c;
    public:
    
    // member functions
    explicit stack (const container_type& ctnr = container_type())
    {
        this->c = ctnr;
    }
    bool empty() const
    {
        return this->c.empty();
    }
    size_type size() const
    {
        return this->c.size();
    }
    value_type& top()
    {
        return this->c.back();
    }
    void push (const value_type& val)
    {
        return this->c.push_back(val);
    }
    void pop()
    {
        return this->c.pop_back();
    }
    template <class U, class Container1>
    friend bool operator== (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs);
    template <class U, class Container1>
    friend bool operator!= (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs);
    template <class U, class Container1>
    friend bool operator< (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs);
    template <class U, class Container1>
    friend bool operator<= (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs);
    template <class U, class Container1>
    friend bool operator> (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs);
    template <class U, class Container1>
    friend bool operator>= (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs);
    
};


template <class U, class Container1>
bool operator== (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs)
{
    return lhs.c == rhs.c;
}

template <class U, class Container1>
bool operator!= (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs)
{
    return lhs.c != rhs.c;
}

template <class U, class Container1>
bool operator< (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs)
{
    return lhs.c < rhs.c;
}    

template <class U, class Container1>
bool operator<= (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs)
{
    return lhs.c <= rhs.c;
}

template <class U, class Container1>
bool operator> (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs)
{
    return lhs.c > rhs.c;
}
template <class U, class Container1>
bool operator>= (const stack<U,Container1>& lhs, const stack<U,Container1>& rhs)
{
    return lhs.c >= rhs.c;
} 
}
