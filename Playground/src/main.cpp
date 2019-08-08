
#include <iostream>

#include <cds/FibHeap.h>
#include <cds/BinHeap.h>
#include <memory>



struct Dummy {
	std::string name;
};


struct DummyBinHeap {
	int _val;
	DummyBinHeap(int val): _val(val) {}
};

int main() 
{
	std::unique_ptr<cds::AbstractHeap<DummyBinHeap>> heap(new cds::BinHeap<DummyBinHeap>([](DummyBinHeap a, DummyBinHeap b)-> bool {return a._val < b._val; }));

	heap->emplace(0);
	heap->emplace(1);
	heap->emplace(3);
	heap->emplace(7);
	heap->emplace(-30);

	std::cout <<"Size :"<< heap->size() << std::endl;
	std::cout <<"Top :"<< heap->top()._val << std::endl;
	heap->pop();


	std::cout << "Size :" << heap->size() << std::endl;
	std::cout << "Top :" << heap->top()._val << std::endl;
	heap->pop();

	std::cout << "Size :" << heap->size() << std::endl;
	std::cout << "Top :" << heap->top()._val << std::endl;

	std::cin.ignore();

}