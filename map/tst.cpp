/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 15:22:00 by mbani             #+#    #+#             */
/*   Updated: 2021/09/23 15:22:45 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "make_pair.hpp"

int main () {
  ft::pair <int,int> foo;
  ft::pair <int,int> bar;

  foo = ft::make_pair (10,20);
  bar = ft::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

  std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
  std::cout << "bar: " << bar.first << ", " << bar.second << '\n';

  return 0;
}