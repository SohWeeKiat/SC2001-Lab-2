#pragma once
#include "CustomQueue.hpp"

namespace Dijkstra {
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