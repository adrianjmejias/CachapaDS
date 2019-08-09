#pragma once
#include "AbstractHeap.h"


namespace cds {

	namespace internal
	{
		template <typename TT>
		class FibHeapNode {
			using Node = FibHeapNode<TT>;
			Node *_parent{ nullptr };
			size_t _order{ 0 };
			bool _dishonor{ false };

		public:

			FibHeapNode(const TT & data) : _data(data) {}
			Node *_left{ this };
			Node *_right{ this };
			Node *_leftmostChild{ nullptr };
			TT _data;


			size_t Order() const { return _order; }

			/*
				uno 2 nodos.
			*/
			inline static void Link(Node* left, Node* right) {
				left->_right = right;
				right->_left = left;
			}
			inline void LinkL(Node* left) {
				Link(left, this);
			}
			inline void LinkR(Node* right) {
				Link(this, right);
			}

			inline bool HasChildren() {
				return Order() > 0;
			}
			void InsertAsChild(Node* toInsert)
			{
				Node* oldLeftest = _leftmostChild;
				_leftmostChild = toInsert;
				_leftmostChild->_parent = this;
				if (oldLeftest)
				{
					oldLeftest->InsertAsBrother(toInsert);
				}
				else
				{
					_leftmostChild->_left = _leftmostChild;
					_leftmostChild->_right = _leftmostChild;
				}


				_order++;
			}
			void InsertAsBrother(Node* toInsert)
			{
				Link(this->_left, toInsert);
				Link(toInsert, this);
				toInsert->_parent = _parent;
			}

			void JoinBrothers() {
				Link(this->_left, this->_right);
			}

			std::tuple<Node*, Node*> PopPreparation() {
				Node* leftmost = _leftmostChild;
				Node* rightmost = _leftmostChild->_left; // es una lista circular XD

				int order = static_cast<int>(_order);
				Node* aux = _leftmostChild;
				while (order-- > 0) {
					aux->_dishonor = false;
					aux->_parent = nullptr;
					aux = aux->_right;
				}


				return std::make_tuple(leftmost, rightmost);
			}
		};
	}



	template <typename TT>
	class FibHeap : public AbstractHeap<TT>
	{
		using Node = internal::FibHeapNode<TT>;
		Node* _top{ nullptr };


		void _UpdateTop(Node* a) {
			if (_compare(a->_data, _top->_data)) {
				_top = a;
			}
		}

		void _Consolidate()
		{
			std::vector<Node*> consolidate;
			std::queue<Node*> q;

			Node* aux = _top->_right;

			q.push(_top);

			// lleno con todos los root nodes
			while (aux != _top) {
				q.push(aux);
				aux = aux->_right;
			}

			while (!q.empty())
			{
				Node* act = q.front();
				q.pop();

				// make sure the order for this node exists
				while (act->Order() >= consolidate.size()) { consolidate.push_back(nullptr); }

				Node* &consOrder = consolidate[act->Order()];

				if (consOrder)
				{
					if (_compare(act->_data, consOrder->_data))
					{
						std::swap(act, consOrder);
					}

					consOrder->InsertAsChild(act);
					q.push(consOrder);
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

			for (int ii = 0, iiEnd = static_cast<int>(consolidate.size()) - 1; ii < iiEnd; ii++) {
				Node* l = consolidate[ii];
				Node* r = consolidate[ii + 1];
				_UpdateTop(l);
				l->LinkR(r);
			}
			//cerrando lista circular
			Node* last = consolidate[consolidate.size() - 1];
			Node* first = consolidate[0];
			_UpdateTop(last);
			last->LinkR(first);
		}

	public:
		FibHeap(CompareFn comp) : AbstractHeap(comp) {

		}
		const TT& top() const
		{
			return _top->_data;
		}
		void push(const TT& data)
		{
			Node* toInsert = new Node(data);
			if (_top)
			{
				_top->InsertAsBrother(toInsert);
				_UpdateTop(toInsert);
			}
			else
			{
				_top = toInsert;
			}

			_size++;
		}

		void pop()
		{
			Node *poppedTop = _top;

			if (!poppedTop) return;

			// Si no es el unico root node
			if (poppedTop->_left != poppedTop)
			{
				// ningun root node tiene referencia a el
				if (poppedTop->HasChildren())
				{
					Node* wrapLeft{ poppedTop->_left };
					Node* wrapRight{ poppedTop };

					auto[leftmost, rightmost] = poppedTop->PopPreparation();

					wrapLeft->LinkR(leftmost);
					wrapRight->LinkL(rightmost);
				}

				_top = poppedTop->_left;
				poppedTop->JoinBrothers();
			}
			else
			{
				//si tengo o no tengo hijos no importa
				//será nullptr o será mi hijo
				_top = poppedTop->_leftmostChild;
			}
			_size--;

			if (size() > 0)
			{
				_Consolidate();
			}
			else
			{
				_top = nullptr;
			}

			delete poppedTop;
		}
	};

}