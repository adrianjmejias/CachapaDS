#pragma once
#include "AbstractHeap.h"
#include <vector>

namespace cds {

	template <typename TT>
	class BinaryHeap : public AbstractHeap<TT>
	{
	private:
		using DataContainer = std::vector<TT>;
		DataContainer elements;


		int _l(int idx)
		{
			return idx << 1+ 1;
		}
		int _r(int idx) {
			return _l(idx) + 1;
		}
		int _p(int idx)
		{
			return (idx - 1) / 2;
		}

		void _Sink(int e)
		{
			//while (2 * k <= n) {
			//	int j = 2 * k;

			//	if (j < n && A[j]<A[j + 1]) j++;
			//	if (A[k] >= A[j]) break;
			//	swap(A[k], A[j]);
			//	k = j;
			//}
		}
		void _Float(int k)
		{
			
			//while (
			//	(int pIndex = _p(k) >=0) // exists parent
			//	&& _compare(elements[k], elements[pIndex])
			//	)
			//{




			//}
		}

	public:
		virtual const TT& top() const 
		{
			// TODO: throw exception if empty
			//return elements[0];
		};


		virtual void push(const TT& data) 
		{

			//elements.push_back(data);
			////_Float(size);
			//_size++;

		};

		virtual void pop() 
		{
		/*	std::swap(elements[0], elements[_size - 1]);
			_size--;*/
			//_Sink(0);
		};
	};

}