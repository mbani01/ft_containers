
#include <iostream>
#include <stack>
#include <vector>
#include "vector/vector.hpp"
#include "stack/stack.hpp"
#include "map/map.hpp"
#include <map>
class test
{
	private:
		int *ptr;
	public:
	test(){
		ptr = (int *)malloc(10);
		std::cout << "construction \n";
		};
	test(test const &obj)
	{
		this->ptr = (int *)malloc(10);
	}
	void operator=(test const &obj){
		this->ptr = (int *)malloc(10);
	}
	// void operator!=(test const &obj)
	// {
	// 	return ptr != obj.ptr;
	// }
	void hello(){std::cout << "hello world \n";}
	~test(){
		free(ptr);
		std::cout << "Destructed \n";}
};

// namespace ft = std;



int main()
{

	ft::map<int, std::string> ft_map;

	for(int i = 0; i < 10; ++i)
		ft_map.insert(ft::make_pair<int, std::string>(i, "value"));
	ft::map<int, std::string>::iterator ft_iter(ft_map.begin());
	ft::map<int, std::string>::iterator ft_iter1(ft_map.end());

	// (void)ft_iter;
	// (void)ft_iter1;
	// for(;ft_iter != ft_iter1; ++ft_iter)
		std::cout << ft_iter1->first << " ";
	// std::cout << std::endl;
	// int ind = 1;
	// std::string val = "value";
	// std::pair<int, std::string> tst(ind, val);
	// std::map<int, std::string> mp;
	// // mp.insert(tst);
	// // std::cout << (mp.begin())->first << " " << (mp.begin())->second << std::endl;
	// // tst.first  = 2;
	// // tst.second = "not value";
	// // std::cout << (mp.begin())->first << " " << (mp.begin())->second << std::endl;


	// ft::map<int, std::string> ft_mp;
	// ft::map<int, std::string>::iterator ft_itr;
	// ft_itr = ft_mp.begin();
	// // (void)ft_itr;
	// ft::pair<ft::map<int, std::string>::iterator,bool> result;
	// for (int i = 0; i < 10 ; ++i)
	// {
	// 	result = ft_mp.insert(ft::make_pair<int, std::string>(i, "val"));
	// }
	// ft_itr = ft_mp.end();
	// ft::map<int, std::string>::iterator ft_it1 = ft_mp.begin();
	// *ft_itr--;
	// while(1)
	// {
	// 	ft_itr--;
	// 	if (ft_itr == ft_it1)
	// 		break;
	// 	std::cout<< ft_itr->first << std::endl;
	// }
	// ft_itr++;
	// std::cout << (*ft_itr--).first << std::endl;

	// std::cout << (*ft_itr).first << std::endl;
	// std::cout << "value : " << result.first->first << std::endl;
	// std::cout << "inserted : " << result.second << std::endl;
	// result = ft_mp.insert(ft::make_pair<int, std::string>(5, "val"));
	
	// std::cout << "value : " << result.first->first << std::endl;
	// std::cout << "inserted : " << result.second << std::endl;
	// std::cout << ft_itr->first << std::endl;
	// std::cout << ft_mp.empty() << std::endl;
	// std::cout << ft_mp.size() << std::endl;
	// std::cout << ft_mp.max_size() << std::endl;
	// // test inst;
	// // test obj;
	// ft::stack<int > cnt;
	// // int obj1;
	// ft::stack<int > cnt1;

	// cnt.push(10);
	// cnt1.push(100);

	// std::cout << (cnt == cnt1) << std::endl;
	// // cnt.push(obj);
	// // cnt.push(obj);
	// // std::cout << "pushed to stack " << std::endl;
	// // std::cout << "will be poped\n";
	// // cnt.pop();
	// // std::cout << "poped from stack " << std::endl;





}