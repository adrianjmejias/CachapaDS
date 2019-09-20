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
			return (idx << 1) + 1;
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
			int rIndex;
			int swapWithIndex;
			// if left child exists
			while ((swapWithIndex = _l(e)) < _size)
			{
				rIndex = swapWithIndex + 1;


				//std::cout << "Sink(" << e << ") l->" << swapWithIndex << "    r->" << rIndex << std::endl;
				//std::cout << "Sink(" << elements[e] << ") l->"<< elements[swapWithIndex] <<"    r->"<< elements[rIndex] << std::endl;
				//
				if (rIndex < _size) 
				{
					if (this->_compare(elements[rIndex], elements[swapWithIndex]))
					{
						swapWithIndex = rIndex;
					}
				}


				if (this->_compare(elements[swapWithIndex], elements[e]))
				{
					std::swap(elements[e], elements[swapWithIndex]);
					e = swapWithIndex;
				}
				else
				{
					break;
				}

			}
		}
		void _Float(int k)
		{
			//exists parent
			int pIndex;
			while ((pIndex = _p(k)) >= 0 && _compare(elements[k], elements[pIndex]))
			{
				std::swap(elements[k], elements[pIndex]);
				k = pIndex;
			}
		}

	public:
		BinaryHeap(CompareFn comp) : AbstractHeap(comp) {

		}
		virtual const TT& top() const 
		{
			 // TODO: throw exception if empty
			return elements[0]; 
		};


		virtual void push(const TT& data) 
		{
			elements.push_back(data);
			_size = elements.size();
			_Float(static_cast<int>(_size - 1));
		};

		virtual void pop() 
		{
			std::swap(elements[0], elements[_size - 1]);
			elements.pop_back();
			_size = elements.size();
			_Sink(0);
		};
	};

}