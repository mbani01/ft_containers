/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 12:35:52 by mbani             #+#    #+#             */
/*   Updated: 2021/09/19 14:21:50 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#if 1
#include "vector/vector.hpp"
#else
#include <vector>
namespace ft = std;
#endif
	// helper functions 

bool mypredicate (int i, int j) 
	{return (i==j);}

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }


void print_vector(ft::vector<int>::iterator ft_it_b, ft::vector<int>::iterator ft_it_e)
{
	std::cout << "ft  :: ";
	for(; ft_it_b != ft_it_e ; ++ft_it_b)
	 {
		std:: cout << *ft_it_b << " ";
	 }
	std::cout << std::endl;
}

int main(void)
{
    	std::cout << "	======================>\033[1;31m init and iterators tests \033[0m<============================ " << std::endl;
	// Creating vects of diffrent types

	ft::vector<int> ft_vect_int; // call default constructor 
	ft::vector<int> vect_1(10, 5); // call fill constructor
	ft::vector<char> ft_vect_char(5, 'a');
	ft::vector<float> ft_vect_float;ft::vector<int>::iterator ft_it;
	ft::vector<char>::iterator ft_it_char(ft_vect_char.begin());
	ft::vector<int>::const_iterator ft_itc(vect_1.end());

	(void)ft_it_char;
	// std_it = ft_itc;
	ft_itc = ft_it;

	// *ft_itc = 8;
	// *std_itc = 8;

	std::cout << (ft_itc == ft_it) << std::endl;
	std::cout << (ft_itc != ft_it) << std::endl << std::endl;

	for(int i = 0; i < 10; ++i)
		ft_vect_int.push_back(i);
	ft::vector<int> ft_vect_int1(ft_vect_int.begin(), ft_vect_int.end()); // call range constructor 

	ft_it = ft_vect_int1.begin();
	for(ft_it = ft_vect_int1.begin(); ft_it != ft_vect_int1.end(); ++ft_it)
		std::cout << *ft_it << std::endl;


	std::cout << "	======================>\033[1;31m member functions tests \033[0m<============================ " << std::endl;

	std::cout << ft_vect_int.max_size() << std::endl;

	ft::vector<int> ft_vect_int2; 
	for(int i = 0; i < 100; i += 20)
		ft_vect_int2.push_back(i);
	std::cout << "Capacity: " << ft_vect_int2.capacity() << std::endl;
	
	print_vector(ft_vect_int2.begin(), ft_vect_int2.end());

	ft_vect_int2.reserve(50);

	std::cout << "Capacity: " << ft_vect_int2.capacity() << std::endl;
	
	print_vector(ft_vect_int2.begin(), ft_vect_int2.end());
	try
	{
	// ft_vect_int2.reserve(4611686018427387999);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	std::cout << "Capacity:  " << ft_vect_int2.capacity() << std::endl;

	ft_vect_int1[8] = 19;
	std::cout << ft_vect_int1[8] << std::endl;
	
	ft_vect_int1[0] = 100;
	std::cout << ft_vect_int1.back() << std::endl;

	ft::vector<int> ft_new(25, 0);
	
	std::cout << "vect 2 Capacity : " << ft_vect_int2.capacity() << std::endl;

	ft_new.assign(ft_vect_int2.begin(), ft_vect_int2.end());

	std::cout << "Capacity:  : " << ft_new.capacity() << std::endl;
	std::cout << "Size: " << ft_new.size() << std::endl;

	print_vector(ft_new.begin(), ft_new.end());

	ft_new.assign(10, 0);

	print_vector(ft_new.begin(), ft_new.end());
	
	std::cout << "Capacity:  : " << ft_new.capacity() << std::endl;
	std::cout << "Size: " << ft_new.size() << std::endl;
	
	ft_new.assign(20, 1);
	
	print_vector(ft_new.begin(), ft_new.end());
	
	std::cout << "Capacity:  : " << ft_new.capacity() << std::endl;
	std::cout << "Size: " << ft_new.size() << std::endl;

	ft::vector<int> ft_new1(10, 0);

	// ft_new1.reserve(100);
	for (int i = 0; i < 2; ++i)
		ft_new1.push_back(i);
	print_vector(ft_new1.begin(), ft_new1.end());
	std::cout << "Capacity:  : " << ft_new1.capacity() << std::endl;
	std::cout << "Size: " << ft_new1.size() << std::endl;

	ft::vector<int> ft_new2;
	std::cout << std::endl;
	// ft_new2.reserve(1);
	ft::vector<int>::iterator ft_it2(ft_new2.begin());
	
	// ft_new2.push_back(50);
	// ft_it2 = ft_new2.begin();
	// ft_it2++;
	// std::cout << *ft_it2 << std::endl;

	ft_new2.insert(ft_it2, 900);
	ft_it2++;
	std::cout << std::endl;
	ft_it2 = ft_new2.begin();
	ft_new2.insert(ft_it2, 100);
	ft_it2 = ft_new2.begin();
	ft_new2.insert(ft_it2, 10);
	ft_it2 = ft_new2.begin();
	ft_new2.insert(ft_it2, 20);
	// ft_it2--;
	ft_it2 = ft_new2.end();
	// std_it2++;
	// ft_it2++;
	std::cout << *(ft_new2.insert(ft_it2, 800))<< std::endl;
	print_vector(ft_new2.begin(), ft_new2.end());
	std::cout << "ft capacity : " << ft_new2.capacity() << std::endl;
	std::cout << "ft size :" << ft_new2.size() << std::endl << std::endl;

	print_vector(ft_new2.begin(), ft_new2.end());
	ft_it2 = ft_new2.begin();
	// ft_it2--;

	ft_new2.insert(ft_it2, 1, 55);
		print_vector(ft_new2.begin(), ft_new2.end());
	ft_it2 = ft_new2.begin();
	ft_it2++;
	ft_new2.insert(ft_it2, 190);
	print_vector(ft_new2.begin(), ft_new2.end());
	std::cout << "ft capacity :  " << ft_new2.capacity() << std::endl;
	std::cout << "ft size :      " << ft_new2.size() << std::endl << std::endl;
	

	ft::vector<int> ft_new3(1, 0);
	ft_new3.reserve(10);
	ft_new3.push_back(10);
	ft_new3.push_back(20);
	ft_new3.push_back(30);
	ft_new3.push_back(40);
	ft_new3.insert(ft_new3.begin(), ft_new2.begin(), ft_new2.end());

	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl << std::endl;

	// std::cout << *(ft_new3.erase(ft_new3.end()  - 3)) << std::endl;
	// std::cout << *(ft_new3.erase(ft_new3.begin() + 3, ft_new3.end())) << std::endl;

	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl << std::endl;

	std::cout << "iter " << ft_new3.end() - ft_new3.begin() << std::endl;

	ft::vector<int> ft_new4(20, 0);
	ft_new4 = ft_new3;
	std::cout << "print new4" << std::endl << std::endl;
	print_vector(ft_new4.begin(), ft_new4.end());
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;






	ft_new3.push_back(3333);
	ft_new3.push_back(20);
	ft_new3.push_back(30);
	ft_new3.push_back(3333);
	ft_new3.swap(ft_new4);
	std::cout << "print new4" << std::endl << std::endl;
	print_vector(ft_new4.begin(), ft_new4.end());
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;
	std::cout << "print new3" << std::endl << std::endl;
	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl;

	ft_new4.clear();
	print_vector(ft_new4.begin(), ft_new4.end());
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;
	
	std::cout << std::endl;
	print_vector(ft_new3.begin(), ft_new3.end());
	print_vector(ft_new2.begin(), ft_new2.end());
	ft::swap(ft_new3, ft_new2);
	std::cout << std::endl;
	print_vector(ft_new3.begin(), ft_new3.end());
	print_vector(ft_new2.begin(), ft_new2.end());
	std::cout <<  "ft size :" << ft_new3.size() << "\nft capacity : " << ft_new3.capacity() << std::endl;
	ft_new3.resize(12, 10);
	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout <<  "ft size :" << ft_new3.size() << "\nft capacity : " << ft_new3.capacity() << std::endl;
	ft_new3.resize(13, 6);
	print_vector(ft_new3.begin(), ft_new3.end());
	std::cout << "ft size :" << ft_new3.size() << "\nft capacity : " << ft_new3.capacity() << std::endl;
}