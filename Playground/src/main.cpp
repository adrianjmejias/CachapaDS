
#include <iostream>
#include <cds/FibHeap.h>


#include <queue>


struct Dummy {
	std::string _name;

	Dummy(std::string name) : _name(name){

	}
};

struct DummyComparator {
	bool operator()() {
		//return a.name < b.name;
		
		std::cout << "lfunctor " << std::endl;
		return true;
	}
};
int main() 
{
	cds::FibHeap < Dummy, DummyComparator()> fib;

	std::priority_queue<int> q;
	
	fib.empty();

	fib.push(Dummy("jejejee"));

	std::cin.ignore();

}