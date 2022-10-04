#include "Dijkstra.hpp"

namespace Dijkstra {
	Dijkstra_APQ::Dijkstra_APQ(int vertex_count, AdjList& edges, int start_vertex) : 
		DijkstraImp<AdjMatrix>(start_vertex, vertex_count),
		pq(start_vertex, vertex_count)
	{
		this->edgeLinkages.resize(vertex_count);
		for (int i = 0; i < vertex_count; i++) {
			this->edgeLinkages[i].resize(vertex_count);
			memset(this->edgeLinkages[i].data(), 0, sizeof(int) * this->edgeLinkages[i].size());

			for (auto& e : edges[i])
				this->edgeLinkages[i][e.vertex] = e.weight;
		}
	}

	void Dijkstra_APQ::Solve()
	{
		int remaining = this->pq.GetSize();
		while (remaining > 0) {
			int u = this->pq.GetElement();
			this->S[u] = true;
			for (int i = 0; i < this->vertex_count; i++) {
				if (this->edgeLinkages[u][i] == 0)
					continue;//no linkage
				Edge v(i, this->edgeLinkages[u][i]);
				if (!this->S[v.vertex] && this->dist[v.vertex] > this->dist[u] + v.weight) {
					this->dist[v.vertex] = this->dist[u] + v.weight;
					this->pred[v.vertex] = u;
					this->pq.Update(Edge(v.vertex, this->dist[v.vertex]));
				}
			}
		}
	}

	/***********************************************************************/

	Dijkstra_MHPQ::Dijkstra_MHPQ(int vertex_count, AdjList& edges, int start_vertex) :
		DijkstraImp<AdjList>(start_vertex, vertex_count),
		pq(start_vertex, vertex_count)
	{
		this->edgeLinkages = edges;
	}

	void Dijkstra_MHPQ::Solve()
	{
		while (this->pq.GetSize()) {
			int u = this->pq.GetElement();
			this->S[u] = true;
			for (int i = 0; i < this->edgeLinkages[u].size(); i++) {
				Edge v = this->edgeLinkages[u][i];

				if (!this->S[v.vertex] && this->dist[v.vertex] > this->dist[u] + v.weight) {
					this->dist[v.vertex] = this->dist[u] + v.weight;
					this->pred[v.vertex] = u;
					this->pq.Update(Edge(v.vertex, this->dist[v.vertex]));
				}
			}
		}
	}
}