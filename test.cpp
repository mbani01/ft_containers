
#include <iostream>
#include <stack>
#include <vector>
// #include "vector/vector.hpp"
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


int main()
{
	int ind = 1;
	std::string val = "value";
	std::pair<int, std::string> tst(ind, val);
	std::map<int, std::string> mp;
	// mp.insert(tst);
	// std::cout << (mp.begin())->first << " " << (mp.begin())->second << std::endl;
	// tst.first  = 2;
	// tst.second = "not value";
	// std::cout << (mp.begin())->first << " " << (mp.begin())->second << std::endl;


	ft::map<int, std::string> ft_mp;
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