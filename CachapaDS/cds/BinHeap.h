#pragma once
#include "AbstractHeap.h"


namespace cds {

	namespace internal
	{
		template <typename TT>
		class BinHeapNode {
			using Node = BinHeapNode<TT>;
		public:
			std::vector<Node*> childs;
			TT _data;
			BinHeapNode(const TT & data) : _data(data){}
			size_t Order() const { return childs.size(); }

			inline bool HasChildren() {
				return Order() > 0;
			}
			void InsertAsChild(Node* toInsert)
			{
				childs.push_back(toInsert);
			}

		};
	}



	template <typename TT>
	class BinHeap : public AbstractHeap<TT>
	{
		using Node = internal::BinHeapNode<TT>;
		const int NONE = -1;
		int _top{-1};
		std::vector<Node*> roots;

		void _UpdateTop(int a) {
			if (_compare(roots[a]->_data, roots[_top]->_data)) {
				_top = a;
			}
		}

		void _Consolidate() 
		{
			std::vector<Node*> consolidate;
			std::deque<Node*> q(roots.begin(), roots.end());
			
			while (!q.empty()) 
			{
				Node* act = q.front();
				q.pop_front();
				
				// make sure the order for this node exists
				while (act->Order() >= consolidate.size()) { consolidate.push_back(nullptr); }

				Node* &consOrder = consolidate[act->Order()];

				if (consOrder == act) {
					__debugbreak();
				}


				if (consOrder)
				{
					if (_compare(act->_data, consOrder->_data))
					{
						std::swap(act, consOrder);
					}
					
					consOrder->InsertAsChild(act);
					q.push_back(consOrder);
					consOrder = nullptr;
				}
				else 
				{
					consOrder = act;
				}
			}

			consolidate.erase(
				std::remove_if(consolidate.begin(), consolidate.end(), [](Node* a) {return a == nullptr; }),
				consolidate.end()
			);

			roots.assign(consolidate.begin(), consolidate.end());

			if (size() > 0) 
			{
				_top = 0;
				for (int ii = 1, iiEnd = static_cast<int>(consolidate.size()); ii < iiEnd; ii++) {
					_UpdateTop(ii);
				}
			}
			else 
			{
				_top = NONE;
			}


		}
		BinHeap() : AbstractHeap([](const TT& a, const TT&b) {return true; }) {

		}
	public:
		BinHeap(CompareFn comp) : AbstractHeap(comp) {

		}

		const TT& top() const
		{
			return roots[_top]->_data;
		}

		void push(const TT& data)
		{
			Node* nNode = new Node(data);

			if (_top == NONE) {
				_top = 0; //first pos
			}

			roots.push_back(nNode);
			_size++;

			_Consolidate();
		}
		
		void pop()
		{
			
			if (_top == NONE) return;
			Node* poppedTop = roots[_top];
			
			//saco
			std::swap(roots[_top], roots[roots.size() - 1]);
			roots.pop_back();

			//pego hijos


			std::copy(poppedTop->childs.begin(), poppedTop->childs.end(), std::back_inserter(roots));
			_size--;	
			
			_Consolidate();

			delete poppedTop;
		}

		void Merge(const BinHeap& other) {
			std::copy(other.roots.begin(), other.roots.end(), std::back_inserter(roots));
			_size += other.size();
			_Consolidate();
		}

};
}