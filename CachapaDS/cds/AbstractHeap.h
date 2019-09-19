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
	};






	class Mergeable {

	};


	namespace internal{
		const int LEFT = 0, RIGHT = 1;
		class AbstractNode {

		};
	}


}