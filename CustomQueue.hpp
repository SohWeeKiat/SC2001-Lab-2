#pragma once
#include "PriorityQueue.hpp"
#include "DijstraDef.hpp"

namespace Dijkstra {
	class PriorityQueueArr : public Queue::PriorityQueueImp<Edge> {

	public:
		PriorityQueueArr(int source, int size);
		int GetElement() override;
		void Update(const Edge& Obj) override;
	};

	class PriorityQueueHeap : public Queue::PriorityQueueImp<Edge> {

	public:
		PriorityQueueHeap(int source, int size);
		int GetElement() override;
		void Update(const Edge& Obj) override;

	private:
		void FixHeap(int index);
		void Bubble(int index);

		int Parent(int index);
		int LeftChild(int index);
		int RightChild(int index);
	};
}