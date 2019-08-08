#pragma once
#include <iostream>
#include <functional>

namespace cds {

	template <class TT> class Node {
	public:
		const TT & _data;
		Node(const TT & data) : _data(data) {}


		void insert_as_brother(Node * other) {

		}
		void insert_as_child(Node * other) {

		}




	};

	template <class TT, std::function<void(TT,TT)> comp> class FibHeap 
	{
		size_t _nNodes = 0;
		Node<TT> *_topNode{ nullptr };



	public:
		bool empty() const
		{
			CompFunc();
			return _nNodes == 0;
		}
		size_t size() const {
			return _nNodes;
		}
		const TT & top() const {
			return _topNode->data;
		};
		void push(const TT & data) {

			if (_topNode)
			{
				Node<TT> *newNode = new Node(data);



				_topNode->insert_as_brother(newNode);

				//if (CompFunc(newNode->_data, _topNode->_data)) 
				{

				}


			}
			else
			{
				_topNode = new Node(data);
			}
		}

		template <class... Args> void emplace(Args&&... args);
		void pop();



	};


}