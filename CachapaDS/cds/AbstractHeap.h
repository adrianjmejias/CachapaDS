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

		template <class... Args> 
		void emplace(Args&&... args) {
			push(TT(std::forward<Args>(args)...));
		}
		virtual void pop() = 0;
	};






	class MergeHeap 
	{
		virtual void Merge(MergeHeap&) = 0;
	};


	namespace internal{
		const int LEFT = 0, RIGHT = 1;
		class AbstractNode {

		};
	}


}