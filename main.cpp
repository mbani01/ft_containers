

#include <list>
#include <iostream>
#include "list/list.hpp"
#include <iterator>

int main()
{
	std::list <int> lst(5, 5);
	int i = 0;
	std::list<int>::iterator it;
	for(it = lst.begin();it != lst.end(); ++it)
	{
		*it = i++;
		if (i == 5)
			break;
	}


	ft::list <int> lst1(lst.begin(), lst.end());
	// ft::list<int>::iterator it1(lst1.begin());
	ft::list<int>::const_iterator  it3(lst1.begin());
	// it3 = lst1.begin();
	std::cout << *it3 << std::endl;
	// while(++it1 != lst1.end())
	// 	std::cout << *it1 << std::endl;
	// it3 = lst1.end();
	// it3 = it1;
	// std::cout << *it1++ << std::endl;
	// std::cout << *it1++ << std::endl;
	// while(1)
	// {
	// 	std::cout << ++*it1 << std::endl;
	// 	if (it1 == lst1.end())
	// 		break;
	// }

	std::cout << std::endl;
	std::list <int> lst2(lst.begin(), lst.end());
	std::list<int>::const_iterator it2(lst2.end());
	while(--it2 != lst2.begin())
		std::cout << *it2 << std::endl;
	// it2 = lst2.begin();
	// std::cout << *it2++ << std::endl;
	// std::cout << *it2++ << std::endl;
	// while(1)
	// {
	// 	std::cout << ++*it2 << std::endl;
	// 	if (it2 == lst2.end())
	// 		break;
	// }
	// while(1);

}
