

#include <list>
#include <iostream>
#include "list/list.hpp"
#include <iterator>

int main()
{
	// Creating lists of diffrent types
	
	std::list<int> std_list_int(10, 0); 
	std::list<int>::iterator  std_it(std_list_int.begin());
	ft::list<char> ft_list_char(5, 'a');
	std::list<char> std_list_char;
	ft::list<float> ft_list_float;
	std::list<float> std_list_float;
	
	
	// init stdlist with value from 0 to 9
	int i = 0;
	for(std_it = std_list_int.begin(); std_it != std_list_int.end(); ++std_it) 
		*std_it = i++;
	std::cout << "last ele :" << *--std_it << std::endl;

	ft::list<int> ft_list_int(std_list_int.begin(), std_list_int.end());
	ft::list<int>::iterator  ft_it(ft_list_int.begin());

	
	std::cout << "ft  :: ";
	for(ft_it = ft_list_int.begin(); ft_it != ft_list_int.end(); ++ft_it)
		std:: cout << *ft_it ;
	std::cout << std::endl << "std :: ";
	for(std_it = std_list_int.begin(); std_it != std_list_int.end(); ++std_it)
		std:: cout << *std_it ;
	std::cout << std::endl;

	ft_it = ft_list_int.begin();
	*ft_it = 100;
	std::cout << ft_it->operator*() << std::endl;
	ft_it++;
	--ft_it;
	std::cout << ft_it->operator*() << std::endl;
	if (ft_it == ft_list_int.end())
		std::cout << "This should not be printed " << std::endl;
	if (ft_it != ft_list_int.end())
		std::cout << "iter is diff than list end" << std::endl;

	ft::list<int>::const_iterator ft_c_it;
	ft_c_it = ft_it;
	ft_c_it++;
	std::cout << *ft_c_it << std::endl;
	// *ft_c_it = 60; //trying to assign to const iterator should generate compiling error
	
	//reverse iterators

	// ft::list<int>::reverse_iterator ft_rev_it(ft_list_int.begin());
	std::list<int>::reverse_iterator std_rev_it(std_list_int.begin());
	std::list<int>::reverse_iterator std_rev_ite(std_list_int.rend());

	if (std_rev_it == std_rev_ite)
		std::cout << "true \n";


/*
first node should be added (rend)

*/



	// std_rev_it = std_it;
	std::cout << std::endl;
	// std::cout  << *ft_rev_it << std::endl;
	std::cout << *--std_rev_it << std::endl;
	// std::cout << *(ft_list_int.begin()) << " " << *ft_rev_it << std::endl;


	
}
