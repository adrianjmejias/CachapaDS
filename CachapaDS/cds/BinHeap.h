#pragma once
#include "AbstractHeap.h"


namespace cds {

	namespace internal
	{
		template <typename TT>
		class BinHeapNode {
			using Node = BinHeapNode<TT>;

		public:
			
			Node *_left{ this };
			Node *_right{ this };
			Node *_parent{ nullptr };
			Node *_leftmostChild{ nullptr };
			TT _data;
			bool _dishonor{ false };
			size_t _order{ 0 };


			size_t Order() const { return _order; }

			/*
				uno 2 nodos.
			*/
			inline static void Link(Node* left, Node* right) {
				left->_right = right;
				right->_left = left;
			}
			void LinkL(Node* right) {
				Link(this, right);
			}
			void LinkR(Node* left) {
				Link(left, this);
			}

			BinHeapNode(const TT & data) : _data(data){}
			bool HasChildren() {
				return Order() > 0;
			}
			void InsertAsChild(Node* toInsert)
			{
				if (_leftmostChild) {
					_leftmostChild->InsertAsBrother(toInsert);
				}
				_leftmostChild = toInsert;
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
				Node* rightmost = _leftmostChild;

				int order = static_cast<int>(_order);

				while (order-- > 0) { 
					rightmost->_dishonor = false;
					rightmost->_parent = nullptr;
					rightmost = rightmost->_right; 
				}


				return std::make_tuple(leftmost, rightmost);
			}
		};
	}



	template <typename TT>
	class BinHeap : public AbstractHeap<TT>
	{
		using Node = internal::BinHeapNode<TT>;
		Node* _top{nullptr};
	
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
				while (!(consolidate.size() < act->_order)) consolidate.push_back(nullptr);

				Node* &consOrder = consolidate[act->_order];

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



			// Aca tengo que hacer otra estructura de datos donde quite los 
			// espacios nullptr que introduje al usar ese vector
			// como ya no me importa el orden de los tree podría ser otro vector rela

			std::remove_if(begin(consolidate), end(consolidate), [](Node* a) {return !a; });

			for (int ii = 0, iiEnd = consolidate.size() -1; ii < iiEnd; ii++) {
				Node* l = consolidate[ii];
				Node* r = consolidate[ii+1];
				l->LinkR(r);
			}

			//cerrando lista circular
			Node* last = consolidate[consolidate.size() - 1];
			Node* first = consolidate[0];

			last->LinkR(first);
		}
	
	public:
		BinHeap(CompareFn comp) : AbstractHeap(comp) {

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
				
				if (_compare(toInsert->_data, _top->_data)) {
					_top = toInsert;
				}
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

			
			
			// Si no es el unico root node
			if (poppedTop->_left != poppedTop) 
			{
				// ponemos esto solo como entry point para los hijos
				// debemos hacer consolidate para asegurarnos de que
				// cumpla con heap condition
				_top = poppedTop->_left;

				if (poppedTop->HasChildren()) {

					Node* wrapLeft{ _top->_left};
					Node* wrapRight{ _top->_right};
					
					auto [leftmost, rightmost] = poppedTop->PopPreparation();
					
					wrapLeft->LinkR(leftmost);
					wrapRight->LinkL(rightmost);
				}

				_Consolidate();
			}
			else
			{
				//si tengo o no tengo hijos no importa
				//será nullptr o será mi hijo
				_top = poppedTop->_leftmostChild;
			}
			
			delete poppedTop;
			_size--;
		}
	};

}