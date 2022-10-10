#pragma once
#include <climits>
#include <vector>

namespace Dijkstra {
	struct Edge {
		int vertex;
		int weight;

		Edge() : vertex(0),
			weight(INT_MAX)
		{
		}

		Edge(int vertex, int weight) : vertex(vertex),
			weight(weight)
		{
		}

		Edge(const Edge& rhs) : vertex(rhs.vertex),
			weight(rhs.weight)
		{
		}

		Edge(Edge& rhs) : vertex(rhs.vertex),
			weight(rhs.weight)
		{
		}

		bool operator<(const Edge& rhs) const
		{
			return this->weight < rhs.weight;
		}

		bool operator<=(const Edge& rhs) const
		{
			return this->weight <= rhs.weight;
		}

		bool operator>(const Edge& rhs) const
		{
			return this->weight > rhs.weight;
		}

		bool operator==(const Edge& rhs) const
		{
			return this->vertex == rhs.vertex;
		}
	};

	typedef std::vector<std::vector<int>> AdjMatrix;//stores weight directly
	typedef std::vector<std::vector<Edge>> AdjList;


	template<typename T>
	class DijkstraImp {

	public:
		DijkstraImp(int start_vertex, int vertex_count) :
			vertex_count(vertex_count),
			S(vertex_count),
			dist(vertex_count),
			pred(vertex_count)
		{
			for (int i = 0; i < vertex_count; i++) {
				this->S[i] = false;
				this->dist[i] = INT_MAX;
				this->pred[i] = -1;
			}
			this->dist[start_vertex] = 0;
		}

		virtual void Solve() = 0;

	protected:
		int vertex_count;
		T edgeLinkages;
		std::vector<bool> S;
		std::vector<int> dist;
		std::vector<int> pred;
	};

}