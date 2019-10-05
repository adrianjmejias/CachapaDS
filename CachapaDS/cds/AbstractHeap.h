#pragma once

#include <utility>
#include <functional>
#include <queue>


namespace cds {

	template <typename TT>
	class AbstractHeap {
	protected:
		using CompareFn = std::function<bool(const TT&, const TT&)>;
		
		const CompareFn _compare;
		size_t _size = 0;
		AbstractHeap(CompareFn comp): _compare(comp){}
	
	public:
		virtual bool empty() const final{ return _size == 0; };
		virtual size_t size() const final { return _size; };
		virtual const TT& top() const = 0;
		virtual void push(const TT& data) = 0;
		virtual void pop() = 0;
		
		
	

		template <class... Args> 
		void emplace(Args&&... args) {
			push(TT(std::forward<Args>(args)...));
		}

		template <typename II>
		static std::vector<II> sort(std::vector<II> arr, AbstractHeap<II>* h)
		{

			for (const II& item : arr)
			{
				h->push(item);
			}

			arr.clear();

			while (!h->empty())
			{
				arr.push_back(h->top());
				h->pop();
			}

			return arr;
		}
	};





	class Mergeable {
		virtual void Merge(const Mergeable&) = 0;
	};
}