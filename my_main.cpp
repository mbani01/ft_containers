/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:51:27 by mbani             #+#    #+#             */
/*   Updated: 2021/09/15 17:38:48 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector/vector.hpp"
#include <vector>
#include <iterator>


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

bool mypredicate (int i, int j) 
	{return (i==j);}

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }
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
	ft::vector<char>::iterator ft_it_char(ft_vect_char.begin());
	ft::vector<int>::const_iterator ft_itc(vect_1.end());
	std::vector<int>::const_iterator std_itc(std_vect_int.end());

	// std_it = ft_itc;
	ft_itc = ft_it;

	// *ft_itc = 8;
	// *std_itc = 8;

	std::cout << (ft_itc == ft_it) << std::endl;
	std::cout << (ft_itc != ft_it) << std::endl << std::endl;

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
	ft_new3.push_back(10);
	ft_new3.push_back(20);
	ft_new3.push_back(30);
	ft_new3.push_back(40);
	std_new3.push_back(10);
	std_new3.push_back(20);
	std_new3.push_back(30);
	std_new3.push_back(40);
	std_new3.insert(std_new3.begin(), std_new2.begin(), std_new2.end());
	ft_new3.insert(ft_new3.begin(), std_new2.begin(), std_new2.end());

	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	std::cout << "std capacity : " << std_new3.capacity() << std::endl;
	std::cout << "std size :" << std_new3.size() << std::endl;
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl << std::endl;


	// std::cout << *(std_new3.erase(std_new3.end() - 3)) << std::endl;
	// std::cout << *(ft_new3.erase(ft_new3.end()  - 3)) << std::endl;


	// std::cout << *(std_new3.erase(std_new3.begin() + 3, std_new3.end())) << std::endl;
	// std::cout << *(ft_new3.erase(ft_new3.begin() + 3, ft_new3.end())) << std::endl;

	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	std::cout << "std capacity : " << std_new3.capacity() << std::endl;
	std::cout << "std size :" << std_new3.size() << std::endl;
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl << std::endl;

	std::cout << "iter " << ft_new3.end() - ft_new3.begin() << std::endl;

	std::vector<int> std_new4(20, 0);
	ft::vector<int> ft_new4(20, 0);
	std_new4 = std_new3;
	ft_new4 = ft_new3;
	std::cout << "print new4" << std::endl << std::endl;
	print_vector(std_new4.begin(),std_new4.end(),
		ft_new4.begin(), ft_new4.end());
	std::cout << "std capacity : " << std_new4.capacity() << std::endl;
	std::cout << "std size :" << std_new4.size() << std::endl;
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;


	ft_new3.push_back(3333);
	ft_new3.push_back(20);
	ft_new3.push_back(30);
	ft_new3.push_back(3333);
	std_new3.push_back(3333);
	std_new3.push_back(20);
	std_new3.push_back(30);
	std_new3.push_back(3333);
	ft_new3.swap(ft_new4);
	std_new3.swap(std_new4);
	std::cout << "print new4" << std::endl << std::endl;
	print_vector(std_new4.begin(),std_new4.end(),
		ft_new4.begin(), ft_new4.end());
	std::cout << "std capacity : " << std_new4.capacity() << std::endl;
	std::cout << "std size :" << std_new4.size() << std::endl;
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;
	std::cout << "print new3" << std::endl << std::endl;
	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	std::cout << "std capacity : " << std_new3.capacity() << std::endl;
	std::cout << "std size :" << std_new3.size() << std::endl;
	std::cout << "ft capacity : " << ft_new3.capacity() << std::endl;
	std::cout << "ft size :" << ft_new3.size() << std::endl;

	ft_new4.clear();
	std_new4.clear();
	print_vector(std_new4.begin(),std_new4.end(),
		ft_new4.begin(), ft_new4.end());
	std::cout << "std capacity : " << std_new4.capacity() << std::endl;
	std::cout << "std size :" << std_new4.size() << std::endl;
	std::cout << "ft capacity : " << ft_new4.capacity() << std::endl;
	std::cout << "ft size :" << ft_new4.size() << std::endl;

	// ft::vector<int, std_new4.get_allocator()> ft_new5;

	// std::cout << std_new4.get_allocator() == ft_new5 << std::endl;

	
	std::cout << std::endl;
	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	print_vector(std_new2.begin(),std_new2.end(),
		ft_new2.begin(), ft_new2.end());
	ft::swap(ft_new3, ft_new2);
	std::swap(std_new3, std_new2);
	std::cout << std::endl;
	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	print_vector(std_new2.begin(),std_new2.end(),
		ft_new2.begin(), ft_new2.end());

	std::cout << std_new3.size() << " " << std_new3.capacity() << std::endl;
	std::cout << ft_new3.size() << " " << ft_new3.capacity() << std::endl;
	std_new3.resize(12, 10);
	ft_new3.resize(12, 10);
	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	std::cout << std_new3.size() << " " << std_new3.capacity() << std::endl;
	std::cout << ft_new3.size() << " " << ft_new3.capacity() << std::endl;
	std_new3.resize(13, 6);
	ft_new3.resize(13, 6);
	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	std::cout << std_new3.size() << " " << std_new3.capacity() << std::endl;
	std::cout << ft_new3.size() << " " << ft_new3.capacity() << std::endl;

	std::cout << "	======================>\033[1;31m reverse iterator tests \033[0m<============================ " << std::endl << std::endl;

	std::vector<int>::reverse_iterator std_rit(std_new3.end() - 1);


	std_rit--;
	std::cout << *std_rit << std::endl;


	std::cout << "	======================>\033[1;31m Non-member functions tests \033[0m<============================ " << std::endl << std::endl;
	ft::vector<int> foo (3,200);
	ft::vector<int> bar (3,300);

	if (foo == bar)
		std::cout << "equal\n";
	if (foo != bar)
		std::cout << "not equal \n";
	if (foo < bar)
		std::cout << "foo is less than bar" << std::endl;
	if (foo <= bar)
		std::cout << "foo is less than or equal bar" << std::endl;
	if (bar > foo)
		std::cout << "bar is greater than foo" << std::endl;
	if (foo >= bar)
		std::cout << "foo is greater than or equal bar" << std::endl;

	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	ft::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( ft::equal (myvector.begin(), myvector.end(), myints, mypredicate) )
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n"<< std::endl;
  char foo1[]="Apple";
  char bar1[]="apartment";

  std::cout << std::boolalpha;

  std::cout << "Comparing foo1 and bar1 lexicographically (foo1<bar1):\n";

  std::cout << "Using default comparison (operator<): ";
  std::cout << ft::lexicographical_compare(foo1,foo1+5,bar1,bar1+9);
  std::cout << '\n';

  std::cout << "Using mycomp as comparison object: ";
  std::cout << ft::lexicographical_compare(foo1,foo1+5,bar1,bar1+9,mycomp);
  std::cout << '\n';

	std::cout << "	======================>\033[1;31m iteartors arithmetic operations tests \033[0m<============================ " << std::endl << std::endl;
	print_vector(std_new3.begin(),std_new3.end(),
		ft_new3.begin(), ft_new3.end());
	std::cout << "std::size :" << std_new3.size() << " std::capacity :" << std_new3.capacity() << std::endl;
	std::cout << "ft::size  :" <<ft_new3.size() << " ft::capacity  :" << ft_new3.capacity() << std::endl<< std::endl;

	std::vector<int>::iterator std_it3(std_new3.begin());
	ft::vector<int>::iterator ft_it3(ft_new3.begin());

	std::cout << *(4 + std_it3) << std::endl;
	std::cout << *(4 + ft_it3) << std::endl;
	std::cout << *std_it3++ << std::endl;
	std::cout << *ft_it3++ << std::endl;
	std::cout << *(std_it3 + 2) << std::endl;
	std::cout << *(ft_it3 + 2) << std::endl;	
	std::cout << *std_it3 << std::endl;
	std::cout << *ft_it3 << std::endl;
	std::cout << *(std_it3 += 1) << std::endl;
	std::cout << *(ft_it3 += 1) << std::endl;	
	std::cout << *std_it3 << std::endl;
	std::cout << *ft_it3 << std::endl;

	
	std::cout << std::endl;
	std_it3 = std_new3.end();
	ft_it3 = ft_new3.end();
	--std_it3;
	--ft_it3;
	std_it3--;
	ft_it3--;
	std::cout << *std_it3-- << std::endl;
	std::cout << *ft_it3-- << std::endl;
	std::cout << *(std_it3 - 6) << std::endl;
	std::cout << *(ft_it3 - 6) << std::endl;	
	std::cout << *std_it3 << std::endl;
	std::cout << *ft_it3 << std::endl;
	std::cout << *(std_it3 -= 9) << std::endl;
	std::cout << *(ft_it3 -= 9) << std::endl;	
	std::cout << *std_it3 << std::endl;
	std::cout << *ft_it3 << std::endl;
	ft_it3 = ft_new3.begin();
	std_it3 = std_new3.begin();
	std::cout << (ft_new3.end() - ft_it3) << std::endl;
	std::cout << (std_new3.end() - std_it3) << std::endl;
	
	std::cout << std::endl;
	std::cout << (ft_it3 < ft_new3.end()) << std::endl;
	std::cout << (std_it3 < std_new3.end()) << std::endl;
	std::cout << (ft_it3 > ft_new3.end()) << std::endl;
	std::cout << (std_it3 > std_new3.end()) << std::endl;
	std::cout << (ft_it3 <= ft_new3.end()) << std::endl;
	std::cout << (std_it3 <= std_new3.end()) << std::endl;
	std::cout << (ft_it3 >= ft_new3.end()) << std::endl;
	std::cout << (std_it3 >= std_new3.end()) << std::endl;
	std::cout << *(std_it3.base()) << std::endl;
	std::cout << *(ft_it3.base()) << std::endl;
	std::cout << std_it3[4] << std::endl;
	std::cout << ft_it3[4] << std::endl;


	std::cout << std::endl;
	std::vector<int>::reverse_iterator std_rit3(std_new3.end() - 1);
	ft::vector<int>::reverse_iterator ft_rit3(ft_new3.end() - 1);
	std::cout << *std_rit3 << std::endl;
	std::cout << *ft_rit3 << std::endl;
	std_rit3 = std_new3.rbegin();
	ft_rit3 = ft_new3.rbegin();
	std::cout << *std_rit3 << std::endl;
	std::cout << *ft_rit3 << std::endl;	
	std::cout << *(std_rit3 + 8) << std::endl;
	std::cout << *(ft_rit3 + 8) << std::endl;
	++std_rit3;
	++ft_rit3;
	std_rit3++;
	ft_rit3++;
	std::cout << *std_rit3 << std::endl;
	std::cout << *ft_rit3 << std::endl;
	std_rit3 += 5;
	ft_rit3 += 5;
	std::cout << *std_rit3 << std::endl;
	std::cout << *ft_rit3 << std::endl;
	std::cout << *(std_rit3 - 1) << std::endl;
	std::cout << *(ft_rit3 - 1) << std::endl;	
	std::cout << *std_rit3-- << std::endl;
	std::cout << *ft_rit3-- << std::endl;
	std::cout << *--std_rit3 << std::endl;
	std::cout << *--ft_rit3 << std::endl;
	std::cout << *std_rit3 << std::endl;
	std::cout << *ft_rit3 << std::endl;
	std::cout << *(std_rit3 -= 5) << std::endl;
	std::cout << *(ft_rit3 -= 5) << std::endl;

	
	std::cout << std::endl;

	std_rit3 = std_new3.rend();
	ft_rit3 = ft_new3.rend();
	std::cout << std_rit3[1] << std::endl;
	std::cout << ft_rit3[1] << std::endl;


	
	std::cout << *(std_new3.rend() - 2) << std::endl;
	std::cout << *(ft_new3.rend() - 2) << std::endl;
	std::vector<int>::const_reverse_iterator std_crit3(std_new3.end() - 1);
	ft::vector<int>::const_reverse_iterator ft_crit3(ft_new3.end() - 1);

	std::cout << *std_crit3 << std::endl;
	std::cout << *ft_crit3 << std::endl;

	// *std_crit3 = 8;
	// *ft_crit3 = 8;

	std::cout << std::endl;

	std::cout << (ft_rit3 < ft_new3.rend()) << std::endl;
	std::cout << (std_rit3 < std_new3.rend()) << std::endl;
	std::cout << (ft_rit3 <= ft_new3.rend()) << std::endl;
	std::cout << (std_rit3 <= std_new3.rend()) << std::endl;
	std::cout << (ft_rit3 > ft_new3.rend()) << std::endl;
	std::cout << (std_rit3 > std_new3.rend()) << std::endl;
	std::cout << (ft_rit3 >= ft_new3.rend()) << std::endl;
	std::cout << (std_rit3 >= std_new3.rend()) << std::endl;
	std::cout << (ft_rit3 != ft_new3.rend()) << std::endl;
	std::cout << (std_rit3 != std_new3.rend()) << std::endl;
	std::cout << (ft_rit3 == ft_new3.rend()) << std::endl;
	std::cout << (std_rit3 == std_new3.rend()) << std::endl;

	std_rit3 = std_new3.rbegin();
	ft_rit3 = ft_new3.rbegin();
	std::cout << *(8 + std_rit3) << std::endl;
	std::cout << *(8 + ft_rit3) << std::endl;

	std::cout << ft_new3.rbegin() - ft_new3.rend() << std::endl;
	std::cout << std_new3.rbegin() - std_new3.rend() << std::endl;

}
