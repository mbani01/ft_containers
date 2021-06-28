

#include <list>
#include <iostream>
#include "list/list.hpp"
#include <iterator>


void print_list(std::list<int>::iterator std_it_b, std::list<int>::iterator std_it_e,
ft::list<int>::iterator ft_it_b, ft::list<int>::iterator ft_it_e)
{
	// std::list<int>::iterator  std_it(std_list_int.begin());
	// ft::list<int>::iterator  ft_it(ft_list_int.begin());
	std::cout << "ft  :: ";
	for(; ft_it_b != ft_it_e ; ++ft_it_b)
		std:: cout << *ft_it_b << " ";;
	std::cout << std::endl << "std :: ";
	for(; std_it_b != std_it_e ; ++std_it_b)
		std:: cout << *std_it_b << " ";;
	std::cout << std::endl;
}

void print_rev(std::list<int>::reverse_iterator std_it_rb, std::list<int>::reverse_iterator std_it_re,
ft::list<int>::reverse_iterator ft_it_rb, ft::list<int>::reverse_iterator ft_it_re)
{
	std::cout << "Printing list using reverse_iterator !" << std::endl;
	std::cout << "ft  :: ";
	for(; ft_it_rb != ft_it_re ; ++ft_it_rb)
		std:: cout << *ft_it_rb << " ";;
	std::cout << std::endl << "std :: ";
	for(; std_it_rb != std_it_re ; ++std_it_rb)
		std:: cout << *std_it_rb << " ";;
	std::cout << std::endl; 
}

int main()
{
	
/*	======================> init and iterators tests <============================  */

	std::cout << "	======================>\033[1;31m init and iterators tests \033[0m<============================ " << std::endl;
	// Creating lists of diffrent types
	std::list<int> std_list_int; 
	std::list<int>::iterator  std_it(std_list_int.begin());
	// ft::list<int> list_1(10, 5);
	ft::list<char> ft_list_char(5, 'a');
	std::list<char> std_list_char;
	ft::list<float> ft_list_float;
	std::list<float> std_list_float;
	
	
	// init stdlist with value from 0 to 9
	// int i = 0;
	for(int i = 0; i < 10; ++i) 
		std_list_int.push_back(i);
	std::cout << "last ele :" << *--std_it << std::endl;

	ft::list<int> ft_list_int1(std_list_int.begin(), std_list_int.end());
	ft::list<int> ft_list_int;

	//test opeartor= 
	ft_list_int = ft_list_int1;

	ft::list<int>::iterator  ft_it(ft_list_int.begin());
	print_list(std_list_int.begin(),std_list_int.end(),
	ft_list_int.begin(), ft_list_int.end());

	ft_it = ft_list_int.begin();
	std_it = std_list_int.begin();
	*ft_it = 100;
	*std_it = 100;
	std::cout << "ft   :" << *ft_it << std::endl;
	std::cout << "std   :" << *std_it << std::endl;
	ft_it++;
	--ft_it;
	std_it++;
	--std_it;
	std::cout << "first ele value :" << *ft_it << std::endl;
	if (ft_it == ft_list_int.end()) //check opeartor==
		std::cout << "This should not be printed " << std::endl;
	if (ft_it != ft_list_int.end()) //check opeartor!=
		std::cout << "iter is diff than list end" << std::endl;

	ft::list<int>::const_iterator ft_c_it;
	ft_c_it = ft_it;
	ft_c_it++;
	std::cout << "dereferencing const iter :" << *ft_c_it << std::endl;
	// *ft_c_it = 60; //trying to assign to const iterator should generate compiling error
	
	//reverse iterators
	print_list(std_list_int.begin(),std_list_int.end(),
	ft_list_int.begin(), ft_list_int.end());
	ft::list<int>::reverse_iterator ft_rev_it(ft_list_int.rend());
	std::list<int>::reverse_iterator std_rev_it(std_list_int.rend());
	std::cout << std::endl;
	std::cout  << "ft rev_iter dereferencing  :" << *(--ft_rev_it) << std::endl;
	std::cout << "std rev_iter dereferencing :" << *(--std_rev_it) << std::endl;
	std::cout << std::endl;
	print_rev(std_list_int.rbegin(), std_list_int.rend(), ft_list_int.rbegin(), ft_list_int.rend());

	// intialize rev_it with an iterator
	ft::list<int>::reverse_iterator ft_rev_it1(ft_list_int.end());
	std::list<int>::reverse_iterator std_rev_it1(std_list_int.end());
	if ((ft_rev_it1 == ft_list_int.rbegin()) && (std_rev_it1 == std_list_int.rbegin()))
		std::cout << "initializing  a rev_iter with an iterator is working ^_^\n";


	//const reverse iterators
	ft::list<int>::const_reverse_iterator ft_rev_cit(ft_list_int.rbegin());
	std::list<int>::const_reverse_iterator std_rev_cit(std_list_int.rbegin());
	std::cout << "rbegin std : " << *std_rev_cit << std::endl << "rbegin ft  : " << *ft_rev_cit << std::endl; 
	// *std_rev_cit = 10; // assign to const rev_iter (compile error)

/*	======================> member functions test <============================  */
	std::cout << "	======================>\033[1;31m member functions tests \033[0m<============================" << std::endl;

	ft::list<int> ft_emp;
	std::list<int> std_emp;
	std::cout << "ft empty  : " << ft_list_int.empty() << std::endl;
	std::cout << "std empty : " << std_list_int.empty() << std::endl;
	std::cout << "ft empty  : " << ft_emp.empty() << std::endl;
	std::cout << "std empty : " << std_emp.empty() << std::endl;

	std::cout << std::endl;

	std::cout << "ft size  : " << ft_list_int.size() << std::endl;
	std::cout << "std size : " << std_list_int.size() << std::endl;
	std::cout << "ft size  : " << ft_emp.size() << std::endl;
	std::cout << "std size : " << std_emp.size() << std::endl;

	std::cout << std::endl;

	std::cout << "ft max_size  : " << ft_list_int.max_size() << std::endl;
	std::cout << "std max_size : " << std_list_int.max_size() << std::endl;

	std::cout << std::endl;

	std::cout << "ft front  : " << ft_list_int.front() << std::endl;
	std::cout << "std front : " << std_list_int.front() << std::endl;
	std::cout << "ft front  : " << ft_emp.front() << std::endl;
	std::cout << "std front : " << std_emp.front() << std::endl;

	std::cout << std::endl;

	print_list(std_list_int.begin(),std_list_int.end(),
	ft_list_int.begin(), ft_list_int.end());

	std::cout << "ft back  : " << ft_list_int.back() << std::endl;
	std::cout << "std back : " << std_list_int.back() << std::endl;

	// std::cout << "ft back  : " << ft_emp.back() << std::endl;
	// std::cout << "std back : " << std_emp.back() << std::endl;
	ft::list<int> new_lst;
	// if (new_lst.begin() == new_lst.end())
	// 	std::cout << "here" ;
	ft_list_int.assign(new_lst.begin(), new_lst.end()); 
	std::cout << ft_list_int.size() ;
/*
	 should  free node before head in opeartor= 
*/
// while (1);
}
