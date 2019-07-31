#pragma once
#include <iostream>


namespace cds{
    template <class TT>
	class FibHeap {
		size_t size = 0;



		class Node {
			const TT &data;
		};



	public:
		bool empty() const;
		size_t size() const;
		const TT& top() const;
		void push(const TT&);

		template <class... Args> void emplace(Args&&... args);
		void pop();

		

	};
	

}