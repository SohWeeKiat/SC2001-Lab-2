#pragma once
#include <map>
#include <vector>
#include "DijstraDef.hpp"
#include "PriorityQueue.hpp"

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

	class Dijkstra_APQ : public DijkstraImp<AdjMatrix> {

	public:
		Dijkstra_APQ(int vertex_count, AdjList& edges, int start_vertex);
		virtual void Solve() override;

	private:
		PriorityQueueArr pq;
	};

	class Dijkstra_MHPQ : public DijkstraImp<AdjList> {

	public:
		Dijkstra_MHPQ(int vertex_count, AdjList& edges, int start_vertex);
		virtual void Solve() override;

	private:
		PriorityQueueHeap pq;
	};
}