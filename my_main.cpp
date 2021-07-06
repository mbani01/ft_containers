/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:51:27 by mbani             #+#    #+#             */
/*   Updated: 2021/07/06 16:23:35 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector/vector.hpp"
#include <vector>


void print_vector(std::vector<int>::iterator std_it_b, std::vector<int>::iterator std_it_e,
ft::vector<int>::iterator ft_it_b, ft::vector<int>::iterator ft_it_e)
{
	// std::vector<int>::iterator  std_it(std_vector_int.begin());
	// ft::vector<int>::iterator  ft_it(ft_vector_int.begin());
	std::cout << "ft  :: ";
	for(; ft_it_b != ft_it_e ; ++ft_it_b)
		std:: cout << *ft_it_b << " ";;
	std::cout << std::endl << "std :: ";
	for(; std_it_b != std_it_e ; ++std_it_b)
		std:: cout << *std_it_b << " ";;
	std::cout << std::endl;
}

// void print_rev(std::vector<int>::reverse_iterator std_it_rb, std::vector<int>::reverse_iterator std_it_re,
// ft::vector<int>::reverse_iterator ft_it_rb, ft::vector<int>::reverse_iterator ft_it_re)
// {
// 	std::cout << "Printing vector using reverse_iterator !" << std::endl;
// 	std::cout << "ft  :: ";
// 	for(; ft_it_rb != ft_it_re ; ++ft_it_rb)
// 		std:: cout << *ft_it_rb << " ";;
// 	std::cout << std::endl << "std :: ";
// 	for(; std_it_rb != std_it_re ; ++std_it_rb)
// 		std:: cout << *std_it_rb << " ";;
// 	std::cout << std::endl; 
// }

int main()
{


	//should fix copy constructor when iterators are done !!!
	std::cout << "	======================>\033[1;31m init and iterators tests \033[0m<============================ " << std::endl;
	// Creating vects of diffrent types
	std::vector<int> std_vect_int; 
	ft::vector<int> ft_vect_int; // call default constructor 
	ft::vector<int> vect_1(10, 5); // call fill constructor
	ft::vector<char> ft_vect_char(5, 'a');
	std::vector<char> std_vect_char;
	ft::vector<float> ft_vect_float;
	std::vector<float> std_vect_float;

	std::vector<int>::iterator std_it;
	ft::vector<int>::iterator ft_it;
	ft::vector<int>::const_iterator ft_itc(vect_1.begin());
	std::vector<int>::const_iterator std_itc(std_vect_int.begin());

	// *ft_itc = 8;
	// *std_itc = 8;

	for(int i = 0; i < 10; ++i)
		std_vect_int.push_back(i);
	ft::vector<int> ft_vect_int1(std_vect_int.begin(), std_vect_int.end()); // call range constructor 

	ft_it = ft_vect_int1.begin();
	// for(ft_it = ft_vect_int1.begin(); ft_it != ft_vect_int1.end(); ++ft_it)
	// 	std::cout << *ft_it << std::endl;
	// print_vector(std_vect_int.begin(),std_vect_int.end(),
	// ft_vect_int1.begin(), ft_vect_int1.end());
	std::cout << ft_vect_int.max_size() << std::endl;
	std::cout << std_vect_int.max_size() << std::endl;

	
	std::vector<int> std_vect_int2; 
	ft::vector<int> ft_vect_int2;
	std::cout << ft_vect_int2.capacity() << std::endl;
	std::cout << std_vect_int2.capacity() << std::endl;
	
	std_vect_int2.reserve(19);
	ft_vect_int2.reserve(19);
	std::cout << ft_vect_int2.capacity() << std::endl;
	std::cout << std_vect_int2.capacity() << std::endl;
}