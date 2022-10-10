#pragma once
#include "CustomQueue.hpp"

namespace Dijkstra {

	class Dijkstra_APQ : public DijkstraImp<AdjMatrix> {

	public:
		Dijkstra_APQ(int vertex_count, const AdjList& edges, int start_vertex);
		Dijkstra_APQ(int vertex_count, AdjMatrix& edges, int start_vertex);
		virtual void Solve() override;

	private:
		PriorityQueueArrV2<Edge> pq;
	};

#define UseNewPQ 0
	class Dijkstra_MHPQ : public DijkstraImp<AdjList> {

	public:
		Dijkstra_MHPQ(int vertex_count, const AdjList& edges, int start_vertex);
		Dijkstra_MHPQ(int vertex_count, AdjMatrix& edges, int start_vertex);
		virtual void Solve() override;

	private:
#if UseNewPQ >= 1
		custom_priority_queueV2<Edge> pq;
#else
		custom_priority_queue<Edge> pq;
#endif
	};
}