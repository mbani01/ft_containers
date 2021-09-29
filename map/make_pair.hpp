/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:19:08 by mbani             #+#    #+#             */
/*   Updated: 2021/09/23 15:19:44 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "pair.hpp"

namespace ft
{

template <class T1,class T2>
ft::pair<T1,T2> make_pair (T1 x, T2 y)
{
return ( ft::pair<T1,T2>(x,y) );
};

}