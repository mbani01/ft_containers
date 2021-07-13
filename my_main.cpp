/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:51:27 by mbani             #+#    #+#             */
/*   Updated: 2021/07/11 16:46:33 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector/vector.hpp"
#include <vector>


void print_vector(std::vector<int>::iterator std_it_b, std::vector<int>::iterator std_it_e,
ft::vector<int>::iterator ft_it_b, ft::vector<int>::iterator ft_it_e)
{
	std::cout << "ft  :: ";
	for(; ft_it_b != ft_it_e ; ++ft_it_b)
	 {
		std:: cout << *ft_it_b << " ";
	 }
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
	ft::vector<int>::const_iterator ft_itc(vect_1.end());
	std::vector<int>::const_iterator std_itc(std_vect_int.end());

	// *ft_itc = 8;
	// *std_itc = 8;

	for(int i = 0; i < 10; ++i)
		std_vect_int.push_back(i);
	ft::vector<int> ft_vect_int1(std_vect_int.begin(), std_vect_int.end()); // call range constructor 

	ft_it = ft_vect_int1.begin();
	for(ft_it = ft_vect_int1.begin(); ft_it != ft_vect_int1.end(); ++ft_it)
		std::cout << *ft_it << std::endl;
	print_vector(std_vect_int.begin(),std_vect_int.end(),
	ft_vect_int1.begin(), ft_vect_int1.end());
	std::cout << "	======================>\033[1;31m member functions tests \033[0m<============================ " << std::endl;
	
	std::cout << ft_vect_int.max_size() << std::endl;
	std::cout << std_vect_int.max_size() << std::endl;

	std::vector<int> std_vect_int2; 
	for(int i = 0; i < 100; i += 20)
		std_vect_int2.push_back(i);
	ft::vector<int> ft_vect_int2(std_vect_int2.begin(), std_vect_int2.end());
	std::cout << "ft capacity " << ft_vect_int2.capacity() << std::endl;
	std::cout << "std capacity " << std_vect_int2.capacity() << std::endl;
	
	print_vector(std_vect_int2.begin(),std_vect_int2.end(),
	ft_vect_int2.begin(), ft_vect_int2.end());
	
	// std::cout <<" size  :"<< ft_vect_int2.end() - ft_vect_int2.begin() << std::endl;
	ft_vect_int2.reserve(50);
	std_vect_int2.reserve(50);

	std::cout << "ft capacity " << ft_vect_int2.capacity() << std::endl;
	std::cout << "std capacity " << std_vect_int2.capacity() << std::endl;
	
	print_vector(std_vect_int2.begin(),std_vect_int2.end(),
	ft_vect_int2.begin(), ft_vect_int2.end());
	try
	{
		/* code */
	// std_vect_int2.reserve(46116860184273879);
	// ft_vect_int2.reserve(4611686018427387999);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	std::cout << "ft capacity " << ft_vect_int2.capacity() << std::endl;
	std::cout << "std capacity " << std_vect_int2.capacity() << std::endl;

	ft_vect_int1[8] = 19;
	std_vect_int[8] = 19;
	std::cout << ft_vect_int1[8] << std::endl;
	std::cout << std_vect_int[8] << std::endl;
	
	ft_vect_int1[0] = 100;
	std_vect_int[0] = 100;
	std::cout << ft_vect_int1.back() << std::endl;
	std::cout << std_vect_int.back() << std::endl;

	std::vector<int> std_new(25, 0);
	ft::vector<int> ft_new(25, 0);

	// std_new.push_back(100);
	// std_new.push_back(200);
	// std_new.push_back(300);
	// std_new.push_back(300);
	// std_new.push_back(300);

	std::cout << "capacity : " << std_new.capacity() << std::endl;
	std::cout << "size :" << std_new.size() << std::endl;

	// std_vect_int2.assign(12, 10);
	
	std::cout << "vect 2capacity : " << std_vect_int2.capacity() << std::endl;
	std::cout << "vect 2 size :" << std_vect_int2.size() << std::endl;

	std_new.assign(std_vect_int2.begin(), std_vect_int2.end());
	ft_new.assign(std_vect_int2.begin(), std_vect_int2.end());


	std::cout << "std capacity : " << std_new.capacity() << std::endl;
	std::cout << "std size :" << std_new.size() << std::endl;
	std::cout << "ft capacity : " << ft_new.capacity() << std::endl;
	std::cout << "ft size :" << ft_new.size() << std::endl;

	print_vector(std_new.begin(),std_new.end(),
	ft_new.begin(), ft_new.end());

	std_new.assign(10, 0);
	ft_new.assign(10, 0);

	print_vector(std_new.begin(),std_new.end(),
	ft_new.begin(), ft_new.end());
	
	std::cout << "std capacity : " << std_new.capacity() << std::endl;
	std::cout << "std size :" << std_new.size() << std::endl;
	std::cout << "ft capacity : " << ft_new.capacity() << std::endl;
	std::cout << "ft size :" << ft_new.size() << std::endl;
	
	std_new.assign(20, 1);
	ft_new.assign(20, 1);
	
	print_vector(std_new.begin(),std_new.end(),
	ft_new.begin(), ft_new.end());
	
	std::cout << "std capacity : " << std_new.capacity() << std::endl;
	std::cout << "std size :" << std_new.size() << std::endl;
	std::cout << "ft capacity : " << ft_new.capacity() << std::endl;
	std::cout << "ft size :" << ft_new.size() << std::endl;

	std::vector<int> std_new1(10, 0);
	ft::vector<int> ft_new1(10, 0);

	// std_new1.reserve(100);
	// ft_new1.reserve(100);
	for (int i = 0; i < 2; ++i)
	{
		std_new1.push_back(i);
		ft_new1.push_back(i);
	}
	print_vector(std_new1.begin(),std_new1.end(),
	ft_new1.begin(), ft_new1.end());
	
	std::cout << "std capacity : " << std_new1.capacity() << std::endl;
	std::cout << "std size :" << std_new1.size() << std::endl;
	std::cout << "ft capacity : " << ft_new1.capacity() << std::endl;
	std::cout << "ft size :" << ft_new1.size() << std::endl;


	std::vector<int> std_new2;
	ft::vector<int> ft_new2;

	std::cout << std::endl;
	// std_new2.reserve(1);
	// ft_new2.reserve(1);
	std::vector<int>::iterator std_it2(std_new2.begin());
	ft::vector<int>::iterator ft_it2(ft_new2.begin());
	
	// std_new2.push_back(50);
	// ft_new2.push_back(50);
	
	// std_it2 = std_new2.begin();
	// ft_it2 = ft_new2.begin();
	
	// ft_it2++;
	// std_it2++;
	// std::cout << *ft_it2 << std::endl;
	// std::cout << *std_it2 << std::endl;

	std_new2.insert(std_it2, 900);
	ft_new2.insert(ft_it2, 900);
	std_it2++;
	ft_it2++;
	std::cout << '\n';
	std_it2 = std_new2.begin();
	ft_it2 = ft_new2.begin();
	std_new2.insert(std_it2, 100);
	ft_new2.insert(ft_it2, 100);
		std_it2 = std_new2.begin();
	ft_it2 = ft_new2.begin();
	std_new2.insert(std_it2, 10);
	ft_new2.insert(ft_it2, 10);
		std_it2 = std_new2.begin();
	ft_it2 = ft_new2.begin();
	std_new2.insert(std_it2, 20);
	ft_new2.insert(ft_it2, 20);
	// std_it2--;
	// ft_it2--;
	std_it2 = std_new2.end();
	ft_it2 = ft_new2.end();
	// std_it2++;
	// ft_it2++;
	std::cout << *(std_new2.insert(std_it2, 800))<< std::endl;
	std::cout << *(ft_new2.insert(ft_it2, 800))<< std::endl;
	print_vector(std_new2.begin(),std_new2.end(),
	ft_new2.begin(), ft_new2.end());
	std::cout << "std capacity : " << std_new2.capacity() << std::endl;
	std::cout << "std size :" << std_new2.size() << std::endl;
	std::cout << "ft capacity : " << ft_new2.capacity() << std::endl;
	std::cout << "ft size :" << ft_new2.size() << std::endl << std::endl;

	print_vector(std_new2.begin(),std_new2.end(),
	ft_new2.begin(), ft_new2.end());
	std_it2 = std_new2.begin();
	ft_it2 = ft_new2.begin();
	// std_it2--;
	// ft_it2--;

	std_new2.insert(std_it2, 1, 55);
	ft_new2.insert(ft_it2, 1, 55);
		print_vector(std_new2.begin(),std_new2.end(),
	ft_new2.begin(), ft_new2.end());
	std_it2 = std_new2.begin();
	ft_it2 = ft_new2.begin();
	std_it2++;
	ft_it2++;
	std_new2.insert(std_it2, 190);
	ft_new2.insert(ft_it2, 190);
	print_vector(std_new2.begin(),std_new2.end(),
	ft_new2.begin(), ft_new2.end());
	std::cout << "std capacity : " << std_new2.capacity() << std::endl;
	std::cout << "std size :     " << std_new2.size() << std::endl;
	std::cout << "ft capacity :  " << ft_new2.capacity() << std::endl;
	std::cout << "ft size :      " << ft_new2.size() << std::endl << std::endl;

	std::vector<int> std_new3(1, 0);
	ft::vector<int> ft_new3(1, 0);
	std_new3.reserve(10);
	ft_new3.reserve(10);
	// ft_new3.push_back(10);
	// ft_new3.push_back(20);
	// ft_new3.push_back(30);
	// ft_new3.push_back(40);
	// std_new3.push_back(10);
	// std_new3.push_back(20);
	// std_new3.push_back(30);
	// std_new3.push_back(40);
	std_new3.insert(std_new3.begin(), std_new2.begin(), std_new2.end());
	ft_new3.insert(ft_new3.begin(), std_new2.begin(), std_new2.end());

	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	std::cout << "std capacity : " << std_new3.capacity() << std::endl;
	std::cout << "std size :" << std_new3.size() << std::endl;
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl << std::endl;
}