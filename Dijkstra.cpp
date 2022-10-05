#include "Dijkstra.hpp"
#include <iostream>

namespace Dijkstra {
	Dijkstra_APQ::Dijkstra_APQ(int vertex_count, AdjList& edges, int start_vertex) : 
		DijkstraImp<AdjMatrix>(start_vertex, vertex_count)
	{
		this->edgeLinkages.resize(vertex_count);
		for (int i = 0; i < vertex_count; i++) {
			this->edgeLinkages[i].resize(vertex_count);
			memset(this->edgeLinkages[i].data(), 0, sizeof(int) * this->edgeLinkages[i].size());

			for (auto& e : edges[i])
				this->edgeLinkages[i][e.vertex] = e.weight;
		}
		for (int i = 0; i < vertex_count; i++)
			this->pq.push_back(Edge(i, i == start_vertex ? 0 : INT_MAX));
	}

	void Dijkstra_APQ::Solve()
	{
		while (!this->pq.empty()) {
			auto edge = this->pq.top();
			int u = edge.vertex;
			this->S[u] = true;
			for (int i = 0; i < this->vertex_count; i++) {
				if (this->edgeLinkages[u][i] == 0)
					continue;//no linkage
				Edge v(i, this->edgeLinkages[u][i]);
				if (!this->S[v.vertex] && this->dist[v.vertex] > this->dist[u] + v.weight) {
					this->pq.remove(Edge(v.vertex, 0));

					this->dist[v.vertex] = this->dist[u] + v.weight;
					this->pred[v.vertex] = u;

					this->pq.push_back(Edge(v.vertex, this->dist[v.vertex]));
				}
			}
		}
	}

	/***********************************************************************/

	Dijkstra_MHPQ::Dijkstra_MHPQ(int vertex_count, AdjList& edges, int start_vertex) :
		DijkstraImp<AdjList>(start_vertex, vertex_count)
	{
		this->edgeLinkages = edges;
		for (int i = 0; i < vertex_count; i++)
			this->pq.push(Edge(i, i == start_vertex ? 0 : INT_MAX));
	}

	void Dijkstra_MHPQ::Solve()
	{
		while (!this->pq.empty()) {
			Edge edge = this->pq.top();
#if _DEBUG
			std::cout << "u:" << edge.vertex << " weight:" << edge.weight << std::endl;
#endif
			this->pq.pop();
			int u = edge.vertex;
			this->S[u] = true;
			for (int i = 0; i < this->edgeLinkages[u].size(); i++) {
				Edge v = this->edgeLinkages[u][i];
#if _DEBUG
				std::cout << "linkage: " << v.vertex << " " << v.weight << std::endl;
#endif
				if (!this->S[v.vertex] && this->dist[v.vertex] > this->dist[u] + v.weight) {
					this->pq.remove(Edge(v.vertex, 0));
#if _DEBUG
					std::cout << " this->dist[v.vertex]:" << this->dist[v.vertex] << std::endl;
					std::cout << " this->dist[u]:" << this->dist[u] << std::endl;
#endif
					this->dist[v.vertex] = this->dist[u] + v.weight;
					this->pred[v.vertex] = u;
#if _DEBUG
					std::cout << "vertex: " << v.vertex << " updating weight:" << this->dist[v.vertex] << std::endl;
#endif
					this->pq.push(Edge(v.vertex, this->dist[v.vertex]));
				}
			}
#if _DEBUG
			std::cout << "----------end----------" << std::endl;
#endif
		}
	}
}