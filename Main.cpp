#include "Dijkstra.hpp"
#include <iostream>
#include <chrono>

#define MIN_WEIGHT 1
#define MAX_WEIGHT 50

int main()
{
	std::vector<Dijkstra::AdjList> AdjListOfDiffEdge;

	int vertex_count = 100;
	Dijkstra::AdjList list(vertex_count);
	for (unsigned int v = 0; v < vertex_count - 1; v++)
		list[v].push_back(Dijkstra::Edge(v + 1, MIN_WEIGHT + rand() % MAX_WEIGHT));
	AdjListOfDiffEdge.push_back(list);

	for (int edge = 2; edge < 50; edge++) {
		for (unsigned int v = 0; v < vertex_count; v++) {
			if (list[v].size() < edge) {
				while (list[v].size() < edge) {
					unsigned int rand_vertex = rand() % vertex_count;
					while (rand_vertex == v)
						rand_vertex = rand() % vertex_count;
					if (rand_vertex >= vertex_count)
						printf("WTF\n");
					list[v].push_back(Dijkstra::Edge(rand_vertex, MIN_WEIGHT + rand() % MAX_WEIGHT));
				}
			}
		}
		AdjListOfDiffEdge.push_back(list);
	}
	for (int i = 0; i < AdjListOfDiffEdge.size(); i++) {
		std::cout << "----------Starting----------" << std::endl;
		std::cout << "Minimum Edge Per vertex: " << i + 1 << std::endl;

		auto list = AdjListOfDiffEdge[i];
		Dijkstra::Dijkstra_APQ apq(vertex_count, list, 0);
		auto start_time = std::chrono::high_resolution_clock::now();
		apq.Solve();
		auto end_time = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<
			std::chrono::microseconds>(end_time - start_time);
		std::cout << "Time taken by Dijkstra_APQ: " << duration.count() << " microseconds" << std::endl;

		list = AdjListOfDiffEdge[i];
		Dijkstra::Dijkstra_MHPQ mhpq(vertex_count, list, 0);
		start_time = std::chrono::high_resolution_clock::now();
		mhpq.Solve();
		end_time = std::chrono::high_resolution_clock::now();

		duration = std::chrono::duration_cast<
			std::chrono::microseconds>(end_time - start_time);
		std::cout << "Time taken by Dijkstra_MHPQ: " << duration.count() << " microseconds" << std::endl;
	}
	/*for (int i = 1; i < 6; i++) {//amount of vertex
		unsigned int vertex_count = std::pow(10, i);
		unsigned int max_edges = std::pow(vertex_count, 2);

		Dijkstra::AdjList list(vertex_count);
		for (unsigned int v = 0; v < vertex_count; v++)
			list[v].push_back(Dijkstra::Edge(v + 1, MIN_WEIGHT + rand() % MAX_WEIGHT));

		unsigned int amt_to_generate = max_edges - vertex_count - 1;
		amt_to_generate = rand() % amt_to_generate;
		for (unsigned int v = 0; v < amt_to_generate; v++) {
			unsigned int vertex = rand() % vertex_count;
			unsigned int rand_vertex = rand() % vertex_count;
			while(rand_vertex == vertex)
				rand_vertex = rand() % vertex_count;
			list[vertex].push_back(Dijkstra::Edge(rand_vertex, MIN_WEIGHT + rand() % MAX_WEIGHT));
		}
		AdjListOfDiffSizes.push_back(list);
	}*/

}