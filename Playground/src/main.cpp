

#include <cds/FibHeap.h>
#include <cds/BinHeap.h>
#include <cds/BinaryHeap.h>

#include <iostream>
#include <chrono>
#include <memory>
#include <random>
#include <functional>


struct DummyBinHeap {
	int _val;
	DummyBinHeap(int val) : _val(val) {}
};

std::ostream& operator<<(std::ostream& out, const DummyBinHeap& d)
{
	out << d._val;
	return out;
}




using timeDT = unsigned long long;

std::vector<DummyBinHeap> GenerateRandom(size_t size, std::function<int()> generator)
{
	std::vector<DummyBinHeap> randVec;
	for (int ii = 0; ii < size; ii++)
	{
		randVec.push_back(DummyBinHeap(generator()));
	}
	return randVec;
}

template <typename durationType>
durationType measureTime(std::function<void()> f)
{
	auto start = std::chrono::system_clock::now();

	f();

	auto end = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}


template <typename TT>
struct TestTimes
{
	TT push = 0;
	TT pop = 0;
	TT sort = 0;
	template <typename OO>
	void add(const TestTimes<OO>& other)
	{
		this->pop += static_cast<TT>(other.pop);
		this->push += static_cast<TT>(other.push);
		this->sort += static_cast<TT>(other.sort);
	}
};

int main()
{
	auto condition = [](DummyBinHeap a, DummyBinHeap b)-> bool {return a._val > b._val; };

	std::unique_ptr<cds::AbstractHeap<DummyBinHeap> > heaps[] = {
		std::make_unique<cds::FibHeap<DummyBinHeap> >(condition),
		std::make_unique<cds::BinHeap<DummyBinHeap> >(condition),
		std::make_unique<cds::BinaryHeap<DummyBinHeap>>(condition),
	};
	

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10000000); // distribution in range [1, 6]

	std::function<int()> randGenerator = [&]() {
		return dist(rng);
	};

	std::vector<int> testCases;
	std::vector<TestTimes<timeDT> > times[3];
	TestTimes<float> avg[3];
	testCases.push_back(1000);
	testCases.push_back(5000);
	testCases.push_back(7500);
	testCases.push_back(10000);
	testCases.push_back(50000);
	testCases.push_back(75000);
	testCases.push_back(100000);
	testCases.push_back(250000);
	testCases.push_back(500000);
	testCases.push_back(750000);
	testCases.push_back(1000000);
	testCases.push_back(1200000);
	//testCases.push_back(5000000);
	//testCases.push_back(10000000);
	//testCases.push_back(50000000);
	//testCases.push_back(100000000);

	for(auto ammount : testCases)
	{
		auto instances = GenerateRandom(ammount, randGenerator);
		int mI = 0;

		for (auto &heap : heaps)
		{
			times[mI].push_back(TestTimes<timeDT>());
			TestTimes<timeDT> &tt = times[mI][times[mI].size() - 1];
			auto tests = instances;

			tt.push = measureTime<timeDT>([&]() {
				for (auto ii : tests)
				{
					heap->push(ii);
				}
			});

			tt.pop = measureTime<timeDT>([&]() {
				while(!heap->empty())
				{
					heap->pop();
				}
			});

			tt.sort = measureTime<timeDT>([&]() {
				cds::AbstractHeap<timeDT>::sort<DummyBinHeap>(tests, heap.get());
			});
			std::cout << "test done: " << ammount << std::endl;
			mI++;
		}
	}

	int mI = 0;
	int nTests = testCases.size();

	for (auto &heap : heaps)
	{
		TestTimes<float> avg;

		for (size_t jj = 0; jj < nTests; jj++)
		{
			auto &tt = times[mI][jj];

			std::cout << "test " << testCases[jj] << std::endl;

			std::cout << "push " << tt.push << std::endl;
			std::cout << "pop " << tt.pop << std::endl;
			std::cout << "sort " << tt.sort << std::endl;
			avg.add<timeDT>(tt);
		}
		std::cout << "avg push " << avg.push << std::endl;
		std::cout << "avg pop " << avg.pop << std::endl;
		std::cout << "avg sort " << avg.sort <<std::endl;
		std::cout << "------" <<std::endl;
		mI++;
	}




	std::cin.ignore();



	


}