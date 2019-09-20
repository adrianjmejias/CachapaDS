
#include <iostream>

#include <cds/FibHeap.h>
#include <cds/BinHeap.h>
#include <cds/BinaryHeap.h>
#include <memory>


#define CDS_ASSERT(x) if(!(x)){\
std::cout<<#x<<std::endl;\
std::cout<<__LINE__<<std::endl;\
}\


struct Dummy {
	std::string name;
};


struct DummyBinHeap {
	int _val;
	DummyBinHeap(int val): _val(val) {}
};

int main()
{
	std::unique_ptr<cds::AbstractHeap<DummyBinHeap> > heaps[] = {
		std::make_unique<cds::FibHeap<DummyBinHeap>>([](DummyBinHeap a, DummyBinHeap b)-> bool {return a._val < b._val; }),
		std::make_unique<cds::BinHeap<DummyBinHeap>>([](DummyBinHeap a, DummyBinHeap b)-> bool {return a._val < b._val; }),
		std::make_unique<cds::BinaryHeap<DummyBinHeap>>([](DummyBinHeap a, DummyBinHeap b)-> bool {return a._val > b._val; }),
	};

	for (size_t ii = 2; ii < 3; ii++)
	{
		auto heap = heaps[ii].get();

		for (int ii = 0; ii < 100; ii++) {
			heap->emplace(ii);
			std::cout << "Top :" << heap->top()._val << std::endl;
		}

		while (!heap->empty())
		{
			//std::cout << "Size :" << heap->size() << std::endl;
			std::cout << "Top :" << heap->top()._val << std::endl;
			heap->pop();
		}
	}

	std::cin.ignore();



	


}