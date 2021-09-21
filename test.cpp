
#include <iostream>
#include <stack>
#include <vector>
// #include "vector/vector.hpp"
#include "stack/stack.hpp"


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
	// test inst;
	// test obj;
	ft::stack<int > cnt;
	// int obj1;
	ft::stack<int > cnt1;

	cnt.push(10);
	cnt1.push(100);

	std::cout << (cnt == cnt1) << std::endl;
	// cnt.push(obj);
	// cnt.push(obj);
	// std::cout << "pushed to stack " << std::endl;
	// std::cout << "will be poped\n";
	// cnt.pop();
	// std::cout << "poped from stack " << std::endl;

}